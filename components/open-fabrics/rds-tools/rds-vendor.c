/*
 * Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/*
 * OFED Solaris ioctl wrapper
 */
#if defined(__SVR4) && defined(__sun)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include <stropts.h>
#include <sys/rds.h>

int
sol_ioctl(int fd, int opt_val, struct rds_info_arg *argp, socklen_t *ulen,
    int *item_size)
{
	int len;
	struct rds_info_arg arg = *argp;

	/* 1st call gets the length of the data available */
	*ulen = 0;
	bzero(&arg, sizeof (struct rds_info_arg));
	arg.lenp = (uint64_t)(uintptr_t)ulen;
	arg.datap = NULL;
	*item_size = ioctl(fd, opt_val, &arg);
	argp->lenp = arg.lenp;
	argp->datap = arg.datap;
	if ((*item_size < 0) && (errno != ENOSPC))
		return (1);

	do {
		if (*ulen == 0)
			return (0);
		if (arg.datap)
			arg.datap = (uint64_t)(uintptr_t)realloc(
			    (char *)(uintptr_t)arg.datap, *ulen);
		else
			arg.datap = (uint64_t)(uintptr_t)malloc(*ulen);

		if (arg.datap == NULL)
			return (2);

		/* 2nd call gets the data */
		len = *ulen;
		*item_size = ioctl(fd, opt_val, &arg);
		argp->lenp = arg.lenp;
		argp->datap = arg.datap;
		if ((*item_size < 0) && (errno != ENOSPC)) {
			return (3);
		}
	} while (*ulen > len);
	return (0);
}
#endif
