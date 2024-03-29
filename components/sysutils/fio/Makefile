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

SINGLE_PYTHON_VERSION= yes
OPENSSL_VERSION= 3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fio
COMPONENT_VERSION=	3.36
COMPONENT_SUMMARY=	Flexible I/O tester
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:008ac147289450f557d66d3608d0b07f80d4ba6444dfb576153fb6536c16ef5e
COMPONENT_PROJECT_URL=	https://git.kernel.dk/cgit/fio/
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/snapshot/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/test/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/System
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --cc="$(CC)"
CONFIGURE_OPTIONS += --extra-cflags="$(CFLAGS)"

LDFLAGS += -L$(OPENSSL_LIBDIR.$(BITS))

CONFIGURE_ENV += CFLAGS="-I$(OPENSSL_INCDIR) $(CFLAGS)"

COMPONENT_TEST_TARGETS=	test

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/six
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
