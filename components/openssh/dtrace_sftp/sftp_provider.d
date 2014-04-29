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

/*
 * We seem currently unable to depend properly on existing D libraries (like
 * sftp.d). But the definitions for conninfo_t and sftpinfo_t are stored there
 * (and have to be, since that's where the real translators live). So we're
 * forced to define something here to satisfy dtrace(1M), but none of the
 * definitions or translators here are actually used.
 */
typedef struct sftpinfo {
	int dummy;
} sftpinfo_t;

typedef struct sftpproto {
	int dummy;
} sftpproto_t;

typedef struct conninfo {
	int dummy;
} conninfo_t;

translator conninfo_t <sftpproto_t *dp> {
};

translator sftpinfo_t <sftpproto_t *dp> {
};

provider sftp {
	probe transfer__start(sftpproto_t *p) :
	    (conninfo_t *p, sftpinfo_t *p);
	probe transfer__done(sftpproto_t *p) :
	    (conninfo_t *p, sftpinfo_t *p);
};

#pragma D attributes Evolving/Evolving/ISA provider sftp provider
#pragma D attributes Private/Private/Unknown provider sftp module
#pragma D attributes Private/Private/Unknown provider sftp function
#pragma D attributes Private/Private/ISA provider sftp name
#pragma D attributes Evolving/Evolving/ISA provider sftp args
