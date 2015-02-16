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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		MySQL-python
COMPONENT_VERSION=	1.2.2
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/mysql-python
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:f4133b81e65c7b94a5921ff6a0e7bdbfb622f2a70473673103cb17d5a5be807a
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/mysql-python/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/mysql

TPNO=			9533

# Syntax issues: not Python 3 ready.
PYTHON_VERSIONS=	2.7 2.6

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

PATH_32=/usr/mysql/5.5/bin/$(MACH32):/usr/bin:$(SPRO_VROOT)/bin
PATH_64=/usr/mysql/5.5/bin:/usr/bin:$(SPRO_VROOT)/bin
COMPONENT_BUILD_ENV   += PATH=$(PATH_$(BITS)):$(PATH)
COMPONENT_INSTALL_ENV += PATH=$(PATH_$(BITS)):$(PATH)

CFLAGS_32=	-L/usr/mysql/5.5/lib -R/usr/mysql/5.5/lib
CFLAGS_64=	-L/usr/mysql/5.5/lib/$(MACH64) -R/usr/mysql/5.5/lib/$(MACH64)
CFLAGS +=	$(CFLAGS_$(BITS))

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)


REQUIRED_PACKAGES += database/mysql-55
REQUIRED_PACKAGES += database/mysql-55/library
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
