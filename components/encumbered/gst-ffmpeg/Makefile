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

COMPONENT_NAME= gst-ffmpeg
COMPONENT_VERSION= 0.10.13
COMPONENT_SUMMARY= GNOME streaming media framework plugins
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:ed9cc4375100c80ce56540ac1c30b8712a94d0cb97ba33dd52dd6203cd554729
COMPONENT_ARCHIVE_URL= \
  http://gstreamer.freedesktop.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gstreamer.freedesktop.org/
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = library/audio/gstreamer/plugin/ffmpeg
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

gcc_OPT = -O2

PATH = /usr/gnu/bin:/usr/bin

CFLAGS += -I/usr/sfw/include -I/usr/X11/include

COMPONENT_PREP_ACTION =        ( cd $(SOURCE_DIR) && aclocal -I ./m4 -I./common/m4 &&\
					autoheader &&\
					automake -a -f -c --gnu &&\
					autoconf )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/orc
