#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020-1 Rick V
#

BUILD_BITS=32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=i3status
COMPONENT_VERSION=2.13
COMPONENT_SUMMARY=status indicator for i3
COMPONENT_PROJECT_URL=https://i3wm.org
COMPONENT_FMRI=desktop/window-manager/i3/i3status
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_ARCHIVE_URL=https://github.com/i3/i3status/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=sha256:9d545df5c0053be5e05b7d196ec3c4a20deee102c39ef8b7f0eb816e85bae0ce
COMPONENT_LICENSE=BSD-3

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk
CPPFLAGS+= -D_XOPEN_SOURCE=700
CPPFLAGS+= -D__EXTENSIONS__
LDFLAGS+= -lpulse -lsocket -lnsl
CONFIGURE_OPTIONS+= --enable-debug=no
CFLAGS.studio+=-xspace 

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/window-manager/i3
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/libconfuse
REQUIRED_PACKAGES += library/libyajl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
