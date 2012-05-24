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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#

include $(SRC)/make-rules/Makefile.env

CPPFLAGS += -I/usr/include/libxml2
LDLIBS += -lxml2 -lcrypto

# Compensate for libxml's lint library
LINTFLAGS += -erroff=E_INCONS_ARG_DECL2

MOD_APIS=panels
MOD_OBJS=mod_panels.o
MOD_LIBNAME=mod_panels.so
MOD_INSTALLDIR=$(RADDIR_MODULE)

DTDDIR=$(ROOT)/usr/share/lib/xml/dtd
APISDIR=../../../../apis

include $(SRC)/make-rules/Makefile.com

install: $(DTDDIR)/vpanel.dtd.1

FILEMODE=444
$(DTDDIR)/%: %
	$(INS.file);
	$(RMCDDL)
