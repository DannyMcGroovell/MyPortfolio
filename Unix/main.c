#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <string.h>

// Число философов
#define N 5 

struct shared_data {
  sem_t mutex;
  sem_t eaters[N];
  int state[N];
};

struct shared_data *shared;

void initialize_shared()
{
    shared = mmap(
        0, 
        sizeof(struct shared_data), 
        PROT_READ | PROT_WRITE, 
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );
    memset(shared, 0, sizeof(struct shared_data));
    sem_init(&shared->mutex, 1, 1);
    for(int i = 0; i < N; ++i) 
    {
        sem_init(&shared->eaters[i], 1, 1);
    }
}

void deinitialize_shared()
{
    for(int i = 0; i < N; ++i)
    { 
        sem_destroy(&shared->eaters[i]);
    }
    sem_destroy(&shared->mutex);
    munmap(shared, sizeof(struct shared_data));
}

#define LEFT (i + N - 1) % N // макрос, определяющий номер левого философа
#define RIGHT (i + 1) % N    // макрос, определяющий номер правого философа

#define THINKING 0 // код состояния, когда философ размышляет
#define HUNGRY   1 // код состояния, когда философ хочет поесть (ожидает палочки)
#define EATING   2 // код состояния, когда философ ест

static const char * state_names[] = {"THINKING", "HUNGRY", "EATING"};

#define MAX_TIME 5 // максимальное время, которое может быть потрачено на еду и/или на размышления


// процесс поедания
void eat() 
{
    int time = rand() % MAX_TIME;
    sleep(time);
}

// процесс размышлений
void think() 
{
    int time = rand() % MAX_TIME;
    sleep(time);
}

// проверка, сможет ли приступить к еде голодный i-й философ...
void test(int i) 
{
    // если сам философ голоден, а его соседи не едят (то есть вилки свободны)
    if (shared->state[i] == HUNGRY && 
        shared->state[LEFT] != EATING && 
        shared->state[RIGHT] != EATING
    ) 
    {
        shared->state[i] = EATING;    // меняем статус, что наш i-й философ поел
        sem_post(&shared->eaters[i]); // философ начал есть, поэтому инкрементируем семафор, чтобы философа не заблокировали соседи
    }
}

// i-й философ пытается взять палочку...
void take_sticks(int i) 
{
    sem_wait(&shared->mutex); // входим в критическую область, чтобы с палочками на данный момент работал только один философ
    shared->state[i] = HUNGRY; // i-й философ теперь хочет есть (а он либо поест, либо не поест сразу, всё зависит от того, не едят ли его соседи...)
    test(i); // попытка взять две вилки...
    sem_post(&shared->mutex); // выходим из критической области
    sem_wait(&shared->eaters[i]); // если не удалось начать есть (то есть sem_post не выполнился, и семафор равен нулю), то он блокируется.
    // разблокировать его смогут соседи после приёма пищи
}

void put_sticks(int i) 
{
    sem_wait(&shared->mutex); // входим в критическую область, чтобы с палочками на данный момент работал только один философ
    shared->state[i] = THINKING; // i-й философ наелся, теперь начал думать
    test(LEFT); // проверяем, если сосед слева голоден (то есть ожидает вилку), то даём ему сигнал, чтобы они начали есть 
    test(RIGHT); // аналогично с правым соседом... 
    sem_post(&shared->mutex);
}

void philosopher(int i)
{
    while (1) // бесконечный цикл
    {
        think();        // сначала философ думает
        take_sticks(i); // затем берёт палочки (или, если быть точнее, пытается взять)
        eat();          // ест
        put_sticks(i);  // кладёт палочки обратно
    }
}

void print_states()
{
    sem_wait(&shared->mutex);
    for (int i = 0; i < N; ++i)
    {
        printf("Philosopher %i is %s\n", i, state_names[shared->state[i]]);
    }
    printf("\n");
    sem_post(&shared->mutex);
}

int main()
{
    initialize_shared();

    pid_t philosophers[N];
    for (int i = 0; i < N; ++i)
    {
        pid_t id = fork();
        if (id == 0) // дитя
        {
            philosopher(i);
            exit(0);
        }
        else if (id > 0) // родитель
        {
            philosophers[i] = id;
            printf("philosophers[%d]=%d\n", i, philosophers[i]);
        }
        else
        {
           printf("Error\n");
           exit(1);
        }
    }

    while (1)
    {
        print_states();
        sleep(1);
    }
    

    // ждём окончания работы детей
    for(int i = 0; i < N; ++i) 
    {
        waitpid(philosophers[i], NULL, 0);
    }

    deinitialize_shared();

    return 0;
}
