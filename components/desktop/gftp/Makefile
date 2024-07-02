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
# Copyright (c) 2015 Alexander Pyhalov
#

OPENSSL_VERSION= 3.1
PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gftp
COMPONENT_VERSION=	2.9.1
COMPONENT_VERSION_MNR=	b
COMPONENT_PROJECT_URL=	https://www.gftp.org/
COMPONENT_SUMMARY=	Multithreaded file transfer client for *NIX based machines
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)$(COMPONENT_VERSION_MNR)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:79c727a0c7720e0e49dac4fc760a686d10ff78a496e1e3e644b45d3e76e1eecd
COMPONENT_ARCHIVE_URL=	https://github.com/masneyb/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)$(COMPONENT_VERSION_MNR)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/$(COMPONENT_NAME)
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	MIT
COMPONENT_CLASSIFICATION=	Applications/System Utilities

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS += -I$(OPENSSL_INCDIR)
LDFLAGS  += -L$(OPENSSL_LIBDIR)

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
