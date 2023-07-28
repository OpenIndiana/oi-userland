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
# Copyright 2016 Jim Klimov
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright 2019 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		augeas
COMPONENT_VERSION=	1.14.1
COMPONENT_SUMMARY=	Augeas is a utility for editing configuration files
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:368bfdd782e4b9c7163baadd621359c82b162734864b667051ff6bcb57b9edff
COMPONENT_ARCHIVE_URL=	https://github.com/hercules-team/$(COMPONENT_NAME)/releases/download/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://augeas.net/index.html
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --disable-dependency-tracking
CONFIGURE_OPTIONS += --disable-static

# Needed for "gmake test" to work.
# SHELLOPTS is exported via make-rules/shared-macros.mk,
# causing the braceexpand option to be set.
# This option causes "$1: unbound variable" errors during the check-TESTS,
# and the gnulib-tests don't even run at all.
# Note that the below unexports SHELLOPTS, even for targets
# other than "test."
unexport SHELLOPTS

COMPONENT_TEST_ARGS		= -k
COMPONENT_TEST_TRANSFORMER	= $(NAWK)
COMPONENT_TEST_TRANSFORMS	= "'/TOTAL|FAIL/'"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
