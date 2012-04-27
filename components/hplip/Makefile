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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         hplip
COMPONENT_VERSION=      3.10.9
COMPONENT_PROJECT_URL=	http://hplipopensource.com/hplip-web/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:1d34630084eccfcc80c08065becdf9313fd8f5a09a4cf523dbd9d3ec724206b9
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/hplip/files/hplip/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# We need to be able to return from void functions
CC += $(studio_FEATURES_EXTENSIONS)
CXX += $(studio_FEATURES_EXTENSIONS) $(studio_NORUNPATH) $(studio_LIBRARY_NONE)

ROOTPPDCACHE =  $(PROTO_DIR)/usr/lib/lp/caches/SUNWhpijs.cache

# configure(1) options to use
CONFIGURE_OPTIONS +=	--localedir=$(CONFIGURE_LOCALEDIR)
CONFIGURE_OPTIONS +=	--disable-pp-build
CONFIGURE_OPTIONS +=	--disable-gui-build

CONFIGURE_ENV +=	LDFLAGS=" -lnsl"

HPLIP_VARIANT = $(BUILD_DIR)/$(MACH32)-hplip
HPIJS_VARIANT = $(BUILD_DIR)/$(MACH32)-hpijs

VARIANTS = $(HPLIP_VARIANT) $(HPIJS_VARIANT)

# We build two variants: for the CUPS/SANE support
# and for the HPIJS only support

# use these options for the CUPS/SANE support
$(HPLIP_VARIANT)/.built: CONFIGURE_OPTIONS += --with-hpppddir=/usr/share/cups/model/SUNWhplip
$(HPLIP_VARIANT)/.built: CONFIGURE_OPTIONS += --enable-fax-build
$(HPLIP_VARIANT)/.built: CONFIGURE_OPTIONS += --disable-udev-acl-rules
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

install: COMPONENT_INSTALL_ENV += halpredir=/etc/hal/fdi/preprobe/10osvendor

COMPONENT_INSTALL_ARGS += -e

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Generate configuration scripts
$(HPLIP_VARIANT)/.built: COMPONENT_PREP_ACTION = \
		(cd $(@D) ; autoconf )

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

#
# Since it looks like you can't build HPLIP with both HPIJS and CUPS support
# and seperate the HPIJS and CUPS PPD data, we need to replicate the code and
# build it twice.  Once for the HPIJS support used by LP and once for the rest
# of the support used for CUPS and SANE.
#
build: $(VARIANTS:%=%/.built)

install: $(VARIANTS:%=%/.installed)
	$(RM) $(ROOTPPDCACHE)
	$(MKDIR) $(PROTO_DIR)/usr/lib/lp/caches
	($(ENV) VER="$(BUILD_DIR)/$(MACH32)-hpijs" \
		PPDSRC="$(PROTO_DIR)/usr/share/ppd/SUNWhpijs" \
		DONOTINSTALL="/dev/null" \
		CACHE="$(ROOTPPDCACHE)" \
		IPATH="/usr/share/ppd/$(BUILD_DIR)/" \
		$(KSH93) cache.ksh)

# empty test target
test:	$(NO_TESTS)

include ../../make-rules/depend.mk
