#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021 Gary Mills
# Copyright 2016 Alexander Pyhalov
#

BUILD_BITS=		64
USE_OPENSSL11=	yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fio
COMPONENT_VERSION=	3.30
COMPONENT_SUMMARY=	Flexible I/O tester
COMPONENT_FMRI=		system/test/fio
COMPONENT_CLASSIFICATION=	Development/System
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:93998f838f72f871b36d60da132fcc3abaadd7b14c628ec95ee4092f2d277aed
COMPONENT_PROJECT_URL=	http://freecode.com/projects/fio
COMPONENT_ARCHIVE_URL=	https://brick.kernel.dk/snaps/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

# Specify the python version used by this build
PYTHON_VERSION=		3.9

CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --cc="$(CC)"
CONFIGURE_OPTIONS += --extra-cflags="$(CFLAGS)"

COMPONENT_TEST_TARGETS=	test

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/six-39
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
