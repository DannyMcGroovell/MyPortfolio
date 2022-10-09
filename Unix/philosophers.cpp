#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#define LEFT (i + K - 1) % K //������, ������������ ����� ������ ��������
#define RIGHT (i + 1) % K //������, ������������ ����� ������� ��������
#define THINKING 0 //��� ���������, ����� ������� ����������
#define HUNGRY 1 //��� ���������, ����� ������� ����� ������ (������� �������)
#define EATING 2 //��� ���������, ����� ������� ���
#define MAX_TIME 5 //������������ �����, ������� ����� ���� ��������� �� ��� �/��� �� �����������

int K; //���������� ���������
sem_t *mutex = NULL; //�������� ���������� ����� � ����������� ������� (����� - �������� �������)
sem_t *eaters = NULL; //��������� �� sem_t, ������� ������������ ������ ���������� �� ������ �� K ���������
int* state = NULL; //��������� �� ������ int'��, ��������������� ��������� ���������

//������� ��������
void eat(int i) {
        int time = rand() % MAX_TIME;
        printf("Philosopher #%d is eating...\n", i + 1);
        sleep(time);
        printf("Philosopher #%d stopped eating...\n", i + 1);
}

//������� �����������
void think(int i) {
        int time = rand() % MAX_TIME;
        printf("Philosopher #%d is thinking...\n", i + 1);
        sleep(time);
}

//��������, ������ �� ���������� � ��� �������� i-� �������...
void test(int i) {
        //���� ��� ������� �������, � ��� ������ �� ���� (�� ���� ����� ��������)
        if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
                state[i] = EATING; //������ ������, ��� ��� i-� ������� ����
                sem_post(&eaters[i]); //������� ����� ����, ������� �������������� �������, ����� �������� �� ������������� ������
        }
}

//i-� ������� �������� ����� �������...
void take_sticks(int i) {
        sem_wait(mutex); //������ � ����������� �������, ����� � ��������� �� ������ ������ ������� ������ ���� �������
        state[i] = HUNGRY; //i-� ������� ������ ����� ���� (� �� ���� �����, ���� �� ����� �����, �� ������� �� ����, �� ���� �� ��� ������...)
        test(i); //������� ����� ��� �����...
        sem_post(mutex); //������� �� ����������� �������
        sem_wait(&eaters[i]); //���� �� ������� ������ ���� (�� ���� sem_post �� ����������, � ������� ����� ����), �� �� �����������.
        //�������������� ��� ������ ������ ����� ����� ����
}

void put_sticks(int i) {
        sem_wait(mutex); //������ � ����������� �������, ����� � ��������� �� ������ ������ ������� ������ ���� �������
        state[i] = THINKING; //i-� ������� ������, ������ ����� ������
        test(LEFT); //���������, ���� ����� ����� ������� (�� ���� ������� �����), �� ��� ��� ������, ����� ��� ������ ���� 
//� �������� ���� ������ ����������� �� test(RIGHT), �������� ������������ ��� �������.
        test(RIGHT); //���������� � ������ �������... 
//
        sem_post(mutex);
}


//���, ������������� ������ ������� (��������������� ��������� ��������)
void* philosopher(void* arg) {
        int i = *((int*)arg);
        while (1 == 1) { //����������� ����
                think(i); //������� ������� ������
                take_sticks(i); //����� ���� ������� (���, ���� ���� ������, �������� �����)
                eat(i); //���
                put_sticks(i); //����� ������� �������
        }
}



int main(int argc, char* argv[]) {
        if (argc != 2) {
                fprintf(stderr, "Usage: %s <NUMBER_OF_PHILOSOPHERS>\n", argv[0]);
                return 1;
        }
 
        //���������������� �������...
        K = atoi(argv[1]); //��������� �� ������ � ������������� ����������
        if (K <= 1) { //���� ��� �����, ��� ���������� ������� ������ ����, �� �������� � ��������� ���������
                fprintf(stderr, "Error by transformation of the argument...\n");
                return 2; 
        }

        mutex = (sem_t*)malloc(sizeof(sem_t));
        if (sem_init(mutex, 0, 1) != 0) { //������ ������� ��� ������������� ������� � ����������� �������
                fprintf(stderr, "Error by creating semaphore...\n");
                return 3;
        }
 
        eaters = (sem_t*)calloc(K, sizeof(sem_t)); //�������� ������ ��� K ���������, ��������������� ���������
        state = (int*)calloc(K, sizeof(int)); //�������� ������ ��� K ������������� ����������, ��������������� ��������� ���������     

        memset(state, 0, K);

        srand(time(NULL));
        pthread_t *philosophers = (pthread_t*)malloc(K * sizeof(pthread_t)); //�������� ������ ��� K �������, ��������������� ���������

        int i;
        for (i = 0; i < K; i++) {
                if (sem_init(&eaters[i], 0, 0) != 0) {  //������ K ���������
                        fprintf(stderr, "Error by creating semaphore...\n");
                        return 3;
                }
        }

        int *t = (int *)malloc(sizeof(int));
        for (i = 0; i < K; i++) {
                *t = i;
                if (pthread_create(&philosophers[i], NULL, philosopher, t) != 0) { //������ ������
                        fprintf(stderr, "Error by creating thread\n");
                        return 2;
                }
        usleep(100000); //��� ��������� �����! 
        //���� � ���, ��� ����-�������� �������� �������� �����  i ��� ��������� ���� �� ������������� ����������. �� ���� ��������� ����� ���������� ���� �����.

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