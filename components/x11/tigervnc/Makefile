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
COMPONENT_VERSION= 1.1.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= TigerVNC X11/VNC server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:594b70825a2c24863afd7b8dd2a5bc1935807118c6726e1d98396dee44d060f4
COMPONENT_ARCHIVE_URL= \
  ftp://tux.rainside.sk/gentoo/distfiles/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://tigervnc.org/
COMPONENT_LICENSE_FILE= LICENCE.TXT
COMPONENT_LICENSE= GPLv2

PATCH_LEVEL=0

# Note that the xorg additional patch (tigervnc-xserver) does not fit this pattern. That is intentional
PATCH_PATTERN = [0-9][0-9]*.patch

XORG_ADDITIONAL_PATCH_1 = $(PATCH_DIR)/tigervnc11-xorg111.patch
XORG_ADDITIONAL_PATCH_2 = $(PATCH_DIR)/tigervnc11-xorg112.patch
XORG_ADDITIONAL_PATCH_3 = $(PATCH_DIR)/tigervnc11-xorg114.patch

XORG_SERVER_VERSION= 1.14.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_POST_UNPACK_ACTION +=  ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) )

$(SOURCE_DIR)/.prep: $(ARCHIVE_STAMPS) $(COMPONENT_DIR)/../xorg-server/xorg-server-$(XORG_SERVER_VERSION)/.prep
	$(COMPONENT_PREP_ACTION)
	chmod -R u+w $(COMPONENT_SRC)/unix/xserver
	cp -r $(COMPONENT_DIR)/../xorg-server/xorg-server-$(XORG_SERVER_VERSION)/* $(COMPONENT_SRC)/unix/xserver
	$(GPATCH) -d $(@D)/unix $(GPATCH_FLAGS) < $(SOURCE_DIR)/unix/xserver114.patch
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) <  $(XORG_ADDITIONAL_PATCH_1) 
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) <  $(XORG_ADDITIONAL_PATCH_2) 
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) <  $(XORG_ADDITIONAL_PATCH_3) 
	( cd $(@D)/unix/xserver && \
		aclocal -I m4 && \
		autoheader && \
		libtoolize --automake --copy --force && \
		automake -a -f -c &&\
		autoconf)
	$(TOUCH) $@


$(COMPONENT_DIR)/../xorg-server/xorg-server-$(XORG_SERVER_VERSION)/.prep:
	$(GMAKE) -C $(COMPONENT_DIR)/../xorg-server prep

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LD_OPTIONS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

COMPONENT_PREP_ACTION =        (cd $(@D) &&\
					aclocal -I m4 && \
                                        autoheader && \
                                        libtoolize --automake --copy --force && \
                                        automake -a -f -c &&\
                                        autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --with-installed-zlib
CONFIGURE_OPTIONS+= --with-system-jpeg 
CONFIGURE_OPTIONS+= --without-simd
CONFIGURE_OPTIONS+= --localstatedir=/var

CONFIGURE_LIBDIR = /usr/lib/vnc

# I don't know why, but it just doesn't work without this
gcc_OPT= 

CPPFLAGS += -DSUNSOFT
CPPFLAGS += -I/usr/include/pixman-1
CPPFLAGS += -I/usr/include/xorg

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

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

$(BUILD_DIR)/.built_jar: $(BULD_32)
	$(ENV) $(COMPONENT_BUILD_ENV) \
                $(GMAKE) -C $(BUILD_DIR_32)/java/src/com/tigervnc/vncviewer  $(COMPONENT_BUILD_GMAKE_ARGS)
	$(TOUCH) $(@)

$(BUILD_DIR)/.installed_jar: $(INSTALL_32) $(BUILD_DIR)/.built_jar
	rm -fr $(JAVA_INSTALL_DIR)
	$(MKDIR) $(JAVA_INSTALL_DIR)
	$(INSTALL) -m 0444  $(BUILD_DIR_32)/java/src/com/tigervnc/vncviewer/README \
		$(BUILD_DIR_32)/java/src/com/tigervnc/vncviewer/LICENCE.TXT \
		$(BUILD_DIR_32)/java/src/com/tigervnc/vncviewer/index.html \
		$(BUILD_DIR_32)/java/src/com/tigervnc/vncviewer/index.vnc \
		$(BUILD_DIR_32)/java/src/com/tigervnc/vncviewer/tigervnc_16.gif \
		$(JAVA_INSTALL_DIR)
	$(INSTALL) -m 0555 $(BUILD_DIR_32)/java/src/com/tigervnc/vncviewer/VncViewer.jar $(JAVA_INSTALL_DIR)
	$(TOUCH) $(@)

$(BUILD_DIR)/.built_Xvnc: $(BULD_32) $(BUILD_DIR)/.configured_Xvnc
	(cd $(BUILD_DIR_32)/unix; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
	$(COMPONENT_BUILD_TARGETS))
	(cd $(BUILD_DIR_32)/unix/xserver; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
	$(COMPONENT_BUILD_TARGETS))
	$(TOUCH) $@

$(BUILD_DIR)/.installed_Xvnc: $(INSTALL_32) $(BUILD_DIR)/.built_Xvnc
	(cd $(BUILD_DIR_32)/unix/xserver/hw/vnc; $(ENV) $(COMPONENT_INSTALL_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_INSTALL_ARGS) \
	$(COMPONENT_INSTALL_TARGETS))
	$(TOUCH) $@


$(BUILD_DIR)/.configured_Xvnc: $(BUILD_DIR_32)/.configured
	(cd $(BUILD_DIR_32)/unix/xserver ; $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL)  $(XVNC_CONFIGURE_SCRIPT) $(XVNC_CONFIGURE_OPTIONS))
	$(TOUCH) $(@)

build: $(BUILD_32) $(BUILD_DIR)/.built_jar $(BUILD_DIR)/.built_Xvnc

install: $(INSTALL_32) $(BUILD_DIR)/.installed_jar $(BUILD_DIR)/.installed_Xvnc

REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxdmcp
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfont
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/server/xserver-common
