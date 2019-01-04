/* Copyright (c) 2018 Evan Wyatt
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __JERS_COMMON_H
#define __JERS_COMMON_H

#include <sys/types.h>

#include <uthash.h>

/* Used for loggingMode */
#define JERS_LOG_DEBUG    0
#define JERS_LOG_INFO     1
#define JERS_LOG_WARNING  2
#define JERS_LOG_CRITICAL 3

struct user {
	uid_t uid;
	gid_t gid;

	char * username;
	char * shell;
	char * home_dir;

	int group_count;
	gid_t * group_list;

	int env_count;				// Number of variables being used in users_env
	int env_size;  				// Number of variables that can be stored in user_env
	char ** users_env;			// Variables - NULL terminated
	char * users_env_buffer;	// Buffer storing the cached variables for the user

	time_t expiry;

	UT_hash_handle hh;
};

#define CACHE_EXPIRY 900 // 15 minutes

int64_t getTimeMS(void);

char * removeWhitespace(char * str);
void uppercasestring(char * str);
void lowercasestring(char * str);
int int64tostr(char * dest, int64_t num);
void _logMessage(const char * whom, int level, const char * message);
char * gethost(void);

int matches(const char * pattern, const char * string);

char * print_time(const struct timespec * time, int elapsed);
void timespec_diff(const struct timespec *start, const struct timespec *end, struct timespec *diff);

struct user * lookup_user(uid_t uid, int load_env);

#endif