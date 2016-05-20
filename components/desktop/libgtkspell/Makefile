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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtkspell
COMPONENT_VERSION=	2.0.16
COMPONENT_PROJECT_URL=	http://gtkspell.sourceforge.net/
COMPONENT_ARCHIVE_HASH= \
    sha256:8fc7dc560167b2cb7193e76aca625a152dc19b0ebf49816b78539cbb90d80d02
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/gtkspell

TPNO=			11953

# Was not version-lock'd in Desktop, so cannot be upgraded to.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Needed to pick up the GNU version of xgettext.
PATH =		$(GNUBIN):$(USRBINDIR)

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; \
	libtoolize --force --copy ; \
	aclocal -I . ; \
	libtoolize --force ; \
	autoheader ; \
	automake -a -c -f ; \
	autoconf )

ASLR_MODE =	$(ASLR_ENABLE)

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += library/spell-checking/enchant
