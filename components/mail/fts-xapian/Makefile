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
# Copyright 2024 Friedrich Kink
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         fts-xapian
COMPONENT_VERSION=      1.7.17
COMPONENT_SUMMARY=      FTS Xapian plugin for Dovecot
COMPONENT_PROJECT_URL=  https://github.com/grosjo/fts-xapian
COMPONENT_FMRI=         mail/dovecot/fts-xapian
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      dovecot-$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:64163cc758995b4203948c707f3ab48d317f13babd8dea987bf54740d71e7267
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( cd $(SOURCE_DIR); autoupdate; autoreconf -vi; )

TEST_TARGET= $(NO_TESTS)

CONFIGURE_OPTIONS+= --enable-static=no 
CONFIGURE_OPTIONS+= --disable-dependency-tracking
CONFIGURE_OPTIONS+= --with-dovecot=/usr/lib/amd64/dovecot 
CONFIGURE_OPTIONS+= --with-dovecot-install-dirs

# manually added dependency
REQUIRED_PACKAGES += mail/dovecot

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/xapian
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
