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
 * is preloaded, it interposes on time(2) and returns a constant value when
 * the execname matches one of the desired "programs" and TIME_CONSTANT
 * contains an integer value to be returned.
 */

#include <stdlib.h>
#include <ucontext.h>
#include <dlfcn.h>
#include <strings.h>

/* The list of programs that we want to use a constant time. */
static char *programs[] = { "date", "cpp", "cc1", "perl", NULL };

static int
stack_info(uintptr_t pc, int signo, void *arg)
{
	Dl_info info;
	void *sym;

	if (dladdr1((void *)pc, &info, &sym, RTLD_DL_SYMENT) != NULL) {
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
intercept()
{
	char *execname = my_execname();
	time_t result = -1;

	if (execname != NULL) {
		int i;

		for (i = 0; programs[i] != NULL; i++)
			if (strcmp(execname, programs[i]) == 0) {
				static char *time_constant;

				if (time_constant == NULL)
					time_constant = getenv("TIME_CONSTANT");

				if (time_constant != NULL)
					result = atoll(time_constant);

				break;
			}
	}

	return (result);
}

time_t
time(time_t *ptr)
{
	time_t result = intercept();

	if (result == (time_t)-1) {
		static time_t (*fptr)(time_t *);

		if (fptr == NULL)
			fptr = (time_t (*)(time_t *))dlsym(RTLD_NEXT, "time");

		result = (fptr)(ptr);
	} else if (ptr != NULL)
			*ptr = result;

	return (result);
}
