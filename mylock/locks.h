#ifndef __LOCKS_H__
#define __LOCKS_H__
enum lock_types;

/**
 * Have a look at https://linux.die.net/man/3/list_head for using list_head
 */
#include <sys/queue.h>
struct thread {
	pthread_t pthread;
	unsigned long flags;
	TAILQ_ENTRY(thread) next;
};

/*************************************************
 * Spinlock
 */
struct spinlock {
	/* Fill this in */
	int held;
};
void init_spinlock(struct spinlock *);
void acquire_spinlock(struct spinlock *);
void release_spinlock(struct spinlock *);


/*************************************************
 * Mutex
 */
struct mutex {
	/* Fill this in */
	int value;
	struct spinlock *sl;
	TAILQ_HEAD(threads, thread) waiters;
};
void init_mutex(struct mutex *);
void acquire_mutex(struct mutex *);
void release_mutex(struct mutex *);


/*************************************************
 * Semaphore
 */
struct semaphore {
	/* Fill this in */
	int value;
	struct spinlock *spl;
	TAILQ_HEAD(threads2, thread) waiters2;
};
void init_semaphore(struct semaphore *, const int);
void wait_semaphore(struct semaphore *);
void signal_semaphore(struct semaphore *);

/*************************************************
 * Lock tester.
 * Will be invoked if the program is run with -T
 */
void test_lock(void);
#endif