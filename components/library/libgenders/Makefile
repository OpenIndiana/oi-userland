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
# Copyright (c) 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		genders
COMPONENT_VERSION=	1.22
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://github.com/chaos/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	libgenders - configuration database for clusters
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0ff292825a29201106239c4d47d9ce4c6bda3f51c78c0463eb2634ecc337b774
COMPONENT_ARCHIVE_URL=	https://github.com/chaos/$(COMPONENT_NAME)/releases/download/$(COMPONENT_NAME)-$(subst .,-,$(COMPONENT_VERSION))-$(COMPONENT_REVISION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =	library/$(COMPONENT_NAME)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION =	System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D) && \
	 cd $(@D) && \
	 aclocal -I config && \
	 libtoolize --copy && \
	 autoheader && \
	 automake --add-missing --copy --gnu && \
	 autoconf --warnings=all )

CONFIGURE_OPTIONS+= --without-java-extensions
CONFIGURE_OPTIONS+= --with-non-shortened-hostnames

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
