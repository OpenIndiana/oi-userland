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
# Copyright (c) 2024 Geoff Weiss
#

BUILD_STYLE= meson
# Allow subprojects to download and build
MESON_WRAPMODE= default

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         foliate
COMPONENT_VERSION=      3.2.1
COMPONENT_SUMMARY=      A simple and modern GTK eBook reader
COMPONENT_PROJECT_URL=  https://johnfactotum.guthub.io/$(COMPONENT_NAME)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a11515af3b6247f40a6d1118028d2e684293c0fe0ca32697f41fb514fa69af87
COMPONENT_ARCHIVE_URL=  https://github.com/johnfactotum/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         desktop/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/Accessories
COMPONENT_LICENSE=      GPL-3.0.-or-later
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# foliate-js submodule git hash
GIT_HASH_SUBMODULE=399248a67a8862ffb5e6463a33f9d52b317ca2eb
# download foliate-js submodule; delete empty directory foliate-js; rename root directory of extracted module to foliate-js
COMPONENT_PRE_CONFIGURE_ACTION= ( cd $(COMPONENT_SRC)/src && \
   wget https://github.com/johnfactotum/foliate-js/archive/$(GIT_HASH_SUBMODULE).zip && \
   unzip $(GIT_HASH_SUBMODULE).zip && \
   rm $(GIT_HASH_SUBMODULE).zip  && \
   rmdir foliate-js && \
   mv foliate-js-$(GIT_HASH_SUBMODULE) foliate-js )

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gjs
