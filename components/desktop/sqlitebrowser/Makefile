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
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         sqlitebrowser
COMPONENT_VERSION=      3.13.1
COMPONENT_SUMMARY=      DB browser for sqlite3
COMPONENT_PROJECT_URL=  https://sqlitebrowser.org
COMPONENT_FMRI=         desktop/application/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1044ba67d649cabc459eb887c016f70d6a404ad651390ab33bf7859dc7f1b67b
COMPONENT_ARCHIVE_URL=  https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.illumos):$(QT5_BINDIR):$(QT5_BASEDIR)

CMAKE_OPTIONS += "-DSYSCONFDIR=$(ETCDIR)"
CMAKE_OPTIONS += "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"

COMPONENT_POST_INSTALL_ACTION = (\
	/usr/bin/elfedit -e 'dyn:value -s RUNPATH "$(GCC_LIBDIR):$(QT5_LIBDIR)"' $(PROTO_DIR)/usr/bin/sqlitebrowser; \
	/usr/bin/elfedit -e 'dyn:value -s RPATH "$(GCC_LIBDIR):$(QT5_LIBDIR)"' $(PROTO_DIR)/usr/bin/sqlitebrowser )

# Packages Required at Buildtime. Not found By gmake

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
