#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

APXS=apxs
DTRACE=/usr/sbin/dtrace

CC=`$(APXS) -q CC`
CFLAGS=`$(APXS) -q CFLAGS`
LDFLAGS_SHLIB=`$(APXS) -q LDFLAGS_SHLIB`

all: .libs/mod_dtrace.so

.libs/mod_dtrace.o: mod_dtrace.c
	$(APXS) -c -o mod_dtrace.so mod_dtrace.c && rm .libs/mod_dtrace.so

apache.o: .libs/mod_dtrace.o apache.d
	$(DTRACE) -G -o apache.o -s apache.d .libs/mod_dtrace.o

.libs/mod_dtrace.so: apache.o mapfile .libs/mod_dtrace.o
	$(CC) -Wl,-M -Wl,mapfile $(CFLAGS) -fPIC -shared $(LDFLAGS_SHLIB) -o .libs/mod_dtrace.so .libs/mod_dtrace.o apache.o
	
clean:
	-rm -f *.o *.so *.lo *.la *.slo
	-rm -rf .libs
