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
# Copyright 2016 John Smith. All rights reserved.
#


include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libconfig
COMPONENT_VERSION=	1.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://github.com/hyperrealm/libconfig
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:18739792eb463d73525d7aea9b0a48b14106fae1cfec09aedc668d8c1079adf1
COMPONENT_ARCHIVE_URL=	https://github.com/hyperrealm/libconfig/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libconfig
COMPONENT_SUMMARY=	C/C++ library for processing configuration files
COMPONENT_CLASSIFICATION= System/Libraries

COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_LICENSE=	GPLv2


include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D)  && \
				rm -f lib/scanner.{c,h} &&\
				autoreconf -f -i)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D) )

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
