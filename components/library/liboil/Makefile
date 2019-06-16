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
# Copyright 2014 Alexander Pyhalov
# Copyright 2019 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		liboil
COMPONENT_VERSION=	0.3.17
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Library of Optimized Inner Loops 
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:105f02079b0b50034c759db34b473ecb5704ffa20a5486b60a8b7698128bfc69
COMPONENT_ARCHIVE_URL= \
  http://liboil.freedesktop.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.gnome.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION += ( cd $(@D) &&\
	aclocal -I./m4 &&\
	autoheader &&\
	automake -a -c -f &&\
	autoconf )

# Without this some tests are failing
gcc_OPT=-O2

# This is needed to find mapfile
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc

unexport SHELLOPTS

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
