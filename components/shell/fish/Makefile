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
# Copyright 2017, Longrin Wischnewski.
# Copyright 2019, Michal Nowak
# Copyright 2021, Nona Hansel
# Copyright 2022 Niklas Poslovski
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fish
COMPONENT_VERSION=	4.0.6
COMPONENT_SUMMARY=	Fish is a smart and user-friendly command line shell
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://fishshell.com
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:125d9ce0dd8a3704dc0782925df34f0208bffc42af5f34914449d14c34b5dae1
COMPONENT_ARCHIVE_URL=	https://github.com/fish-shell/fish-shell/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		shell/fish
COMPONENT_CLASSIFICATION=	System/Shells
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=       COPYING

include $(WS_MAKE_RULES)/common.mk
PATH= $(PATH.gnu)

CMAKE_OPTIONS += -DCMAKE_INSTALL_SYSCONFDIR="/etc"
CMAKE_OPTIONS += -DSYS_PCRE2_INCLUDE_DIR=/usr/include/pcre
CMAKE_OPTIONS += -DFISH_USE_SYSTEM_PCRE2=ON
CMAKE_OPTIONS += -DWITH_GETTEXT=ON

# Need to compile dynamic rust crates. See https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# Need to patch gettext-sys dependency crate contents.  The gettext C
# source does not have #include <stdlib.h> in locating-rule.c .  So patch
# build.rs which then patches gettext after extraction from archive.
# Download all dependency crates and then apply patch.
CRATE_PATCH_FLAG = --backup --version-control=numbered -p0
COMPONENT_PRE_BUILD_ACTION= \
        CARGO_HOME=$(@D)/.cargo cargo fetch --manifest-path $(SOURCE_DIR)/Cargo.toml ; \
        for patchfile in patches-crate/*.patch; do \
                gpatch $(CRATE_PATCH_FLAG) < $$patchfile ; \
        done ;

COMPONENT_TEST_ENV += LC_ALL=C.UTF-8
COMPONENT_TEST_CMD= gmake
COMPONENT_TEST_TARGETS= test

# Manually added dependencies (for tests)
PYTHON_REQUIRED_PACKAGES += library/python/pexpect

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
