#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Adam Stevko. All rights reserved.
# Copyright 2011 Andreas Wacknitz. All rights reserved.
#

BUILD_BITS=		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=   libstatgrab
COMPONENT_VERSION=  0.92
COMPONENT_VERSION2=	$(subst .,_,$(COMPONENT_VERSION))
COMPONENT_FMRI= library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_PROJECT_URL=  https://libstatgrab.org/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5bf1906aff9ffc3eeacf32567270f4d819055d8386d98b9c8c05519012d5a196
COMPONENT_ARCHIVE_URL=  https://github.com/libstatgrab/libstatgrab/releases/download/LIBSTATGRAB_$(COMPONENT_VERSION2)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2
COMPONENT_SUMMARY= libstatgrab is a library that provides cross platform access to statistics about the system on which it's run.

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV.64    += lt_cv_sys_lib_dlsearch_path_spec="/lib/$(MACH64) /usr/lib/$(MACH64)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
