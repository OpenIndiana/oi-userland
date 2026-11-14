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
# Copyright 2026 Ignacio Soriano
#

BUILD_STYLE=justmake
BUILD_BITS=NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mac-sensors
COMPONENT_VERSION=	1.2
COMPONENT_SUMMARY=	Temperatures and fans of Intel Macs and other machines
COMPONENT_PROJECT_URL=	https://github.com/isoriano1968/mac-sensors
COMPONENT_FMRI=		desktop/system-monitor/mac-sensors
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	\
	$(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:ce66a3756af355746953159f86416611ab0a6d288958e6da35d19ff11f901c12
COMPONENT_LICENSE=	CDDL-1.0
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_INSTALL_ARGS +=	PREFIX=$(USRDIR)
COMPONENT_INSTALL_ARGS +=	PYTHON=$(PYTHON)

# The app runs smcstat(8) of driver/sensor/applesmc on Intel Macs and reads
# the ksensors of driver/cpu/sensor; neither is linked, so pkgdepend cannot
# see them; both are optional (other machines, the drivers outside OI).
# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/pycairo
REQUIRED_PACKAGES.python += library/python/pygobject
REQUIRED_PACKAGES.python += runtime/python
