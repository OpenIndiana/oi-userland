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

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libXext
COMPONENT_VERSION= 1.3.5
COMPONENT_REVISION =	1
COMPONENT_SUMMARY= libXext - X11 protocol common extensions client library
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:db14c0c895c57ea33a8559de8cb2b93dc76c42ea4a39e294d175938a133d7bca
COMPONENT_FMRI =   x11/library/libxext
COMPONENT_LICENSE_FILE = COPYING

DROP_STATIC_LIBRARIES = yes

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -DSUNSOFT

LD_OPTIONS += -M $(COMPONENT_DIR)/mapfile-vers

COMPONENT_PREP_ACTION = ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) && \
                          cd $(@D) && PATH=$(PATH) libtoolize --copy --force && \
                          aclocal -I . &&\
                          automake -c -f -a &&\
                          autoconf )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += LIB_MAN_SUFFIX=3xext
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS += --without-xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxevie
REQUIRED_PACKAGES += x11/library/libxscrnsaver
