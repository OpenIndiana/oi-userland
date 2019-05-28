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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         hplip
COMPONENT_VERSION=      3.19.5
COMPONENT_PROJECT_URL=	http://hplipopensource.com/hplip-web/index.html
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:8f5ac056c1a778b78511588f427072078703d683dfe5af6214ba179e89b453e1
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/hplip/files/hplip/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_OPTIONS += -I $(COMPONENT_DIR)

# Enable ASLR for this component
# ASLR_MODE = $(ASLR_ENABLE)

# We need to be able to return from void functions
# CC += $(studio_FEATURES_EXTENSIONS)
# CXX += $(studio_FEATURES_EXTENSIONS) $(studio_NORUNPATH) $(studio_CXXLIB_CSTD)

ROOTPPDCACHE =  $(PROTO_DIR)/usr/lib/lp/caches/SUNWhpijs.cache

# build with the distribution default libjpeg
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

# common configure options
CONFIGURE_OPTIONS +=	--localedir=$(CONFIGURE_LOCALEDIR)
CONFIGURE_OPTIONS +=	--disable-pp-build
CONFIGURE_OPTIONS +=	--disable-gui-build
CONFIGURE_OPTIONS +=	--disable-qt4
CONFIGURE_OPTIONS +=	am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_OPTIONS +=	am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV +=	PYTHON=$(PYTHON)
# for createPPD.sh
CONFIGURE_ENV +=	"ARCH=$(BITS)"

LDFLAGS+= -lnsl

HPLIP_VARIANT = $(BUILD_DIR)/$(MACH32)-hplip
HPIJS_VARIANT = $(BUILD_DIR)/$(MACH32)-hpijs

VARIANTS = $(HPLIP_VARIANT) $(HPIJS_VARIANT)

# We build two variants: for the CUPS/SANE support
# and for the HPIJS only support

# use these options for the CUPS/SANE support
$(HPLIP_VARIANT)/.built: CONFIGURE_OPTIONS += --with-hpppddir=/usr/share/cups/model/SUNWhplip
$(HPLIP_VARIANT)/.built: CONFIGURE_OPTIONS += --enable-libusb01_build
$(HPLIP_VARIANT)/.built: CONFIGURE_OPTIONS += --enable-fax-build
$(HPLIP_VARIANT)/.built: CONFIGURE_OPTIONS += --enable-hpcups-install
$(HPLIP_VARIANT)/.built: CONFIGURE_OPTIONS += --disable-new-hpcups
$(HPLIP_VARIANT)/.built: CONFIGURE_OPTIONS += --enable-cups-drv-install

# use these options for the HPIJS only support
$(HPIJS_VARIANT)/.built: CONFIGURE_OPTIONS += --enable-foomatic-ppd-install
$(HPIJS_VARIANT)/.built: CONFIGURE_OPTIONS += --with-hpppddir=/usr/share/ppd/SUNWhpijs/HP
$(HPIJS_VARIANT)/.built: CONFIGURE_OPTIONS += --disable-cups-drv-install
$(HPIJS_VARIANT)/.built: CONFIGURE_OPTIONS += --disable-hpcups-install
$(HPIJS_VARIANT)/.built: CONFIGURE_OPTIONS += --disable-doc-build
$(HPIJS_VARIANT)/.built: CONFIGURE_OPTIONS += --enable-hpijs-only-build
$(HPIJS_VARIANT)/.built: CONFIGURE_OPTIONS += --enable-hpijs-install

COMPONENT_INSTALL_ARGS += -e

# for install-data libImageProcessor architecture selection
COMPONENT_INSTALL_ENV  +=  "ARCH=$(BITS)"

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Generate configuration scripts
$(HPLIP_VARIANT)/.built: COMPONENT_PREP_ACTION = \
		(cd $(@D) ; autoconf )

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

$(BUILD_DIR)/.allvariantsinstalled: $(VARIANTS:%=%/.installed)
	$(RM) $(ROOTPPDCACHE)
	$(MKDIR) $(PROTO_DIR)/usr/lib/lp/caches
	($(ENV) VER="$(BUILD_DIR)/$(MACH32)-hpijs" \
		PPDSRC="$(PROTO_DIR)/usr/share/ppd/SUNWhpijs" \
		DONOTINSTALL="/dev/null" \
		CACHE="$(ROOTPPDCACHE)" \
		IPATH="/usr/share/ppd/$(BUILD_DIR)/" \
		$(KSH93) cache.ksh)
	# set version of python interpreter to calm the pkglint
	find $(PROTO_DIR) -name \*.py -print0 | \
	   while IFS= read -r -d $$'\0' file; do \
		/usr/bin/sed -e '1,1s&^#!.*python[:blank:]\{0,\}$$&#!$(PYTHON)&' \
		   $$file > $$file.pyverset ; \
	   done
	find $(PROTO_DIR) -name \*.py.pyverset -print0 | \
	   while IFS= read -r -d $$'\0' file; do \
		$(MV) $$file `echo $$file | sed -e 's/[.]pyverset$$//'` ; \
	   done
	$(PYTHON) -m compileall $(PROTO_DIR)/usr/share/hplip/
	$(TOUCH) $@

PKG_MACROS +=	PYVER=$(PYTHON_VERSION)
#
# Since it looks like you can't build HPLIP with both HPIJS and CUPS support
# and seperate the HPIJS and CUPS PPD data, we need to replicate the code and
# build it twice.  Once for the HPIJS support used by LP and once for the rest
# of the support used for CUPS and SANE.
#
build: $(VARIANTS:%=%/.built)

install: $(BUILD_DIR)/.allvariantsinstalled

# empty test target
test:	$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/$(JPEG_IMPLEM)
REQUIRED_PACKAGES += image/scanner/xsane/sane-backends
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/usb/libusb
REQUIRED_PACKAGES += system/management/snmp/net-snmp
