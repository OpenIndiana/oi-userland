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

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xdm
COMPONENT_VERSION= 1.1.14
COMPONENT_SUMMARY=  the X Display Manager (xdm) server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:3e9bf25636797ec9e595286dd6820ecc33901439f07705eaf608ecda012c3d5f
COMPONENT_ARCHIVE_URL=	https://xorg.freedesktop.org/archive/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/
COMPONENT_FMRI= system/display-manager/xdm
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING

PATH= $(PATH.gnu)

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( \
	cd  $(@D) && \
	libtoolize --force && \
	aclocal -I . && \
	autoheader && \
	automake -a -c -f && \
	autoconf )

SAMPLE_CONFIGS = $(BUILD_DIR)/.sample-configs

# Only build shared greeter module, not static
CONFIGURE_OPTIONS += --enable-shared=yes
CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --enable-xdmshell
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-xdmconfigdir=/etc/X11/xdm
CONFIGURE_OPTIONS += --with-piddir=/var/run/xdm
CONFIGURE_OPTIONS += --with-authdir=/var/run/xdm
CONFIGURE_OPTIONS += --bindir=/usr/sbin
CONFIGURE_OPTIONS += --with-xrdb=/usr/bin/xrdb
CONFIGURE_OPTIONS += --with-default-session=command='/usr/bin/xterm -ls'

CONFIGURE_ENV += DEF_SERVER=/usr/bin/X
CONFIGURE_ENV += DEF_USER_PATH=/usr/bin:/usr/sbin
CONFIGURE_ENV += DEF_SYSTEM_PATH=/usr/bin:/usr/sbin

XDM_CONFIG_FILES= Xaccess Xresources Xservers xdm-config

$(SAMPLE_CONFIGS):	$(INSTALL_64)
	for config in $(XDM_CONFIG_FILES); do \
		COMMENT_CHAR=$$(head -n 1 $(PROTO_DIR)/etc/X11/xdm/$${config}); \
		$(GSED) -e "s:;:$${COMMENT_CHAR}:" -e "s:FILE:$${config}:" $(COMPONENT_DIR)/files/header  > $(PROTO_DIR)/usr/lib/$(MACH64)/X11/xdm/$${config} ; \
		cat $(PROTO_DIR)/etc/X11/xdm/$${config}>> $(PROTO_DIR)/usr/lib/$(MACH64)/X11/xdm/$${config} ; \
	done
	$(TOUCH) $@

install: $(SAMPLE_CONFIGS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxdmcp
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
REQUIRED_PACKAGES += x11/server/xserver-common
