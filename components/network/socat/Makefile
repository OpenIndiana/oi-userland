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

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		socat
COMPONENT_VERSION=	1.7.3.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:360c9d08b47b446cd88ee2f3465a19177c4d2099fc92d20e1c10b5cd51a27ebf
COMPONENT_PROJECT_URL=	http://www.dest-unreach.org/socat/
COMPONENT_ARCHIVE_URL=	http://www.dest-unreach.org/socat/download/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# For the test target
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_TEST_TARGETS=	test

# Disable colors in test output
COMPONENT_TEST_ENV += TERM=

COMPONENT_TEST_TRANSFORMS= \
	'-ne "s/\.\.\. .* OK/\.\.\. OK/"' \
	'-ne "s/\.\.\. .* NO RESULT/\.\.\. NO RESULT/"' \
	'-ne "s/\.\.\. .* timed out/\.\.\. timed out/"' \
	'-ne "/^test/p"' \
	'-ne "/^summary/p"' \
	'-ne "/^FAILED/p"'

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
