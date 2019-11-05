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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fontconfig
COMPONENT_VERSION=	2.13.1
COMPONENT_REVISION=	3
COMPONENT_SUMMARY=	Fontconfig - Font configuration and customization library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:f655dd2a986d7aa97e052261b36aa67b0a64989496361eca8d604e6414006741
COMPONENT_ARCHIVE_URL= \
	http://www.freedesktop.org/software/fontconfig/release/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/fontconfig/
COMPONENT_FMRI=		system/library/fontconfig
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

gcc_OPT=-O2

# This is necessary to pass tests
unexport SHELLOPTS

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

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) $(BUILD_DIR)/.fonts_installed

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
