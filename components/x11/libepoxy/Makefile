#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016 Aurelien Larcher
# Copyright (c) 2018 Michal Nowak
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libepoxy
COMPONENT_VERSION= 1.5.2
COMPONENT_FMRI=	   x11/library/libepoxy
COMPONENT_SUMMARY= library for handling OpenGL function pointers
COMPONENT_CLASSIFICATION=System/Hardware
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a9562386519eb3fd7f03209f279f697a8cba520d3c155d6e253c3e138beca7d8
COMPONENT_ARCHIVE_URL=	\
    https://github.com/anholt/libepoxy/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for configure without this.
COMPONENT_PREP_ACTION = (cd $(@D) && \
                         libtoolize --automake --copy --force && \
                         aclocal -Im4 && \
                         autoheader && \
                         automake -a -f -c && \
                         autoconf )

CONFIGURE_ENV.32 += CPPFLAGS="$(CPP_LARGEFILES.32)"

REQUIRED_PACKAGES += system/library
