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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#

include ../make-rules/shared-macros.mk

download setup prep build install publish validate:	time-$(MACH32).so \
							time-$(MACH64).so

time-$(MACH64).o:			BITS=64
time-$(MACH32).o time-$(MACH64).o:	CFLAGS += -Kpic

time-$(MACH32).o time-$(MACH64).o:	time.c
	$(CC) $(CFLAGS) -c -o $@ $<

time-%.so:	time-%.o
	$(LD) -G -o $@ $<

clean:
	$(RM) time-*.o

clobber:	clean
	$(RM) time-*.so
