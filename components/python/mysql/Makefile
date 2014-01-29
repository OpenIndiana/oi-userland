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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

PATH_32=/usr/mysql/5.5/bin/$(MACH32):/usr/bin
PATH_64=/usr/mysql/5.5/bin:/usr/bin
COMPONENT_BUILD_ENV   += PATH=$(PATH_$(BITS))
COMPONENT_INSTALL_ENV += PATH=$(PATH_$(BITS))

COMPONENT_NAME=		MySQL-python
COMPONENT_VERSION=	1.2.2
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/mysql-python
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:f4133b81e65c7b94a5921ff6a0e7bdbfb622f2a70473673103cb17d5a5be807a
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/mysql-python/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/mysql

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

CFLAGS_32=	-L/usr/mysql/5.5/lib -R/usr/mysql/5.5/lib
CFLAGS_64=	-L/usr/mysql/5.5/lib/$(MACH64) -R/usr/mysql/5.5/lib/$(MACH64)
CFLAGS +=	$(CFLAGS_$(BITS))

# Needed to get around a broken /usr/lib/python2.7/config/Makefile
# See CR #16837431.
LD=$(CC)
LDSHARED=$(CC) -G
PYTHON_ENV += CC="$(CC)"
PYTHON_ENV += LDSHARED="$(LDSHARED)"
PYTHON_ENV += LD="$(LD)"
PYTHON_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += $(PYTHON_ENV)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
