#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# CDDL HEADER END
#
# Copyright (c) 2014, David Hoeppner. All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		datamash
COMPONENT_VERSION=	1.8
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	performs numeric, textual and statistical operations on data files
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/datamash/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7ad97e8c7ef616dd03aa5bd67ae24c488272db3e7d1f5774161c18b75f29f6fd
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	    text/datamash
COMPONENT_CLASSIFICATION=   System/Text Tools      
COMPONENT_LICENSE=      GPLv3

include $(WS_MAKE_RULES)/common.mk

# Provide location for openssl 3.1 headers/libraries
CFLAGS += -I$(OPENSSL_INCDIR)
LDFLAGS  += -L$(OPENSSL_LIBDIR)

CONFIGURE_OPTIONS += --with-openssl=yes

COMPONENT_TEST_ENV += RUN_EXPENSIVE_TESTS=yes

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
