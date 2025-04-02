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
# Copyright (c) 2015-2021 Jim Klimov
# Copyright (c) 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ccache
COMPONENT_VERSION=	4.11.2
COMPONENT_SUMMARY=      ccache - cacher of GCC-compiled files to avoid doing the same job twice
COMPONENT_PROJECT_URL=  https://ccache.dev
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:319390f276123968cfa565acc3da0b1e18414374b40ff25274230e6860352125
COMPONENT_ARCHIVE_URL=  https://github.com/ccache/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/ccache
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_LICENSE=      GPLv3, murmurhash, papowell/jhweiss, PostgreSQL, Python, zlib
COMPONENT_LICENSE_FILE= LICENSE.adoc

include $(WS_MAKE_RULES)/common.mk

# Install additional files
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dt $(PROTOLIBDIR)/svc/manifest/application $(COMPONENT_DIR)/files/ccache-update-symlinks.xml ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dt $(PROTOLIBDIR)/svc/method $(COMPONENT_DIR)/files/ccache-update-symlinks.sh ;

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/hiredis
REQUIRED_PACKAGES += developer/fmt
REQUIRED_PACKAGES += library/libxxhash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
