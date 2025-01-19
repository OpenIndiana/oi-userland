#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
# Copyright 2025 Klaus Ziegler
#

BUILD_BITS= 64_and_32
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fontconfig
COMPONENT_VERSION=	2.16.0
COMPONENT_SUMMARY=	Fontconfig - Font configuration and customization library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:6a33dc555cc9ba8b10caf7695878ef134eeb36d0af366041f639b1da9b6ed220
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/fontconfig/
COMPONENT_ARCHIVE_URL= 	https://www.freedesktop.org/software/fontconfig/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(TEST_64)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_FMRI.fontconfig-32= $(COMPONENT_FMRI)/32

# Make gcc 14 accept the old code.
CFLAGS += -Wno-error=incompatible-pointer-types
CFLAGS += -Wno-error=int-conversion

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D); autoreconf )

# Gperf files should be regenerated
# https://bugs.freedesktop.org/show_bug.cgi?id=101280
COMPONENT_PRE_CONFIGURE_ACTION= ( $(RM) $(SOURCE_DIR)/src/fcobjshash.h )

CONFIGURE_OPTIONS += --with-baseconfigdir=$(ETCDIR)/fonts
CONFIGURE_OPTIONS += --with-default-fonts='/usr/share/fonts'
CONFIGURE_OPTIONS += --with-add-fonts='/etc/X11/fontpath.d,/usr/share/ghostscript/fonts,/usr/X11/lib/X11/fonts'
CONFIGURE_OPTIONS += --with-cache-dir=/var/cache/fontconfig

$(BUILD_DIR)/.fonts_installed:	$(INSTALL_64)
	$(RM) -r $(PROTO_DIR)/etc/fonts/conf.d 
	$(RM) -r $(PROTO_DIR)/etc/fonts/conf.avail
	$(MKDIR) $(PROTO_DIR)/etc/fonts/conf.d
	$(MV) $(PROTO_DIR)/usr/share/fontconfig/conf.avail $(PROTO_DIR)/etc/fonts/conf.avail
	for i in $$(ls $(PROTO_DIR)/etc/fonts/conf.avail); do \
		ln -s ../conf.avail/$$i $(PROTO_DIR)/etc/fonts/conf.d/$$i; \
	done
	$(TOUCH) $@

install:	$(INSTALL_64) $(BUILD_DIR)/.fonts_installed

# Manually added build dependencies
REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += library/json-c/32

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/expat/32
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/freetype-2/32
