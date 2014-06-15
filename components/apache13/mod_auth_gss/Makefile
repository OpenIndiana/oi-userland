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
# Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
#ident	"@(#)Makefile	1.3	07/03/09 SMI"
#


GSS_CPPFLAGS =  -DEAPI -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -I/usr/include/gssapi
GSS_LDFLAGS =  -lgss -lresolv

CPPFLAGS = -I. $(GSS_CPPFLAGS) $(DEFS) -I$(SERVER)/src/include -I$(SERVER)/src/os/unix
LDFLAGS = -zcombreloc -shared $(GSS_LDFLAGS)
CFLAGS =

all: mod_auth_gss.so

install: mod_auth_gss.so
	$(SERVER)/src/helpers/install.sh -c -m 755 mod_auth_gss.so $(DESTDIR)/usr/apache/libexec/mod_auth_gss.so

clobber clean:
	$(RM) *.o *.so *.la *.lo core

.SUFFIXES:	.o .so

.c.o:
	$(CC) -c $(CPPFLAGS) $<

.c.so:
	$(CC) -c $(CPPFLAGS) $< 
	$(LD) $(LDFLAGS) -o $@ $*.o 

.PHONY: all install clean distclean
