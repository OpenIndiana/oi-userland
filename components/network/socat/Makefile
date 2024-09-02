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
# Copyright (c) 2012, Adam Stevko <adam.stevko@gmail.com> 
# Copyright (c) 2018, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		socat
COMPONENT_VERSION=	1.8.0.1
COMPONENT_SUMMARY=	socat is a larger and more flexible variant of netcat
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:6a283565db7cf86292c6f70504c58abb03e29888adeed5a6c5f3457e803c1b81
COMPONENT_PROJECT_URL=	http://www.dest-unreach.org/socat/
COMPONENT_ARCHIVE_URL=	http://www.dest-unreach.org/socat/download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/common.mk

CFLAGS += $(XPG6MODE)
LDFLAGS += -L$(OPENSSL_LIBDIR)

CONFIGURE_OPTIONS += --enable-openssl_base=$(OPENSSL_PREFIX)

# For the test target
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

COMPONENT_TEST_TARGETS=	test

# Disable colors in test output
COMPONENT_TEST_ENV += TERM=

# Note that some tests fail because of missing privileges ("not root")
COMPONENT_TEST_TRANSFORMS= \
	'-ne "s/\.\.\. .* OK/\.\.\. OK/"' \
	'-ne "s/\.\.\. .* NO RESULT/\.\.\. NO RESULT/"' \
	'-ne "s/\.\.\. .* timed out/\.\.\. timed out/"' \
	'-ne "/^test/p"' \
	'-ne "/^summary/p"' \
	'-ne "/^CANT/p"' \
	'-ne "/^FAILED/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
