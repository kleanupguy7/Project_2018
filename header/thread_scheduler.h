#ifndef THREAD_SCHEDULER_H
#define THREAD_SCHEDULER_H

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>



#include "../header/includes.h"

typedef struct histArg{
	uint64_t* payloads;
	uint64_t* rowId;
	uint64_t fromRow;
	uint64_t toRow;
	uint64_t** thread_hists;
	int loc;
}histArg;

typedef struct Job{
	struct Job* prev;
	void* (*function)(void* );
	void* arg;
}Job;

typedef struct Job_Q{
	Job* first;
	Job* last;
	int len;
}Job_Q;

typedef struct thread_info{
	long int id;
	pthread_t thread;
	struct threadpool *pool;
}thread_info;


typedef struct threadpool{
	thread_info** threads;
	int working;
	int alive;
	pthread_mutex_t access;
	pthread_cond_t all_idle;
	pthread_cond_t hasjobs;
	int num_threads;
	Job_Q *Q;
}threadpool;

threadpool* threadpool_init(int );
Job_Q* jobq_init(void );
void* thread_work(void* );
void thread_wait(void );
void* histogramJob(void* );
// void* print_thread_info(void *);
int add_work(Job_Q* ,void *(*function_p)(void*),void* );
Job* getJob();

uint64_t* rebuild_hist(uint64_t** ,uint64_t );

#endif