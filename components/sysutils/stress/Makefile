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
# Copyright 2016 Adam Stevko. All rights reserved.
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	 	stress
COMPONENT_VERSION=	1.0.5
COMPONENT_FMRI=		benchmark/stress
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SUMMARY=	stress is a deliberately simple workload generator for POSIX systems. It imposes a configurable amount of CPU, memory, I/O, and disk stress on the system.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:1798e49ca365d928fb194ba1b8e8d1e09963b49e9edb0a78bcbba15750bb5027
COMPONENT_PROJECT_URL=	https://github.com/resurrecting-open-source-projects/stress
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/1.0.5.tar.gz
COMPONENT_LICENSE =	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(SOURCE_DIR) && ./autogen.sh )

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/^PASS:/p" ' \
        '-e "/=====/p" ' \
        '-e "/Testsuite/p" ' \
        '-e "/^\# TOTAL:/p" ' \
        '-e "/^\# PASS:/p" ' \
        '-e "/^\# SKIP:/p" ' \
        '-e "/^\# XFAIL:/p" ' \
        '-e "/^\# FAIL:/p" ' \
        '-e "/^\# XPASS:/p" ' \
        '-e "/^\# ERROR:/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
