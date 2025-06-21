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
# Copyright 2025 Andreas Wacknitz
#

BUILD_STYLE= cargo
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		scryer-prolog
COMPONENT_VERSION=	0.9.4
COMPONENT_SUMMARY=	Scryer Prolog is a free software ISO Prolog system intended to be an industrial strength production environment
COMPONENT_PROJECT_URL= https://www.scryer.pl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/mthom/scryer-prolog/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ccf533c5c34ee7efbf9c702dbffea21ba1c837144c3592a9e97c515abd4d6904
COMPONENT_FMRI=		runtime/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/System
COMPONENT_LICENSE=	BSD 3-Clause
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += MAKE=gmake

# Need to patch libc to add headers from sys/time_impl.h
# Download all dependency crates and then apply patch.
CRATE_PATCH_FLAG = --backup --version-control=numbered -p0
COMPONENT_PRE_BUILD_ACTION= \
        CARGO_HOME=$(@D)/cargo-vendor cargo fetch --manifest-path $(SOURCE_DIR)/Cargo.toml ; \
        for patchfile in patches-crate/*.patch; do \
                gpatch $(CRATE_PATCH_FLAG) < $$patchfile ; \
        done ;

COMPONENT_POST_INSTALL_ACTION += ( \
	$(MKDIR) $(PROTOUSRSHAREDIR)/scryer-prolog ; \
	$(CP) $(SOURCE_DIR)/README.md $(PROTOUSRSHAREDIR)/scryer-prolog/ ; );

# Manually added build dependencies
REQUIRED_PACKAGES += developer/lang/rustc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
