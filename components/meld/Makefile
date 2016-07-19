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
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		meld
COMPONENT_VERSION=	3.16.1
COMPONENT_PROJECT_URL=	http://meldmerge.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1bec697aa1ababa315ca8241ade65dc68ea87f0d316632f590975afcf967cfab
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/gnome/sources/meld/1.8/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/3.16/$(COMPONENT_ARCHIVE)

TPNO=			30088

# We just need to build one version.
PYTHON_VERSIONS =       2.7

BUILD_STYLE= setup.py
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Needed to find GNU xgettext.
PATH =			$(GNUBIN):$(USRBINDIR)

PKG_MACROS +=		PYVER=$(PYTHON_VERSION)

PYTHON_DATA =		/usr

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

REQUIRED_PACKAGES += developer/gnome/gettext
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += text/gnu-gettext
