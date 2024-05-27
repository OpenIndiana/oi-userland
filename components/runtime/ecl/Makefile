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
# Copyright 2024 Andreas Wacknitz
#

USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ecl
COMPONENT_VERSION=	24.5.10
COMPONENT_SUMMARY=	ecl - Embeddable Common-Lisp
COMPONENT_PROJECT_URL=	https://common-lisp.net
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:e4ea65bb1861e0e495386bfa8bc673bd014e96d3cf9d91e9038f91435cbe622b
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/project/ecl/static/files/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		runtime/ecl
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=	LGPLv2.1+
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

ECL= $(PROTO_DIR)/usr/bin/ecl

COMPONENT_PRE_CONFIGURE_ACTION= ( CLONEY_MODE=copy $(CLONEY) $(SOURCE_DIR) $(@D) )

# At the moment tests need the already installed ecl as using ecl from the proto area fails with a path error.
COMPONENT_PRE_TEST_ACTION += \
	$(GSED) -i "s|ECL=/usr//usr/bin/ecl|ECL=/usr/bin/ecl|" $(BUILD_DIR)/$(MACH64)/build/tests/Makefile

#COMPONENT_TEST_ENV += PATH=$(PROTOUSRBINDIR):$(PATH)
#COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(PROTOUSRLIBDIR$(BITS))

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
