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
# Copyright 2015 Aurelien Larcher
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xlock
COMPONENT_VERSION=	7.5
COMPONENT_REVISION=	2
COMPONENT_FMRI=		x11/xlock
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=	xlock - screen lock program
COMPONENT_SRC=		src
COMPONENT_PROJECT_URL=	https://github.com/oracle/solaris-userland/tree/master/components/x11/app/xlock/sun-src
COMPONENT_LICENSE=	MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ENV += INSTALL="$(INSTALL) -D"
COMPONENT_INSTALL_ENV += PREFIX=$(USRDIR)

COMPONENT_COMMON_ENV = CC=$(CC)
COMPONENT_COMMON_ENV+= CFLAGS="$(CFLAGS)"
COMPONENT_COMMON_ENV+= LDFLAGS="$(LDFLAGS)"

$(SOURCE_DIR)/.prep: $(MAKEFILE_PREREQ)
	$(TOUCH) $@

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
