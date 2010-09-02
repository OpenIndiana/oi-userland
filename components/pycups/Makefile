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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pycups
COMPONENT_VERSION=	1.9.46
IPS_PKG_NAME=		library/python-2/pycups
COMPONENT_DESCRIPTION=	"Python language bindings for CUPS"
COMPONENT_CLASSIFICATION="System/Printing"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://cyberelk.net/tim/software/pycups/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:3d58a0f7b4a1b6a2880baf9ef5e14eae461d0982
COMPONENT_ARCHIVE_URL=	http://cyberelk.net/tim/data/pycups/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/setup.py.mk
include ../../make-rules/ips.mk

PYTHON_ENV +=	CFLAGS=-DVERSION=\\\"$(COMPONENT_VERSION)\\\"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

REQUIRED_TOOL +=	/sbin/uname
REQUIRED_TOOL +=	/usr/bin/basename
REQUIRED_TOOL +=	/usr/bin/env
REQUIRED_TOOL +=	/usr/bin/find
REQUIRED_TOOL +=	/usr/bin/grep
REQUIRED_TOOL +=	/usr/bin/gtar
REQUIRED_TOOL +=	/usr/bin/gzip 
REQUIRED_TOOL +=	/usr/bin/ksh93
REQUIRED_TOOL +=	/usr/bin/ld
REQUIRED_TOOL +=	/usr/bin/mkdir
REQUIRED_TOOL +=	/usr/bin/python2.4
REQUIRED_TOOL +=	/usr/bin/python2.6
REQUIRED_TOOL +=	/usr/bin/rm
REQUIRED_TOOL +=	/usr/bin/sed
REQUIRED_TOOL +=	/usr/bin/sort
REQUIRED_TOOL +=	/usr/bin/touch
REQUIRED_TOOL +=	/usr/lib/python2.4/pycc
REQUIRED_TOOL +=	/usr/lib/python2.6/pycc
REQUIRED_TOOL +=	$(SPRO_ROOT)/bin/cc

REQUIRED_FILE +=	/lib/libc.so
REQUIRED_FILE +=	/usr/include/ctype.h
REQUIRED_FILE +=	/usr/include/cups/adminutil.h
REQUIRED_FILE +=	/usr/include/cups/cups.h
REQUIRED_FILE +=	/usr/include/cups/language.h
REQUIRED_FILE +=	/usr/include/cups/ppd.h
REQUIRED_FILE +=	/usr/include/iconv.h
REQUIRED_FILE +=	/usr/include/locale.h
REQUIRED_FILE +=	/usr/include/python2.4/Python.h
REQUIRED_FILE +=	/usr/include/python2.6/Python.h
REQUIRED_FILE +=	/usr/include/stdarg.h
REQUIRED_FILE +=	/usr/include/stdbool.h
REQUIRED_FILE +=	/usr/include/stdio.h
REQUIRED_FILE +=	/usr/include/stdlib.h
REQUIRED_FILE +=	/usr/include/string.h
REQUIRED_FILE +=	/usr/include/unistd.h
REQUIRED_FILE +=	/usr/include/wchar.h
REQUIRED_FILE +=	/usr/include/wctype.h
REQUIRED_FILE +=	/usr/lib/libc.so
REQUIRED_FILE +=	/usr/lib/libcups.so
REQUIRED_FILE +=	/usr/lib/libpython2.4.so.1.0
REQUIRED_FILE +=	/usr/lib/libpython2.6.so

include ../../make-rules/depend.mk
