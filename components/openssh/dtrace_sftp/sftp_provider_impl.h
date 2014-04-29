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
 * Copyright (c) 2009, 2014, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef	_SFTP_PROVIDER_IMPL_H
#define	_SFTP_PROVIDER_IMPL_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * This structure must match the definition of same in sftp.d.
 */
typedef struct sftpproto {
	int64_t sftp_nbytes;		/* bytes writtten or read */
	const char *sftp_user;		/* user name */
	const char *sftp_operation;	/* SFTP Operation */
	const char *sftp_raddr;		/* remote address */
	const char *sftp_pathname;	/* path with file name */
	int32_t sftp_fd;		/* fd for transfer, if any */
} sftpproto_t;

#define	SFTP_TRANSFER_PROTO(proto, op, fd, path, len) \
	bzero((proto), sizeof (struct sftpproto)); \
	(proto)->sftp_user = (pw->pw_name ? pw->pw_name : "UNKNOWN"); \
	(proto)->sftp_operation = (op ? op : "UNKNOWN"); \
	(proto)->sftp_raddr = (client_addr); \
	(proto)->sftp_fd = (fd); \
	(proto)->sftp_pathname = (path ? path : "UNKNOWN"); \
	(proto)->sftp_nbytes = (len); \

#define	SFTP_TRANSFER_START_OP(op, fd, path, len) \
	if (SFTP_TRANSFER_START_ENABLED()) { \
		sftpproto_t proto; \
		SFTP_TRANSFER_PROTO(&proto, op, fd, path, len); \
		SFTP_TRANSFER_START(&proto); \
	} \

#define	SFTP_TRANSFER_DONE_OP(op, fd, path, len) \
	if (SFTP_TRANSFER_DONE_ENABLED()) { \
		sftpproto_t proto; \
		SFTP_TRANSFER_PROTO(&proto, op, fd, path, len); \
		SFTP_TRANSFER_DONE(&proto); \
	} \

#include <sftp_provider.h>

#ifdef	__cplusplus
}
#endif

#endif /* _SFTP_PROVIDER_IMPL_H */
