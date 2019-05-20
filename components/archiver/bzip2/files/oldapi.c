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
 *  Copyright (c) 2001, 2011, Oracle and/or its affiliates. All rights reserved.
 */

#include <stdio.h>
#include "bzlib.h"

/*
 * Wrappers for the old names. For compatibility with Solaris 8.
 */

int
bzCompressInit(bz_stream *strm, int blockSize100k, int verbosity,
    int workFactor)
{
	return (BZ2_bzCompressInit(strm, blockSize100k, verbosity, workFactor));
}

int
bzCompress(bz_stream *strm, int action)
{
	return (BZ2_bzCompress(strm, action));
}

int
bzCompressEnd(bz_stream *strm)
{
	return (BZ2_bzCompressEnd(strm));
}

int
bzDecompressInit(bz_stream *strm, int verbosity, int small)
{
	return (BZ2_bzDecompressInit(strm, verbosity, small));
}

int
bzDecompress(bz_stream *strm)
{
	return (BZ2_bzDecompress(strm));
}

int
bzDecompressEnd(bz_stream *strm)
{
	return (BZ2_bzDecompressEnd(strm));
}

BZFILE *
bzReadOpen(int *bzerror, FILE *f, int verbosity, int small, void *unused,
    int nUnused)
{
	return (BZ2_bzReadOpen(bzerror, f, verbosity, small, unused, nUnused));
}

void
bzReadClose(int *bzerror, BZFILE *b)
{
	BZ2_bzReadClose(bzerror, b);
}

void
bzReadGetUnused(int *bzerror, BZFILE *b, void **unused, int *nUnused)
{
	BZ2_bzReadGetUnused(bzerror, b, unused, nUnused);
}

int
bzRead(int *bzerror, BZFILE *b, void *buf, int len)
{
	return (BZ2_bzRead(bzerror, b, buf, len));
}

BZFILE *
bzWriteOpen(int *bzerror, FILE *f, int blockSize100k, int verbosity,
    int workFactor)
{
	return (BZ2_bzWriteOpen(bzerror, f, blockSize100k, verbosity,
	    workFactor));
}

void
bzWrite(int *bzerror, BZFILE *b, void *buf, int len)
{
	BZ2_bzWrite(bzerror, b, buf, len);
}

void
bzWriteClose(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in,
    unsigned int *nbytes_out)
{
	BZ2_bzWriteClose(bzerror, b, abandon, nbytes_in, nbytes_out);
}

int
bzBuffToBuffCompress(char *dest, unsigned int *destLen, char *source,
    unsigned int sourceLen, int blockSize100k, int verbosity, int workFactor)
{
	return (BZ2_bzBuffToBuffCompress(dest, destLen, source, sourceLen,
	    blockSize100k, verbosity, workFactor));
}

int
bzBuffToBuffDecompress(char *dest, unsigned int *destLen, char *source,
    unsigned int sourceLen, int small, int verbosity)
{
	return (BZ2_bzBuffToBuffDecompress(dest, destLen, source, sourceLen,
	    small, verbosity));
}


const char *
bzlibVersion(void)
{
	return (BZ2_bzlibVersion());
}

BZFILE *
bzopen(const char *path, const char *mode)
{
	return (BZ2_bzopen(path, mode));
}

BZFILE *
bzdopen(int fd, const char *mode)
{
	return (BZ2_bzdopen(fd, mode));
}

int
bzread(BZFILE *b, void *buf, int len)
{
	return (BZ2_bzread(b, buf, len));
}

int
bzwrite(BZFILE *b, void *buf, int len)
{
	return (BZ2_bzwrite(b, buf, len));
}

int
bzflush(BZFILE *b)
{
	return (BZ2_bzflush(b));
}

void
bzclose(BZFILE *b)
{
	BZ2_bzclose(b);
}

const char *
bzerror(BZFILE *b, int *errnum)
{
	return (BZ2_bzerror(b, errnum));
}
