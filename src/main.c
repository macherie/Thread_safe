#include <stdio.h>
#include <thread.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct
{
    thread_t        *worker_thread;
    pthread_mutex_t worker_thread_lock;
    bool            epilog_timer_created;
    int         epilog_timer_id;
} bt_hc_cb_t;
static bt_hc_cb_t hc_cb;

static void hello_world(void *context)  
{
	while(1) {
		printf("create pthread start \n");
		sleep(1);
		printf("hello world \n");
	}
}

static void can_test(void *context)
{
	while(1) {
		printf("create pthread start \n");
		sleep(1);
		printf("can test \n");
	}
}

static void cleanup(void)
{
	if (hc_cb.worker_thread) {
		thread_free(hc_cb.worker_thread);
	}
	pthread_mutex_lock(&hc_cb.worker_thread_lock);
	hc_cb.worker_thread = NULL;
	pthread_mutex_unlock(&hc_cb.worker_thread_lock);
}

int main(int argc, const char *argv[])
{

	hc_cb.epilog_timer_created = false;
	pthread_mutex_init(&hc_cb.worker_thread_lock, NULL);

	if (hc_cb.worker_thread) {
        printf("init has been called repeatedly without calling cleanup ?");
	}
	hc_cb.worker_thread = thread_new("hello");
  	printf("ret = %p \n", hc_cb.worker_thread);
	if (!hc_cb.worker_thread) {
		printf("unable to create worker thread \n");
		return -1;
	}

	if (hc_cb.worker_thread)
		thread_post(hc_cb.worker_thread, hello_world, NULL);

	if (hc_cb.worker_thread)
		//thread_post(hc_cb.worker_thread, can_test, NULL);

	sleep(1);

	thread_stop(hc_cb.worker_thread);

	sleep(1);

	cleanup();

	return 0;
}
