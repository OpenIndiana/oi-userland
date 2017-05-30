#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		flex
COMPONENT_VERSION=	2.6.4
COMPONENT_PROJECT_URL=	https://github.com/westes/flex
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4df278468142e457a9e5f6492a7d39fdb34bd7e7d42ec21b3c382889b34cfefe
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	819

TPNO=			35362

LDFLAGS += $(CC_BITS)

# Evaluation builds (x86 full builds only) fail generating .po files.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION +=	( cd $(@D) ; $(CONFIG_SHELL) autogen.sh );

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		M4="$(GNUBIN)/m4"

# Needed to pick up GNU sed for correct message formatting.
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

COMPONENT_TEST_ENV +=		PATH=$(GNUBIN):$(USRBINDIR)
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/=====/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

REQUIRED_PACKAGES += developer/documentation-tool/help2man
REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += system/library/math
