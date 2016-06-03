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

BUILD_BITS =            32_and_64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER=gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgsf
COMPONENT_VERSION=	1.14.34
COMPONENT_ARCHIVE_HASH=	\
	sha256:f0fea447e0374a73df45b498fd1701393f8e6acb39746119f8a292fb4a0cb528
COMPONENT_BUGDB=        gnome/libraries

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

TPNO=			24756

include $(WS_MAKE_RULES)/gnome-component.mk

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

CONFIGURE_OPTIONS += --disable-static
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-bz2
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-zlib

# for the tests
unexport SHELLOPTS
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
