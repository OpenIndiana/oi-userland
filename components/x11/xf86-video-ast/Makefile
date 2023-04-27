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
# Copyright 2015 Ken Mays
#

X11_CATEGORY=DRIVER
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xf86-video-ast
COMPONENT_VERSION= 1.1.6
COMPONENT_SUMMARY= xf86-video-ast - ASPEED AST driver for the Xorg X server
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-ast
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:75754fa9c7f9a94fcc706d32cc118942d16c71934d88110442443a143b930daf

include $(WS_MAKE_RULES)/common.mk

# Paths to find libraries/modules to link with 

AST_LIBRARIES_i386 = -lint10 -lpciaccess -lvbe -lvgahw

AST_LIBRARIES = -lfb -lint10 -lpciaccess -lvbe -lvgahw

LD_OPTIONS+= -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
	     $(AST_LIBRARIES)

CONFIGURE_ENV += with_xorg_module_dir=/usr/lib/xorg/modules/drivers/$(MACH64)

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/server/xorg
