#
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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         hplip
COMPONENT_VERSION=      3.15.7
TPNO=			24589
COMPONENT_ARCHIVE_HASH= sha256:d310903048f3600f93422e5a8c39ddd682511e0849cd9abc5e943f9a10bdd49d
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/hplip/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://hplipopensource.com/hplip-web/index.html

include $(WS_MAKE_RULES)/common.mk

PKG_OPTIONS += -I $(COMPONENT_DIR)

# We need to be able to return from void functions
CFLAGS.studio += $(studio_FEATURES_EXTENSIONS)
CXXFLAGS.studio += $(studio_FEATURES_EXTENSIONS) 
CXXFLAGS.studio += $(studio_CXXLIB_CSTD) 
CXXFLAGS.studio += -std=sun03

CONFIGURE_OPTIONS +=	--localedir=$(CONFIGURE_LOCALEDIR)
CONFIGURE_OPTIONS +=	--with-hpppddir=$(USRSHAREDIR)/cups/model/hplip
ifeq ($(OS_VERSION),5.11)
CONFIGURE_OPTIONS +=	--enable-libusb01_build
endif
CONFIGURE_OPTIONS +=	--enable-fax-build
CONFIGURE_OPTIONS +=	--enable-hpcups-install
CONFIGURE_OPTIONS +=	--disable-new-hpcups
CONFIGURE_OPTIONS +=	--enable-cups-drv-install
CONFIGURE_OPTIONS +=	--disable-pp-build
CONFIGURE_OPTIONS +=	--disable-gui-build
CONFIGURE_OPTIONS +=	--disable-qt4
CONFIGURE_OPTIONS +=	PYTHON=$(PYTHON.$(PYTHON_VERSION))
CONFIGURE_OPTIONS +=	am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_OPTIONS +=	am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"
# bye, bye SANE backends
CONFIGURE_OPTIONS +=	--disable-scan-build

ifeq ($(OS_VERSION),5.11)
LDFLAGS += -lnsl
endif

COMPONENT_INSTALL_ARGS += -e

# Generate configuration scripts
COMPONENT_PREP_ACTION = (cd $(@D) ; autoconf )

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

PYTHON_SCRIPTS += $(PROTO_DIR)/usr/lib/cups/backend/hpfax
PYTHON_SCRIPTS += $(PROTO_DIR)/usr/lib/cups/filter/hpps
PYTHON_SCRIPTS += $(PROTO_DIR)/usr/lib/cups/filter/pstotiff
PYTHON_SCRIPTS += \
 $(shell nawk -F \= \
  ' $$1 ~ /^file.*path/ && $$2 ~ /.*\.py$$/ {print "$(PROTO_DIR)/"$$2;} ' \
  $(COMPONENT_DIR)/hplip.proto-objects)

# build .pyc's
COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON.$(PYTHON_VERSION)) -m compileall $(PROTO_DIR)/usr/share/hplip/

# empty test target
test:	$(NO_TESTS)

system-test:    $(NO_TESTS)

# libusb-1 is needed on S12; libusb is needed on S11, so list both.
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/usb/libusb
REQUIRED_PACKAGES += system/management/snmp/net-snmp
