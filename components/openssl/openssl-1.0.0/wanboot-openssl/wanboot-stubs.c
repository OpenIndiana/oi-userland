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
 */
/*
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

/* Content of this file is only needed for wanboot. */
#ifdef	_BOOT

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stddef.h>

/*
 * In OpenSSL 0.9.7 the EVP_read_pw_string now calls into the new "ui"
 * routines of 0.9.7, which is not compiled in the standalone, so it is
 * stubbed out here to avoid having to add a bunch of #ifndef's elsewhere.
 */
/* ARGSUSED */
int
EVP_read_pw_string_min(char *buf, int min, int len, const char *prompt, int
    verify)
{
	return (-1); /* failure */
}

/*
 * In standalone issetugid() is always false.
 */
int
OPENSSL_issetugid(void)
{
	return (1);
}

/*
 * Directory routines -- currently, the only consumer of these interfaces
 * is $SRC/common/openssl/ssl/ssl_cert.c, and it has fallback code in the
 * case of failure, so we just fail opendir() and stub out the rest.  At
 * some point, we may need to provide a real implementation.
 */
/* ARGSUSED */
DIR *
opendir(const char *dirname)
{
	errno = EACCES;
	return (NULL);
}

/* ARGSUSED */
struct dirent *
readdir(DIR *dirp)
{
	return (NULL);
}

/* ARGSUSED */
int
closedir(DIR *dirp)
{
	return (0);
}

/*
 * Atoi is used on multiple places in libcrypto.
 * This implementation is taken from stand-alone libsock library:
 * usr/src/stand/lib/sock/sock_test.c
 * Alternative solution: just extern it here, wanboot has -lsock anyway.
 */
#ifndef	isdigit
#define	isdigit(c) ((c) >= '0' && (c) <= '9')
#endif

#ifndef	isspace
#define	isspace(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || \
		    (c) == '\r' || (c) == '\f' || (c) == '\013')
#endif
int
atoi(const char *p)
{
	int n;
	int c = *p++, neg = 0;

	while (isspace(c)) {
		c = *p++;
	}
	if (!isdigit(c)) {
		switch (c) {
		case '-':
			neg++;
			/* FALLTHROUGH */
		case '+':
			c = *p++;
		}
	}
	for (n = 0; isdigit(c); c = *p++) {
		n *= 10; /* two steps to avoid unnecessary overflow */
		n += '0' - c; /* accum neg to avoid surprises at MAX */
	}
	return (neg ? n : -n);
}

#endif	/* _BOOT */
