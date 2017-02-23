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
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		meld
COMPONENT_VERSION=	3.16.4
COMPONENT_PROJECT_URL=	http://meldmerge.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:93c4f928319dae7484135ab292fe6ea4254123e8219549a66d3e2deba6a38e67
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/gnome/sources/meld/1.8/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/3.16/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	5520

TPNO=			33168

# We just need to build one version.
PYTHON_VERSIONS =       2.7

ifneq ($(BUILD_TYPE), evaluation)
BUILD_STYLE= setup.py
endif
TEST_TARGET=	$(TEST_64)

# Needs older version of libpng, no longer available in evaluation builds.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# Needed to find GNU xgettext.
PATH =			$(GNUBIN):$(USRBINDIR)

PKG_MACROS +=		PYVER=$(PYTHON_VERSION)

PYTHON_DATA =		/usr

COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/test
COMPONENT_TEST_CMD =    /usr/bin/py.test
COMPONENT_TEST_ARGS =

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(in \).*\(seconds\).*|\1 x \2|"' \
	'-n ' \
	'-e "/^===/p" '

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

REQUIRED_PACKAGES += developer/intltool
REQUIRED_PACKAGES += library/desktop/gtksourceview3
REQUIRED_PACKAGES += library/gnome/gnome-common
REQUIRED_PACKAGES += library/python/pycairo-27
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += text/gnu-gettext
