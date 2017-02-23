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
# Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		xmlto
COMPONENT_VERSION=	0.0.28
COMPONENT_PROJECT_URL=	https://fedorahosted.org/xmlto/
COMPONENT_ARCHIVE_HASH= \
    sha256:2f986b7c9a0e9ac6728147668e776d405465284e13c74d4146c9cbc51fd8aad3
COMPONENT_ARCHIVE_URL=	 https://fedorahosted.org/releases/x/m/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13307

TPNO=			27193

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

# These will be used by the xmlto script.
CONFIGURE_ENV += FIND="$(GNUBIN)/find"
CONFIGURE_ENV += GETOPT="$(GNUBIN)/getopt"
CONFIGURE_ENV += GREP="$(GNUBIN)/grep"
CONFIGURE_ENV += TAIL="$(GNUBIN)/tail"

# Strip compilation lines from test output
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*xmlif.l.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

COMPONENT_SYSTEM_TEST_ENV += top_srcdir=$(SOURCE_DIR)
COMPONENT_SYSTEM_TEST_ENV += top_builddir=$(BUILD_DIR)
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	$(GSED) -i -e "s|^XMLIF=.*$$|XMLIF=/usr/bin/xmlif|" \
	$(SOURCE_DIR)/xmlif/test/run-test

# Used by this Makefile.
REQUIRED_PACKAGES += text/gnu-sed

REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += file/gnu-findutils
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/gnu-getopt
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += web/browser/lynx
