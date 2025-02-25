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

BUILD_STYLE=justmake
DROP_STATIC_LIBRARIES = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         rtmpdump
COMPONENT_VERSION=      2.6
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      RTMPdump -- a toolkit for RTMP streams
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://rtmpdump.mplayerhq.hu/
COMPONENT_LICENSE=      GPLv2,LGPLv2
COMPONENT_LICENSE_FILE= rtmpdump.license
COMPONENT_CLASSIFICATION=Applications/Sound and Video
COMPONENT_FMRI=         video/rtmpdump

# This project does not do release tarballs.  It even does not use git tags so
# we need to pin to the desired commit explicitly.
GIT_REPO=https://git.ffmpeg.org/rtmpdump
GIT_COMMIT_ID=6f6bb1353fc84f4cc37138baa99f586750028a01
GIT_HASH = sha256:627ea7b61a14ae5820d3ab164c2e7ce3331a1dd362d8b5b8017bd217b1952743

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

COMPONENT_ENV += CC="$(CC)"
COMPONENT_ENV += XCFLAGS="$(CFLAGS) -I$(OPENSSL_INCDIR)"
COMPONENT_ENV += XLDFLAGS="$(LDFLAGS) -L$(OPENSSL_LIBDIR) -R$(OPENSSL_LIBDIR)"
COMPONENT_ENV += XLIBS="-lnsl -lsocket"

COMPONENT_BUILD_ENV += $(COMPONENT_ENV)

COMPONENT_INSTALL_ENV.64 = ARCH=/$(MACH64)
COMPONENT_INSTALL_ENV += $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV += $(COMPONENT_INSTALL_ENV.$(BITS))

COMPONENT_BUILD_TARGETS = all

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
