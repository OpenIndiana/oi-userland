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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gammu
COMPONENT_VERSION=	1.37.4
COMPONENT_PROJECT_URL=	https://wammu.eu/gammu/
COMPONENT_SUMMARY=	Command line utility to control your phone
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=	https://dl.cihar.com/gammu/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
    sha256:b0fd316f09e862a732aa9ad6fd2f49f09ad69307fd05f50e58f40d33c15deea0
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_FMRI=		utilities/gammu
COMPONENT_CLASSIFICATION=	Applications/System Utilities

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(MYSQL_HOME)/bin:$(PG_HOME)/bin:/usr/gnu/bin:/usr/bin

# Cmake makefiles somehow loose -R/path/to/lib
LDFLAGS.32 += -L$(MYSQL_HOME)/lib -R$(MYSQL_HOME)/lib
LDFLAGS.32 += -L$(PG_HOME)/lib -R$(PG_HOME)/lib
LDFLAGS.64 += -L$(MYSQL_HOME)/lib/$(MACH64) -R$(MYSQL_HOME)/lib/$(MACH64)
LDFLAGS.64 += -L$(PG_HOME)/lib/$(MACH64) -R$(PG_HOME)/lib/$(MACH64)
LDFLAGS += $(LDFLAGS.$(BITS))

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CMAKE_OPTIONS +=	-DBUILD_PYTHON=$(PYTHON)
CMAKE_OPTIONS +=	-DPYTHON_EXECUTABLE=$(PYTHON)
CMAKE_OPTIONS +=	-DWITH_BACKUP=OFF
CMAKE_OPTIONS +=	-DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS +=	-DINSTALL_GNAPPLET=OFF

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/mariadb-55/library
REQUIRED_PACKAGES += database/postgres-93/library
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnu-libiconv
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
