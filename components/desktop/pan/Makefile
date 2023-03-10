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
# Copyright 2022 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         pan
COMPONENT_VERSION=      0.149
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://pan.rebelbase.com
COMPONENT_SUMMARY=      A powerful Newsgroup Article reader
COMPONENT_FMRI=         desktop/nntp/pan
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:5d34d0d7dbb73ee53484ffe173f01d8b2c0732126ec21d8cf29d6baa5ecb85ea
COMPONENT_ARCHIVE_URL=	https://pan.rebelbase.com/download/releases/$(COMPONENT_VERSION)/source/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       Applications/Internet
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= pan.license

LDFLAGS += -lsocket -lnsl

CONFIGURE_OPTIONS += --with-gmime2
CONFIGURE_OPTIONS += --with-gtk3
CONFIGURE_OPTIONS += --with-gnutls

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# SPARC needs math library, to publish.
REQUIRED_PACKAGES += system/library/math

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtkspell3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gmime
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
