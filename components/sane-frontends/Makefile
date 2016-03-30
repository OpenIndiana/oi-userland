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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		sane-frontends
COMPONENT_VERSION=	1.0.14
COMPONENT_PROJECT_URL=	http://www.sane-project.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:e7839dac1b70b5bb39124615aba8a136f5275d0e78bafd3d52ed76964ffea4a9
COMPONENT_ARCHIVE_URL=	ftp://ftp2.sane-project.org/pub/sane/sane-frontends-1.0.14/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libsane

TPNO=			8865

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsane

CONFIGURE_OPTIONS +=	--with-sane-prefix=$(USRDIR)
CONFIGURE_OPTIONS +=	--disable-sanetest
CONFIGURE_OPTIONS +=	--disable-gtktest
CONFIGURE_OPTIONS +=	--disable-gimptest
CONFIGURE_OPTIONS +=	--disable-gimp

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

REQUIRED_PACKAGES += image/scanner/xsane/sane-backends
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
