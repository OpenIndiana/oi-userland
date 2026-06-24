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
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fish
COMPONENT_VERSION=	4.8.0
COMPONENT_SUMMARY=	Fish is a smart and user-friendly command line shell
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://fishshell.com
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:33af62c7df2fa553e0e84fa81f6ea48acf98c2bfc50036eaacc70ac8ba63e707
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

# Need to compile dynamic rust crates. See https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# add fixes to third party vendor crates
CRATE_PATCH_FLAG = --backup --version-control=numbered -p0
COMPONENT_PRE_BUILD_ACTION= \
        CARGO_HOME=$(@D)/.cargo cargo fetch --manifest-path $(SOURCE_DIR)/Cargo.toml ; \
        for patchfile in patches-crate/*.patch; do \
                gpatch $(CRATE_PATCH_FLAG) < $$patchfile ; \
        done ;

COMPONENT_TEST_ENV += LC_ALL=C.UTF-8
COMPONENT_TEST_CMD= gmake
COMPONENT_TEST_TARGETS= fish_run_tests

# strip timing
COMPONENT_TEST_TRANSFORMS += "-e 's/ ms//g'"
COMPONENT_TEST_TRANSFORMS += "-e 's/ [0-9]*$$//'"
# remove terminal color codes
COMPONENT_TEST_TRANSFORMS += "-e 's/\x1B\[32mPASSED\x1B\[0m/PASSED/g'"
COMPONENT_TEST_TRANSFORMS += "-e 's/\x1B\[31mFAILED\x1B\[0m/FAILED/g'"
# only keep the test result lines
COMPONENT_TEST_TRANSFORMS += -n
COMPONENT_TEST_TRANSFORMS += '-e "/FAILED/p" '
COMPONENT_TEST_TRANSFORMS += '-e "/PASSED/p" '

PKG_HARDLINKS += usr/bin/fish

# Manually added dependencies (for tests)
PYTHON_REQUIRED_PACKAGES += library/python/pexpect

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
