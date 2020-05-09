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
# Copyright 2020 David Stes
# 

#
# Package Makefile for "GNU Smalltalk" or "gst"
#
# see http://smalltalk.gnu.org for more info
# note that the "stable" version 3.2.5 the file cint.c doesn't compile
# on OpenIndiana Hipster, so use the "alpha" 3.2.91 (which compiles)
#

# gst can be built 64-bit but seems to have an issue
# ../scripts/Package.st:31: Abort in 64-bit case
BUILD_BITS=32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst
COMPONENT_VERSION=	3.2.91
COMPONENT_SUMMARY=	GNU Smalltalk
COMPONENT_PROJECT_URL=	http://smalltalk.gnu.org
COMPONENT_FMRI=		runtime/gst
COMPONENT_CLASSIFICATION=	Development/Other Languages

COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

COMPONENT_SRC=		smalltalk-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:00628239fcd7c76a3a591cee2df5919ca632387594082af1f29c85bf588162fd
WEBSITE=		https://alpha.gnu.org/gnu/smalltalk/
COMPONENT_ARCHIVE_URL=	$(WEBSITE)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(WEBSITE)/$(COMPONENT_ARCHIVE).sig

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS +=		-I/usr/include/gmp

CONFIGURE_OPTIONS +=    --without-emacs
CONFIGURE_OPTIONS +=    --with-gmp

# the default seems to install non-stripped
COMPONENT_INSTALL_TARGETS=	install-strip

# Build dependencies
REQUIRED_PACKAGES += text/texinfo
REQUIRED_PACKAGES += x11/library/mesa

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libsigsegv
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/freeglut
REQUIRED_PACKAGES += x11/library/glu
