#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
#

#
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

# parfait fails to compile us (22221056)
export PARFAIT_BUILD=no

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openvswitch
COMPONENT_VERSION=	2.3.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d6d96e45fd9c070cc2696a4a09b4cc4b48dd7fc367c0455725d00f7daa343bf0
COMPONENT_PROJECT_URL=  http://openvswitch.org/
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/openvswitch
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION) 

TPNO=			21407

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk

# Depends on S12-only changes in ON to build.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files
PKG_PROTO_DIRS += $(BUILD_DIR_64)

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_PRE_CONFIGURE_ACTION += \
    ($(LN) -fs $(COMPONENT_DIR)/files/include/solaris $(SOURCE_DIR)/include/solaris; \
    $(LN) -fs $(COMPONENT_DIR)/files/lib/* $(SOURCE_DIR)/lib; \
    cd $(SOURCE_DIR); $(SOURCE_DIR)/boot.sh)

COMPILER =	gcc

CONFIGURE_PREFIX	= /usr/lib/ovs

CONFIGURE_OPTIONS	+= --mandir=/usr/share/man
CONFIGURE_OPTIONS	+= --localstatedir=/var/run/ovs
CONFIGURE_OPTIONS	+= --bindir=/usr/sbin
CONFIGURE_OPTIONS	+= --sbindir=/usr/lib/ovs
CONFIGURE_OPTIONS	+= --with-logdir=/var/log/ovs
CONFIGURE_OPTIONS	+= --with-rundir=/var/run/ovs/
CONFIGURE_OPTIONS	+= --with-dbdir=/var/lib/ovs/etc
CONFIGURE_OPTIONS	+= --datarootdir=/usr/lib/ovs/share

# Enable aslr for this component
ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_PRE_BUILD_ACTION = \
    ($(LN) -fs $(COMPONENT_DIR)/files/include/solaris $(SOURCE_DIR)/include/solaris)

COMPONENT_TEST_TRANSFORMS += \
    '-e "s|^tests/pki/test-req.pem.*||g" ' \
    '-e "s|^tests/pki/test2-req.pem.*||g" ' \
    '-e "s|^.*fingerprint.*||g" '

COMPONENT_TEST_ENV += PATH="$(GNUBIN):$(PATH)"

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:	$(SYSTEM_TESTS_NOT_IMPLEMENTED)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/rad
REQUIRED_PACKAGES += system/management/rad/client/rad-c
REQUIRED_PACKAGES += system/management/rad/client/rad-python
REQUIRED_PACKAGES += system/network
