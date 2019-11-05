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
# Copyright 2016 Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		netperf
COMPONENT_VERSION=	2.7.0
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=	Netperf is a benchmark that can be used to measure the performance of many different types of networking.
COMPONENT_PROJECT_URL=	http://www.netperf.org/netperf/
COMPONENT_FMRI=		benchmark/netperf
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/HewlettPackard/netperf/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:4569bafa4cca3d548eb96a486755af40bd9ceb6ab7c6abd81cc6aa4875007c4e
COMPONENT_LICENSE=	HP

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

CFLAGS+= -std=gnu89

CONFIGURE_OPTIONS+= --enable-histogram
CONFIGURE_OPTIONS+= --enable-dirty
CONFIGURE_OPTIONS+= --enable-demo
CONFIGURE_OPTIONS+= --enable-unixdomain
CONFIGURE_OPTIONS+= --enable-dlpi
CONFIGURE_OPTIONS+= --enable-omni
CONFIGURE_OPTIONS+= --enable-xti
CONFIGURE_OPTIONS+= --enable-exs
CONFIGURE_OPTIONS+= --enable-sctp
CONFIGURE_OPTIONS+= --enable-intervals
CONFIGURE_OPTIONS+= --enable-spin
CONFIGURE_OPTIONS+= --enable-burst
CONFIGURE_OPTIONS+= --enable-cpuutil=kstat

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
