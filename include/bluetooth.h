/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 * Not a Contribution
 *
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_INCLUDE_BLUETOOTH_H
#define ANDROID_INCLUDE_BLUETOOTH_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>


typedef void (*alarm_cb)(void *data);
typedef bool (*set_wake_alarm_callout)(uint64_t delay_millis, bool should_wake, alarm_cb cb, void *data);
typedef int (*acquire_wake_lock_callout)(const char *lock_name);
typedef int (*release_wake_lock_callout)(const char *lock_name);


#endif /* ANDROID_INCLUDE_BLUETOOTH_H */
