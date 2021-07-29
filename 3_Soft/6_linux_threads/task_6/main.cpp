#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* pthread1(void* param){
    int* idx = static_cast< int* >(param);
    pthread_mutex_lock(&lock);

    for(int i = 0; i < 10; i++){
        std::cout << i << ") i am tread "<< *idx << std::endl;
    }

    pthread_mutex_unlock(&lock);
    return nullptr;
}

void* pthread2(void* param){
    int* idx = static_cast< int* >(param);
    pthread_cond_wait(&cond, &lock);

    for(int i = 0; i < 10; i++){
        std::cout << i << ") i am tread "<< *idx << std::endl;
    }
    return nullptr;
}


int main()
{
    pthread_t tid[3] = {};
    pthread_attr_t attr = {};
    pthread_attr_init(&attr);

    int idx1 = 1, idx2 = 2, idx3 = 3;

    pthread_create(&tid[2], &attr, pthread2, &idx3);
    pthread_create(&tid[0], &attr, pthread1, &idx1);
    pthread_create(&tid[1], &attr, pthread1, &idx2);

    pthread_cond_broadcast(&cond);

    void* data;

    pthread_join(tid[0], &data);
    pthread_join(tid[1], &data);
    pthread_join(tid[2], &data);

    return 0;
}
