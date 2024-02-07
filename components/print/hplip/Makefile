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
# Copyright (c) 2011, 2023, Oracle and/or its affiliates.
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         hplip
COMPONENT_VERSION=      3.22.10
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=		hplip - HP Linux Printing
COMPONENT_DESCRIPTION=  Support of HP InkJet, Laser printers for CUPS.
COMPONENT_PROJECT_URL=	https://hplipopensource.com/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:533c3f2f6b53e4163ded4fd81d1f11ae6162a0f6451bd5e62a8382d0c1366624
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= 		print/filter/hplip
COMPONENT_CLASSIFICATION=	System/Printing
COMPONENT_LICENSE=		GPLv2+ and MIT and BSD and IJG and Public Domain and GPLv2+ with exceptions and ISC

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# For autopyc transformation
PKG_MACROS += PYVER=$(PYTHON_VERSION)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

# build with the distribution default libjpeg
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

# -lnsl is needed for getdomainname
LDFLAGS += -lnsl

CONFIGURE_OPTIONS +=	--localedir=$(CONFIGURE_LOCALEDIR)
CONFIGURE_OPTIONS +=	--with-hpppddir=$(USRSHAREDIR)/cups/model/hplip
CONFIGURE_OPTIONS +=	--enable-new-hpcups
CONFIGURE_OPTIONS +=	--enable-cups-ppd-install
CONFIGURE_OPTIONS +=	--disable-gui-build
CONFIGURE_OPTIONS +=    --disable-imageProcessor-build
CONFIGURE_OPTIONS +=	PYTHON=$(PYTHON)
CONFIGURE_OPTIONS +=	am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_OPTIONS +=	am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"
# bye, bye SANE backends
CONFIGURE_OPTIONS +=	--disable-scan-build

CONFIGURE_CPPFLAGS += $(CC_PIC_ENABLE)

# Generate configuration scripts
COMPONENT_PREP_ACTION = ( cd $(@D) ; \
    libtoolize --force ; \
    aclocal ; \
    automake --foreign --add-missing ; \
    autoconf )

COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# Do not use transform to create standard ABI version tagged .so files from Python 3 ABI
PY3_CPYTHON_NAMING=\#

# Fix python script shebang
COMPONENT_POST_INSTALL_ACTION += \
	echo "Fixing python shebang..."; \
	ggrep -rlI -m1 '^\#!.*python' $(PROTO_DIR) | while read file; do \
		$(call PYTHON_SCRIPT_SHEBANG_FIX_FUNC,"$$file") \
	done;

# Set actual python version
COMPONENT_POST_INSTALL_ACTION += $(GSED) -i -e "s:\#!/usr/bin/env .*$$:\#!/usr/bin/python$(PYTHON_VERSION):" $(PROTOUSRLIBDIR)/cups/filter/psto* ;
# Pre-compile python source code
COMPONENT_POST_INSTALL_ACTION += $(PYTHON) -m compileall $(PROTO_DIR)/usr/share/hplip;

hplip.license:
	cat $(SOURCE_DIR)/copyright >$@

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += system/network/avahi
