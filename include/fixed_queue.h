/******************************************************************************
 *
 *  Copyright (C) 2014 Google, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#pragma once

#include <stdbool.h>
#include "fixed_queue.h"
#include "list.h"
#include "osi.h"
#include "semaphore.h"


struct fixed_queue_t;
typedef struct fixed_queue_t {
	list_t *list;
	semaphore_t *enqueue_sem;
	semaphore_t *dequeue_sem;
	pthread_mutex_t lock;
	size_t capacity;
} fixed_queue_t;

typedef void (*fixed_queue_free_cb)(void *data);

// Creates a new fixed queue with the given |capacity|. If more elements than
// |capacity| are added to the queue, the caller is blocked until space is
// made available in the queue. Returns NULL on failure. The caller must free
// the returned queue with |fixed_queue_free|.
fixed_queue_t *fixed_queue_new(size_t capacity);

// Freeing a queue that is currently in use (i.e. has waiters
// blocked on it) results in undefined behaviour.
void fixed_queue_free(fixed_queue_t *queue, fixed_queue_free_cb free_cb);

// Enqueues the given |data| into the |queue|. The caller will be blocked
// if nore more space is available in the queue. Neither |queue| nor |data|
// may be NULL.
void fixed_queue_enqueue(fixed_queue_t *queue, void *data);

// Dequeues the next element from |queue|. If the queue is currently empty,
// this function will block the caller until an item is enqueued. This
// function will never return NULL. |queue| may not be NULL.
void *fixed_queue_dequeue(fixed_queue_t *queue);

// Tries to enqueue |data| into the |queue|. This function will never block
// the caller. If the queue capacity would be exceeded by adding one more
// element, this function returns false immediately. Otherwise, this function
// returns true. Neither |queue| nor |data| may be NULL.
bool fixed_queue_try_enqueue(fixed_queue_t *queue, void *data);

// Tries to dequeue an element from |queue|. This function will never block
// the caller. If the queue is empty, this function returns NULL immediately.
// Otherwise, the next element in the queue is returned. |queue| may not be
// NULL.
void *fixed_queue_try_dequeue(fixed_queue_t *queue);

// This function returns a valid file descriptor. Callers may perform one
// operation on the fd: select(2). If |select| indicates that the file
// descriptor is readable, the caller may call |fixed_queue_enqueue| without
// blocking. The caller must not close the returned file descriptor. |queue|
// may not be NULL.
int fixed_queue_get_enqueue_fd(const fixed_queue_t *queue);

// This function returns a valid file descriptor. Callers may perform one
// operation on the fd: select(2). If |select| indicates that the file
// descriptor is readable, the caller may call |fixed_queue_dequeue| without
// blocking. The caller must not close the returned file descriptor. |queue|
// may not be NULL.
int fixed_queue_get_dequeue_fd(const fixed_queue_t *queue);
