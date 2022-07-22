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
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gksu
COMPONENT_VERSION=      2.0.2
COMPONENT_REVISION=     6
COMPONENT_FMRI=         desktop/gksu
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_PROJECT_URL=  http://www.nongnu.org/gksu/
COMPONENT_SUMMARY=      Graphical frontend to su
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:a1de3dca039d88c195fcdc9516379439a1d699750417f1e655aa2101a955ee5a
COMPONENT_ARCHIVE_URL=  http://people.debian.org/~kov/gksu/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_LICENSE=      GPLv2

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					$(TOUCH) NEWS  README&&\
					libtoolize --copy --force &&\
					aclocal &&\
					automake -a -c -f && \
                                        autoconf &&\
					intltoolize --force  --copy )

COMPONENT_PRE_CONFIGURE_ACTION =        (chmod -R u+r $(SOURCE_DIR) && cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

CONFIGURE_ENV+=	LT_SYS_LIBRARY_PATH=$(USRLIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS+=	--libexecdir=$(USRLIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	--disable-nautilus-extension

# -O2 is hardcoded
gcc_OPT=

# Build dependencies
REQUIRED_PACKAGES += library/gnome/gnome-keyring

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libgksu
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
