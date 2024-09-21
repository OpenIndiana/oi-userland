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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libgphoto2
COMPONENT_VERSION=      2.5.27
COMPONENT_SUMMARY=      Digital camera library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:f8b85478c44948a0b0b52c4d4dfda2de1d7bcb7b262c76bd1ae306d9c63240d7
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/gphoto/files/libgphoto/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL=  https://www.gphoto.org
COMPONENT_FMRI=         library/libgphoto2-2
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Without this we get issues with unresolved references to  __deregister_frame_info_bases
LD_B_DIRECT=
LD_Z_IGNORE=

CFLAGS.32 += -D_FILE_OFFSET_BITS=64
CFLAGS	  += $(CFLAGS.$(BITS))
CFLAGS	  += $(XPG8MODE)

COMPONENT_PREP_ACTION += ( cd $(@D) && PATH="$(PATH)" autoreconf -fiv )

CONFIGURE_OPTIONS += --with-doc-dir=/usr/share/doc/libgphoto2
CONFIGURE_OPTIONS += --disable-static

ENV = /usr/bin/env -i

# Manually added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg-turbo
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
