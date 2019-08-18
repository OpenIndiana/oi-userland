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
# Copyright 2019 Andreas Grueninger, Grueninger GmbH, (grueni) 
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=   libqb
COMPONENT_VERSION=  1.0.5
COMPONENT_FMRI= library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_PROJECT_URL=  https://github.com/ClusterLabs/libqb
COMPONENT_SRC=    $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:89fe0c743e5be15f2fa25849f107df41cb144928259752d5c797c13644eba6b1
COMPONENT_ARCHIVE_URL=  \
  https://github.com/ClusterLabs/libqb/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= LGPLv2
COMPONENT_SUMMARY= libqb is a library providing high performance logging, tracing, ipc, and poll.

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

unexport SHELLOPTS

CFLAGS += -DNAME_MAX=255 -DHOST_NAME_MAX=255 -I/usr/include  -I/usr/include/heartbeat \
				 	-lsocket -lnsl -ldladm -lssp_nonshared -lssp -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-socket-dir=/var/run/hacluster
CONFIGURE_OPTIONS += --enable-slow-tests
CONFIGURE_OPTIONS += --disable-rpath

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

COMPONENT_PREP_ACTION=(cd $(@D); $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) autogen.sh)

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D)) 

COMPONENT_TEST_TARGETS = check

#
# Please note for the target test 
#    /var/run/hacluster must exist and must be writable for the build user
#

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
