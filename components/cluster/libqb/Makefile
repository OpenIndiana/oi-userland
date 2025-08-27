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
# Copyright 2025 Klaus Ziegler
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libqb
COMPONENT_VERSION=      1.0.6
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      libqb is a library providing high performance logging, tracing, ipc, and polling.
COMPONENT_PROJECT_URL=  https://github.com/ClusterLabs/libqb
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:08e63e1213ee0582368daea8bebe5798b69050f43d209af0e501d7b43823ba9a
COMPONENT_ARCHIVE_URL=  \
	https://github.com/ClusterLabs/libqb/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -DNAME_MAX=255 -DHOST_NAME_MAX=255 \
	-I/usr/include  -I/usr/include/heartbeat \
	-lsocket -lnsl -ldladm -lssp_nonshared -lssp \
	-D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS \
	-Wno-incompatible-pointer-types

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --with-socket-dir=/var/run/hacluster
CONFIGURE_OPTIONS += --enable-slow-tests
CONFIGURE_OPTIONS += --disable-dependency-tracking

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

COMPONENT_PREP_ACTION= ( cd $(@D); $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

#
# Please note for the target test 
#    /var/run/hacluster must exist and must be writable for the build user
#

# Manually added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
