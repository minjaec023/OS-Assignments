#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#include "config.h"
#include "locks.h"

static int nr_slots = 0;

static enum lock_types lock_type;

void (*enqueue_fn)(int value) = NULL;
int (*dequeue_fn)(void) = NULL;

void enqueue_ringbuffer(int value)
{
	assert(enqueue_fn);
	assert(value >= MIN_VALUE && value < MAX_VALUE);

	enqueue_fn(value);
}

int dequeue_ringbuffer(void)
{
	int value;

	assert(dequeue_fn);

	value = dequeue_fn();
	assert(value >= MIN_VALUE && value < MAX_VALUE);

	return value;
}


/*********************************************************************
 * TODO: Implement using spinlock
 */
typedef struct ring_buffer{
	int* queue;
	int size;
	int in;
	int out;
	int data;
}ring_buffer;

struct spinlock splock;
struct ring_buffer rb;

void enqueue_using_spinlock(int value)
{
again:
	acquire_spinlock(&splock);
	if((rb.in+1)%rb.size == rb.out){
		release_spinlock(&splock);
		goto again;
	}
	
	
	rb.queue[rb.in] = value;
	rb.in = (rb.in+1)%rb.size;
	release_spinlock(&splock);

}

int dequeue_using_spinlock(void)
{
	
again:
	acquire_spinlock(&splock);

	if(rb.in == rb.out){
		release_spinlock(&splock);
		goto again;
	}
	
	rb.data = rb.queue[rb.out];
	rb.out = (rb.out+1)%rb.size;
	release_spinlock(&splock);
	
	return rb.data;
}

void init_using_spinlock(void)
{
	init_spinlock(&splock);	
	enqueue_fn = &enqueue_using_spinlock;
	dequeue_fn = &dequeue_using_spinlock;
}

void fini_using_spinlock(void)
{
	free(rb.queue);
}

/*********************************************************************
 * TODO: Implement using mutex
 */

struct mutex mtlock;

void enqueue_using_mutex(int value)
{

again:
	acquire_mutex(&mtlock);
	if((rb.in+1)%rb.size == rb.out){
		release_mutex(&mtlock);
		goto again;
	}
	
	rb.queue[rb.in] = value;
	rb.in = (rb.in+1)%rb.size;

	release_mutex(&mtlock);
}

int dequeue_using_mutex(void)
{
again:
	acquire_mutex(&mtlock);
	if(rb.in == rb.out){
		release_mutex(&mtlock);
		goto again;
	}
	rb.data = rb.queue[rb.out];
	rb.out = (rb.out+1)%rb.size;
	
	release_mutex(&mtlock);
	
	return rb.data;
}

void init_using_mutex(void)
{
	enqueue_fn = &enqueue_using_mutex;
	dequeue_fn = &dequeue_using_mutex;

	mtlock.sl = malloc(sizeof(mtlock.sl));
	init_spinlock(mtlock.sl);
	init_mutex(&mtlock);
	TAILQ_INIT(&mtlock.waiters);
}

void fini_using_mutex(void)
{
	free(mtlock.sl);
	free(rb.queue);
}


/*********************************************************************
 * TODO: Implement using semaphore
 */
struct semaphore sm;
void enqueue_using_semaphore(int value)
{
//printf("enqueue\n");

again:
	wait_semaphore(&sm);
	if((rb.in+1)%rb.size == rb.out){
		signal_semaphore(&sm);
		goto again;
	}
	rb.queue[rb.in] = value;
	rb.in = (rb.in+1)%rb.size;

	//printf("en.value\n");
	signal_semaphore(&sm);

}

int dequeue_using_semaphore(void)
{
	//printf("dequeue\n");
	
again:
	wait_semaphore(&sm);
	if(rb.in == rb.out){
		signal_semaphore(&sm);
		goto again;
	}
	rb.data = rb.queue[rb.out];
	rb.out = (rb.out+1)%rb.size;
	//printf("de.value\n");

	
	signal_semaphore(&sm);
	
	return rb.data;
}

void init_using_semaphore(void)
{
 	enqueue_fn = &enqueue_using_semaphore;
	dequeue_fn = &dequeue_using_semaphore;

	sm.spl = malloc(sizeof(sm.spl));
	init_spinlock(sm.spl);

	init_semaphore(&sm, 4);
	TAILQ_INIT(&sm.waiters2);
}

void fini_using_semaphore(void)
{
	free(sm.spl);
	free(rb.queue);
}


/*********************************************************************
 * Common implementation
 */
int init_ringbuffer(const int _nr_slots_, const enum lock_types _lock_type_)
{
	assert(_nr_slots_ > 0);
	nr_slots = _nr_slots_;

	/* Initialize lock! */
	lock_type = _lock_type_;
	switch (lock_type) {
	case lock_spinlock:
		init_using_spinlock();
		break;
	case lock_mutex:
		init_using_mutex();
		break;
	case lock_semaphore:
		init_using_semaphore();
		break;
	}

	/* TODO: Initialize your ringbuffer and synchronization mechanism */
	rb.queue = (int*)malloc(sizeof(rb.queue)*(nr_slots+1));
	rb.in = 0;
	rb.out = 0;
	rb.size = _nr_slots_+1;
	rb.data = 0;
	return 0;
}

void fini_ringbuffer(void)
{
	/* TODO: Clean up what you allocated */
	switch (lock_type) {
		default:
			break;
		case lock_spinlock:
			fini_using_spinlock();
			break;
		case lock_mutex:
			fini_using_mutex();
			break;
		case lock_semaphore:
			fini_using_semaphore();
			break;
	}
}