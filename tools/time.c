/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 *
 * Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
 */

/*
 * This compiles to a module that can be preloaded during a build.  If this
 * is preloaded, it interposes on time(2), gettimeofday(3C), and
 * clock_gethrtime(3C) and returns a constant number of seconds since epoch
 * when the execname matches one of the desired "programs" and TIME_CONSTANT
 * contains an integer value to be returned.
 */

#include <stdlib.h>
#include <ucontext.h>
#include <dlfcn.h>
#include <strings.h>
#include <time.h>

/* The list of programs that we want to use a constant time. */
static char *programs[] = { 
	"autogen", "bash", "cpp", "cc1", "date", "doxygen",
	"erl", "grops", "gs", "gtroff", "javadoc", "ksh", "ksh93", "ld",
	"perl", "perl5.8.4", "perl5.10", "ruby", "sh", NULL
};

static int
stack_info(uintptr_t pc, int signo, void *arg)
{
	Dl_info info;
	void *sym;

	if (dladdr1((void *)pc, &info, &sym, RTLD_DL_SYMENT) != 0) {
		if (strstr(info.dli_fname, ".so") == NULL)
			*(char **)arg = (char *)info.dli_fname;
	}

	return (0);
}

static char *
my_execname()
{
	static char *execname;

	if (execname == NULL) {
		ucontext_t ctx;

		if (getcontext(&ctx) == 0)
			walkcontext(&ctx, stack_info, &execname);

		if (execname != NULL) {
			char *s = strrchr(execname, '/');

			if (s != NULL)
				execname = ++s;
		}
	}

	return (execname);
}

static time_t
time_constant()
{
	char *execname = my_execname();
	time_t result = -1;

	if (execname != NULL) {
		int i;

		for (i = 0; programs[i] != NULL; i++)
			if (strcmp(execname, programs[i]) == 0) {
				static char *time_string;

				if (time_string == NULL)
					time_string = getenv("TIME_CONSTANT");

				if (time_string != NULL)
					result = atoll(time_string);

				break;
			}
	}

	return (result);
}

time_t
time(time_t *ptr)
{
	time_t result = time_constant();

	if (result == (time_t)-1) {
		static time_t (*fptr)(time_t *);

		if (fptr == NULL)
			fptr = (time_t (*)(time_t *))dlsym(RTLD_NEXT, "time");

		result = (fptr)(ptr);
	} else if (ptr != NULL)
			*ptr = result;

	return (result);
}

int
gettimeofday(struct timeval *tp, void *tzp)
{
	static int (*fptr)(struct timeval *, void *);
	int result = -1;

	if (fptr == NULL)
		fptr = (int (*)(struct timeval *, void *))dlsym(RTLD_NEXT,
				"gettimeofday");

	if ((result = (fptr)(tp, tzp)) == 0) {
		time_t curtime = time_constant();

		if (curtime != (time_t)-1)
			tp->tv_sec = curtime;
	}

	return (result);
}

int
clock_gettime(clockid_t clock_id, struct timespec *tp)
{
	static int (*fptr)(clockid_t, struct timespec *);
	int result = -1;

	if (fptr == NULL)
		fptr = (int (*)(clockid_t, struct timespec *))dlsym(RTLD_NEXT,
				"clock_gettime");

	if ((result = (fptr)(clock_id, tp)) == 0) {
		time_t curtime = time_constant();

		if (curtime != (time_t)-1)
			tp->tv_sec = curtime;
	}

	return (result);
}
