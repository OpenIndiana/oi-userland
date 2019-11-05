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

#
# Copyright (c) 2009, 2010, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2014 Alexander Pyhalov
#

PROG=		parted

CPPFLAGS +=	-I. \
		-I../libparted/common/lib \
		-I../libparted/common/include

OBJS=		command.o parted.o strlist.o table.o ui.o

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -fPIC -DPIC -c -o $@ $<

$(PROG): $(OBJS) $(LINK)
	$(CC) $(OBJS) $(LDLIBS) -o  $(PROG)

SRCS=		$(OBJS:%.o=%.c)

LDLIBS +=	-L../libparted/ -lparted

all: $(PROG)
install: $(PROG)
	install -D $(PROG) $(DESTDIR)/usr/sbin/$(PROG)

clean:
	$(RM) $(OBJS) $(PROG)
