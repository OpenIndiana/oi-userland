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
#

BUILD_BITS= 32_and_64
USE_COMMON_TEST_MASTER= no
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fontconfig
COMPONENT_REVISION=	1
COMPONENT_VERSION=	2.14.2
COMPONENT_SUMMARY=	Fontconfig - Font configuration and customization library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:dba695b57bce15023d2ceedef82062c2b925e51f5d4cc4aef736cf13f60a468b
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/fontconfig/
COMPONENT_ARCHIVE_URL= 	https://www.freedesktop.org/software/fontconfig/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

gcc_OPT= -O2

COMPONENT_PREP_ACTION=  ( cd $(@D); autoreconf )

# Gperf files should be regenerated
# https://bugs.freedesktop.org/show_bug.cgi?id=101280
COMPONENT_PRE_CONFIGURE_ACTION= ($(RM) $(SOURCE_DIR)/src/fcobjshash.h)

CONFIGURE_OPTIONS+= --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS+= --with-baseconfigdir=$(ETCDIR)/fonts
CONFIGURE_OPTIONS+= --with-default-fonts='/usr/share/fonts'
CONFIGURE_OPTIONS+= --with-add-fonts='/etc/X11/fontpath.d,/usr/share/ghostscript/fonts,/usr/X11/lib/X11/fonts'
CONFIGURE_OPTIONS+= --with-cache-dir=/var/cache/fontconfig

$(BUILD_DIR)/.fonts_installed: $(INSTALL_32_and_64)
	$(RM) -r $(PROTO_DIR)/etc/fonts/conf.d 
	$(RM) -r $(PROTO_DIR)/etc/fonts/conf.avail
	$(MKDIR) $(PROTO_DIR)/etc/fonts/conf.d
	$(MV) $(PROTO_DIR)/usr/share/fontconfig/conf.avail $(PROTO_DIR)/etc/fonts/conf.avail
	for i in $$(ls $(PROTO_DIR)/etc/fonts/conf.avail); do \
		ln -s ../conf.avail/$$i $(PROTO_DIR)/etc/fonts/conf.d/$$i; \
	done
	$(TOUCH) $@

install:	$(INSTALL_32_and_64) $(BUILD_DIR)/.fonts_installed

# This is necessary to pass tests
unexport SHELLOPTS

# Manually added build dependencies
REQUIRED_PACKAGES += developer/gperf

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
