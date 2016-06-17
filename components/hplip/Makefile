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

COMMON_TARGETS= no
include $(WS_MAKE_RULES)/common.mk

PKG_OPTIONS += -I $(COMPONENT_DIR)

# We need to be able to return from void functions
CFLAGS.studio += $(studio_FEATURES_EXTENSIONS)
CXXFLAGS.studio += $(studio_FEATURES_EXTENSIONS) 
CXXFLAGS.studio += $(studio_CXXLIB_CSTD) 

ROOTPPDCACHE =  $(PROTOUSRLIBDIR)/lp/caches/SUNWhpijs.cache

# common configure options
CONFIGURE_OPTIONS +=	--localedir=$(CONFIGURE_LOCALEDIR)
CONFIGURE_OPTIONS +=	--disable-pp-build
CONFIGURE_OPTIONS +=	--disable-gui-build
CONFIGURE_OPTIONS +=	--disable-qt4
# bye, bye SANE backends
CONFIGURE_OPTIONS +=	--disable-scan-build
CONFIGURE_OPTIONS +=	am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_OPTIONS +=	am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

ifeq ($(OS_VERSION),5.11)
LDFLAGS += -lnsl
endif

HPLIP_VARIANT = $(BUILD_DIR)/$(MACH32)-hplip
HPIJS_VARIANT = $(BUILD_DIR)/$(MACH32)-hpijs

VARIANTS = $(HPLIP_VARIANT) $(HPIJS_VARIANT)

# We build two variants: for the CUPS support
# and for the HPIJS only support

# use these options for the CUPS support
$(HPLIP_VARIANT)/.configured: CONFIGURE_OPTIONS += --with-hpppddir=$(USRSHAREDIR)/cups/model/SUNWhplip
$(HPLIP_VARIANT)/.configured: CONFIGURE_OPTIONS += --enable-libusb01_build
$(HPLIP_VARIANT)/.configured: CONFIGURE_OPTIONS += --enable-fax-build
$(HPLIP_VARIANT)/.configured: CONFIGURE_OPTIONS += --enable-hpcups-install
$(HPLIP_VARIANT)/.configured: CONFIGURE_OPTIONS += --disable-new-hpcups
$(HPLIP_VARIANT)/.configured: CONFIGURE_OPTIONS += --enable-cups-drv-install

# use these options for the HPIJS only support
$(HPIJS_VARIANT)/.configured: CONFIGURE_OPTIONS += --enable-foomatic-ppd-install
$(HPIJS_VARIANT)/.configured: CONFIGURE_OPTIONS += --with-hpppddir=$(USRSHAREDIR)/ppd/SUNWhpijs/HP
$(HPIJS_VARIANT)/.configured: CONFIGURE_OPTIONS += --disable-cups-drv-install
$(HPIJS_VARIANT)/.configured: CONFIGURE_OPTIONS += --disable-hpcups-install
$(HPIJS_VARIANT)/.configured: CONFIGURE_OPTIONS += --disable-doc-build
$(HPIJS_VARIANT)/.configured: CONFIGURE_OPTIONS += --enable-hpijs-only-build
$(HPIJS_VARIANT)/.configured: CONFIGURE_OPTIONS += --enable-hpijs-install

COMPONENT_INSTALL_ARGS += -e

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Generate configuration scripts
$(HPLIP_VARIANT)/.built: COMPONENT_PREP_ACTION = \
		(cd $(@D) ; autoconf )

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
		/usr/bin/sed -e '1,1s&^#!.*python[:blank:]\{0,\}$$&#!$(PYTHON.$(PYTHON_VERSION))&' \
		   $$file > $$file.pyverset ; \
	   done
	find $(PROTO_DIR) -name \*.py.pyverset -print0 | \
	   while IFS= read -r -d $$'\0' file; do \
		$(MV) $$file `echo $$file | sed -e 's/[.]pyverset$$//'` ; \
	   done
	$(PYTHON.$(PYTHON_VERSION)) -m compileall $(PROTO_DIR)/usr/share/hplip/
	$(TOUCH) $@

# Since it looks like you can't build HPLIP with both HPIJS and CUPS support
# and seperate the HPIJS and CUPS PPD data, we need to replicate the code and
# build it twice.  Once for the HPIJS support used by LP and once for the rest
# of the support used for CUPS
#
configure: $(VARIANTS:%=%/.configured)

build: $(VARIANTS:%=%/.built)

install: $(BUILD_DIR)/.allvariantsinstalled

# empty test target
test:	$(NO_TESTS)

system-test:    $(NO_TESTS)

# We need one Net-SNMP library on 12, the other on 11, so list both.
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/usb/libusb
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += system/management/snmp/net-snmp-57
