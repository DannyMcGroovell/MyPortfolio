#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#define LEFT (i + K - 1) % K //макрос, определяющий номер левого философа
#define RIGHT (i + 1) % K //макрос, определяющий номер правого философа
#define THINKING 0 //код состояния, когда философ размышляет
#define HUNGRY 1 //код состояния, когда философ хочет поесть (ожидает палочки)
#define EATING 2 //код состояния, когда философ ест
#define MAX_TIME 5 //максимальное время, которое может быть потрачено на еду и/или на размышления

int K; //количество философов
sem_t *mutex = NULL; //взаимное исключение входа в критическую область (взять - положить палочки)
sem_t *eaters = NULL; //указатель на sem_t, которые впоследствии станет указателем на массив из K семафоров
int* state = NULL; //указатель на массив int'ов, характеризующий состояния философов

//процесс поедания
void eat(int i) {
        int time = rand() % MAX_TIME;
        printf("Philosopher #%d is eating...\n", i + 1);
        sleep(time);
        printf("Philosopher #%d stopped eating...\n", i + 1);
}

//процесс размышлений
void think(int i) {
        int time = rand() % MAX_TIME;
        printf("Philosopher #%d is thinking...\n", i + 1);
        sleep(time);
}

//проверка, сможет ли приступить к еде голодный i-й философ...
void test(int i) {
        //если сам филосов голоден, а его соседи не едят (то есть вилки свободны)
        if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
                state[i] = EATING; //меняем статус, что наш i-й философ поел
                sem_post(&eaters[i]); //филосов начал есть, поэтому инкрементируем семафор, чтобы философа не заблокировали соседи
        }
}

//i-й философ пытается взять палочку...
void take_sticks(int i) {
        sem_wait(mutex); //входим в критическую область, чтобы с палочками на данный момент работал только один философ
        state[i] = HUNGRY; //i-й философ теперь хочет есть (а он либо поест, либо не поест сразу, всё зависит от того, не едят ли его соседи...)
        test(i); //попытка взять две вилки...
        sem_post(mutex); //выходим из критической области
        sem_wait(&eaters[i]); //если не удалось начать есть (то есть sem_post не выполнился, и семафор равен нулю), то он блокируется.
        //разблокировать его смогут соседи после приёма пищи
}

void put_sticks(int i) {
        sem_wait(mutex); //входим в критическую область, чтобы с палочками на данный момент работал только один философ
        state[i] = THINKING; //i-й философ наелся, теперь начал думать
        test(LEFT); //проверяем, если сосед слева голоден (то есть ожидают вилку), то даём ему сигнал, чтобы они начали есть 
//Я позволил себе убрать комментарий от test(RIGHT), очевидно поставленный для отладки.
        test(RIGHT); //аналогично с правым соседом... 
//
        sem_post(mutex);
}


//код, выполняющийся каждым потоком (характеризующий поведение философа)
void* philosopher(void* arg) {
        int i = *((int*)arg);
        while (1 == 1) { //бесконечный цикл
                think(i); //сначала философ думает
                take_sticks(i); //затем берёт палочки (или, если быть точнее, пытается взять)
                eat(i); //ест
                put_sticks(i); //кладёт палочки обратно
        }
}



int main(int argc, char* argv[]) {
        if (argc != 2) {
                fprintf(stderr, "Usage: %s <NUMBER_OF_PHILOSOPHERS>\n", argv[0]);
                return 1;
        }
 
        //подготовительный процесс...
        K = atoi(argv[1]); //переводим из строки в целочисленную переменную
        if (K <= 1) { //если так вышло, что количество филосов меньше двух, то ругаемся и завершаем программу
                fprintf(stderr, "Error by transformation of the argument...\n");
                return 2; 
        }

        mutex = (sem_t*)malloc(sizeof(sem_t));
        if (sem_init(mutex, 0, 1) != 0) { //создаём мьютекс для разграничения доступа к критической области
                fprintf(stderr, "Error by creating semaphore...\n");
                return 3;
        }
 
        eaters = (sem_t*)calloc(K, sizeof(sem_t)); //выделяем память под K семафоров, характеризующих философов
        state = (int*)calloc(K, sizeof(int)); //выделяем память под K целочисленных аргументов, характеризующие состояния философов     

        memset(state, 0, K);

        srand(time(NULL));
        pthread_t *philosophers = (pthread_t*)malloc(K * sizeof(pthread_t)); //выделяем память под K потоков, символизирующие философов

        int i;
        for (i = 0; i < K; i++) {
                if (sem_init(&eaters[i], 0, 0) != 0) {  //создаём K семафоров
                        fprintf(stderr, "Error by creating semaphore...\n");
                        return 3;
                }
        }

        int *t = (int *)malloc(sizeof(int));
        for (i = 0; i < K; i++) {
                *t = i;
                if (pthread_create(&philosophers[i], NULL, philosopher, t) != 0) { //создаём потоки
                        fprintf(stderr, "Error by creating thread\n");
                        return 2;
                }
        usleep(100000); //Вся загвоздка здесь! 
        //Дело в том, что Нить-родитель успевает изменить номер  i для следующей нити до инициализации предыдущей. То есть несколько нитей импользуют один номер.

    }

        void* result;
        for (i = 0; i < K; i++) {
                if (philosophers[i] != -1) {
                        if (pthread_join(philosophers[i], &result) != 0) {
                                fprintf(stderr, "Error by joining thread\n");
                                return 3;
                        }
                }
        }
        return 0;
}