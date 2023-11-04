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
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gammu
COMPONENT_VERSION=	1.37.4
COMPONENT_REVISION=	10
COMPONENT_SUMMARY=	Command line utility to control your phone
COMPONENT_PROJECT_URL=	https://wammu.eu/gammu/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=	https://dl.cihar.com/gammu/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:b0fd316f09e862a732aa9ad6fd2f49f09ad69307fd05f50e58f40d33c15deea0
COMPONENT_FMRI=		utility/gammu
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(MYSQL_BINDIR):$(PG_BINDIR):$(PATH.gnu)

# Cmake makefiles somehow loose -R/path/to/lib
LDFLAGS += -L$(MYSQL_LIBDIR) -R$(MYSQL_LIBDIR)
LDFLAGS += -L$(PG_LIBDIR) -R$(PG_LIBDIR)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CMAKE_OPTIONS += -DBUILD_PYTHON=$(PYTHON)
CMAKE_OPTIONS += -DPYTHON_EXECUTABLE=$(PYTHON)
CMAKE_OPTIONS += -DWITH_BACKUP=OFF
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DINSTALL_GNAPPLET=OFF

# Build dependencies
REQUIRED_PACKAGES += utility/bash-completion
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += database/mariadb-106/library
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
