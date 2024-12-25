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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2016 Aurelien Larcher.  All rights reserved.
# Copyright 2023 Friedrich Kink.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ptlib
COMPONENT_VERSION= 2.16.2
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= PTLib Class Library
COMPONENT_PROJECT_URL = https://sourceforge.net/projects/opalvoip/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:eb444e1d72db69c8db1b9b302faa86ba4603cf310a82c934a78238e4f91405d0
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)files/V3.16%20Procyon/Stable%202/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/desktop/ptlib
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE= MPLv1.0

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D) && aclocal && autoconf )

CFLAGS += -I$(OPENSSL_INCDIR)
LDFLAGS += -L$(OPENSSL_LIBDIR)

COMPONENT_BUILD_ARGS += VERBOSE=1

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =  ( CLONEY_MODE=copy $(CLONEY) $(SOURCE_DIR) $(@D) )
COMPONENT_POST_CONFIGURE_ACTION = ( echo "install: ; @\$$(MAKE) --file=$(SOURCE_DIR)/Makefile \$$(MAKECMDGOALS)" >> $(@D)/Makefile )

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-plugins
CONFIGURE_OPTIONS += --enable-resolver
CONFIGURE_OPTIONS += --enable-cpp11
CONFIGURE_OPTIONS += --enable-exceptions
#CONFIGURE_OPTIONS += --enable-opal
CONFIGURE_OPTIONS += --enable-openssl
CONFIGURE_OPTIONS += --enable-sunaudio
CONFIGURE_OPTIONS += --enable-pulse
CONFIGURE_OPTIONS += --enable-url
CONFIGURE_OPTIONS += --enable-http
CONFIGURE_OPTIONS += --enable-httpforms
CONFIGURE_OPTIONS += --enable-httpsvc
CONFIGURE_OPTIONS += --disable-v4l2
CONFIGURE_OPTIONS += --enable-v4l
CONFIGURE_OPTIONS += --enable-lua
CONFIGURE_OPTIONS += PKG_CONFIG_PATH=/usr/lib/$(MACH64)/pkgconfig
CONFIGURE_OPTIONS += OPENLDAP_LIBS="-llber-2.6 -lldap-2.6"
CONFIGURE_OPTIONS += OPENLDAP_CFLAGS="-I/usr/include/openldap"
# to ensure gstreamer-1.0
CONFIGURE_OPTIONS += GSTREAMER_LIBS="-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0"
CONFIGURE_OPTIONS += GSTREAMER_CFLAGS="-pthread -DFFI_NO_RAW_API -I/usr/include/gstreamer-1.0 -I/usr/lib/amd64/libffi-3.2.1/include -I/usr/include/glib-2.0 -I/usr/lib/amd64/glib-2.0/include -I/usr/include/pcre"

ENV += -i

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libsasl
