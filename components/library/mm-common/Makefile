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
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Michal Nowak
# Copyright 2023 Friedrich Kink
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         mm-common
COMPONENT_VERSION=      1.0.5
COMPONENT_SUMMARY=      GNOME C++ bindings effort http://www.gtkmm.org support tools
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:705c6d29f4116a29bde4e36cfc1b046c92b6ef8c6dae4eaec85018747e6da5aa
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/1.0/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gnome.org
COMPONENT_FMRI=         library/desktop/c++/mm-common
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( \
		cd $(SOURCE_DIR); \
		./autogen.sh; \
		$(CLONEY) $(SOURCE_DIR) $(@D); \
		$(GMAKE) distclean; \
		);

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=/usr/lib

COMPONENT_POST_INSTALL_ACTION = $(GSED) -i -e 's:env python3:python$(PYTHON_VERSION):' $(PROTOUSRBINDIR)/mm-common-get

# Configure checks
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += web/wget

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += shell/ksh93
