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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= tigervnc
COMPONENT_VERSION= 1.8.0
COMPONENT_SUMMARY= TigerVNC X11/VNC server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:9951dab0e10f8de03996ec94bec0d938da9f36d48dca8c954e8bbc95c16338f8
COMPONENT_ARCHIVE_URL= \
  https://github.com/TigerVNC/tigervnc/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = http://tigervnc.org/
COMPONENT_LICENSE_FILE= LICENCE.TXT
COMPONENT_LICENSE= GPLv2

# Note that the xorg additional patch (tigervnc-xserver) does not fit this pattern. That is intentional
PATCH_PATTERN = [0-9][0-9]*.patch

XORG_ADDITIONAL_PATCH_1 = $(PATCH_DIR)/tigervnc-screenlock.patch

XORG_SERVER_VERSION= 1.19.6
XORG_SERVER_PATCH= xserver119.patch

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

# Avoid prepending /usr/gnu/bin to $(PATH)
# as ld is used during dix build and GNU ld
# can't handle dtrace probes
PATH=$(GCC_ROOT)/bin:$(PATH.illumos)

COMPONENT_POST_UNPACK_ACTION +=  ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) )

$(SOURCE_DIR)/.prep: $(ARCHIVE_STAMPS) $(COMPONENT_DIR)/../xorg-server/xorg-server-$(XORG_SERVER_VERSION)/.prep
	$(COMPONENT_PREP_ACTION)
	chmod -R u+w $(COMPONENT_SRC)/unix/xserver
	cp -r $(COMPONENT_DIR)/../xorg-server/xorg-server-$(XORG_SERVER_VERSION)/* $(COMPONENT_SRC)/unix/xserver
	$(GPATCH) -d $(@D)/unix $(GPATCH_FLAGS) < $(SOURCE_DIR)/unix/$(XORG_SERVER_PATCH)
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) <  $(XORG_ADDITIONAL_PATCH_1) 
	( cd $(@D)/unix/xserver && \
		aclocal -I m4 && \
		autoheader && \
		libtoolize --automake --copy --force && \
		automake -a -f -c &&\
		autoconf)
	$(TOUCH) $@


$(COMPONENT_DIR)/../xorg-server/xorg-server-$(XORG_SERVER_VERSION)/.prep:
	$(GMAKE) -C $(COMPONENT_DIR)/../xorg-server prep

# Build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

# Set standard explicitly
CFLAGS   += -std=gnu89
CXXFLAGS += -std=gnu++98

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LD_OPTIONS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

COMPONENT_PRE_CMAKE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+= -DENABLE_NLS:BOOL=OFF
CMAKE_OPTIONS+= -DBUILD_JAVA:BOOL=TRUE
CMAKE_OPTIONS+= -DCMAKE_C_ARCHIVE_CREATE:STRING="crS"
CMAKE_OPTIONS+= -DCMAKE_CXX_ARCHIVE_CREATE:STRING="crS"
CMAKE_OPTIONS+= -G "Unix Makefiles"

CONFIGURE_LIBDIR = /usr/lib/vnc

# I don't know why, but it just doesn't work without this
gcc_OPT= 

CPPFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += -DSUNSOFT -DTSOL
CPPFLAGS += -I/usr/include/pixman-1
CPPFLAGS += -I/usr/include/mesa
CPPFLAGS += -I/usr/include/xorg

# Required for linking to libXfont2
X11_SERVERLIBS_DIR=/usr/lib/xorg
LDFLAGS+= -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR) 

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

JAVA_SOURCE_DIR  = $(SOURCE_DIR)/java/com/tigervnc
JAVA_BUILD_DIR   = $(BUILD_DIR_32)/java
JAVA_INSTALL_DIR = $(PROTO_DIR)/usr/share/vnc/classes

XVNC_CONFIGURE_SCRIPT=	$(BUILD_DIR_32)/unix/xserver/configure

XVNC_CONFIGURE_OPTIONS += --bindir=/usr/bin
XVNC_CONFIGURE_OPTIONS += --disable-builddocs
XVNC_CONFIGURE_OPTIONS += --disable-config-hal
XVNC_CONFIGURE_OPTIONS += --disable-dga
XVNC_CONFIGURE_OPTIONS += --disable-dmx
XVNC_CONFIGURE_OPTIONS += --disable-dri3
XVNC_CONFIGURE_OPTIONS += --disable-install-setuid
XVNC_CONFIGURE_OPTIONS += --disable-kdrive
XVNC_CONFIGURE_OPTIONS += --disable-present
XVNC_CONFIGURE_OPTIONS += --disable-static
XVNC_CONFIGURE_OPTIONS += --disable-unit-tests
XVNC_CONFIGURE_OPTIONS += --disable-xephyr
XVNC_CONFIGURE_OPTIONS += --disable-xfree86-utils
XVNC_CONFIGURE_OPTIONS += --disable-xnest
XVNC_CONFIGURE_OPTIONS += --disable-xorg
XVNC_CONFIGURE_OPTIONS += --disable-xsdl
XVNC_CONFIGURE_OPTIONS += --disable-xvfb
XVNC_CONFIGURE_OPTIONS += --disable-xwin
XVNC_CONFIGURE_OPTIONS += --enable-dri2
XVNC_CONFIGURE_OPTIONS += --enable-glx
XVNC_CONFIGURE_OPTIONS += --enable-shared
XVNC_CONFIGURE_OPTIONS += --enable-xcsecurity
XVNC_CONFIGURE_OPTIONS += --enable-xdm-auth-1
XVNC_CONFIGURE_OPTIONS += --enable-xdmcp
XVNC_CONFIGURE_OPTIONS += --prefix=/usr
XVNC_CONFIGURE_OPTIONS += --with-builderstring="Solaris ABI: $(BITS)-bit"
XVNC_CONFIGURE_OPTIONS += --with-default-font-path='catalogue:/etc/X11/fontpath.d'
XVNC_CONFIGURE_OPTIONS += --with-default-xkb-model=pc105
XVNC_CONFIGURE_OPTIONS += --with-dri-driver-path=/usr/lib/xorg/modules/dri
XVNC_CONFIGURE_OPTIONS += --with-log-dir=/var/log
XVNC_CONFIGURE_OPTIONS += --with-module-dir=/usr/lib/xorg/modules
XVNC_CONFIGURE_OPTIONS += --with-os-name="`uname -srm`"
XVNC_CONFIGURE_OPTIONS += --with-vendor-name="Project OpenIndiana"
XVNC_CONFIGURE_OPTIONS += --with-vendor-web="http://openindiana.org"
XVNC_CONFIGURE_OPTIONS += --with-xkb-bin-directory=/usr/bin
XVNC_CONFIGURE_OPTIONS += --with-xkb-output=/var/run/xkb
XVNC_CONFIGURE_OPTIONS += --without-int10
XVNC_CONFIGURE_OPTIONS += --disable-selective-werror
XVNC_CONFIGURE_OPTIONS += AR_FLAGS="cruS"
XVNC_CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"


$(BUILD_DIR)/.configured_Xvnc: $(BUILD_DIR_32)/.configured
	(cd $(BUILD_DIR_32)/unix/xserver ; \
		$(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) \
	       	$(XVNC_CONFIGURE_SCRIPT) $(XVNC_CONFIGURE_OPTIONS))
	$(TOUCH) $(@)

$(BUILD_DIR)/.built_Xvnc: $(BUILD_32) $(BUILD_DIR)/.configured_Xvnc
	(cd $(BUILD_DIR_32)/unix; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
	$(COMPONENT_BUILD_TARGETS))
	(cd $(BUILD_DIR_32)/unix/xserver; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
	$(COMPONENT_BUILD_TARGETS))
	$(TOUCH) $@

$(BUILD_DIR)/.installed_jar: $(INSTALL_32)
	rm -fr $(JAVA_INSTALL_DIR)
	$(MKDIR) $(JAVA_INSTALL_DIR)
	$(INSTALL) -m 0444 \
	$(JAVA_SOURCE_DIR)/vncviewer/README \
	$(JAVA_SOURCE_DIR)/vncviewer/LICENCE.TXT \
	$(JAVA_SOURCE_DIR)/vncviewer/index.html \
	$(JAVA_SOURCE_DIR)/vncviewer/index.vnc \
	$(JAVA_SOURCE_DIR)/vncviewer/tigervnc_16.gif \
	$(JAVA_INSTALL_DIR)
	$(INSTALL) -m 0555 $(JAVA_BUILD_DIR)/VncViewer.jar $(JAVA_INSTALL_DIR)
	$(TOUCH) $(@)

$(BUILD_DIR)/.installed_Xvnc: $(INSTALL_32) $(BUILD_DIR)/.built_Xvnc
	(cd $(BUILD_DIR_32)/unix/xserver/hw/vnc; $(ENV) $(COMPONENT_INSTALL_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_INSTALL_ARGS) \
	$(COMPONENT_INSTALL_TARGETS))
	$(TOUCH) $@


build: $(BUILD_32) $(BUILD_DIR)/.built_Xvnc

install: $(INSTALL_32) $(BUILD_DIR)/.installed_jar $(BUILD_DIR)/.installed_Xvnc

# Build dependencies
REQUIRED_PACKAGES += text/xmlto
REQUIRED_PACKAGES += x11/server/xorg

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += library/fltk
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxdmcp
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxfont2
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/server/xserver-common
