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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=            	32_and_64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtk-engines
COMPONENT_VERSION=	2.20.2
COMPONENT_PROJECT_URL=	http://www.gtk.org/
COMPONENT_ARCHIVE=	gtk-engines-2.20.2.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:15b680abca6c773ecb85253521fa100dd3b8549befeecc7595b10209d62d66b5
COMPONENT_BUGDB=	gnome/libraries
COMPONENT_ANITYA_ID=	13141

TPNO=			8678

# Requires updated version of gtk2, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# 32-bit gcc builds cause segfaults; see bug 21393975.
gcc_OPT.i386.32 = -O2

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

COMPONENT_BUILD_ENV += LD_SHARED_OPTIONS="$(LD_OPTIONS_SO) -lm"

CONFIGURE_OPTIONS += --disable-lua
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-all
CONFIGURE_OPTIONS += --enable-animation
# --disable-deprecated actually disables the -D *_DISABLE_DEPRECATED flags
# that hide deprecated functions in the headers, thus enabling the engines
# to build properly
CONFIGURE_OPTIONS += --disable-deprecated
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

unexport SHELLOPTS
COMPONENT_TEST_TRANSFORMS += '-e "s|$(PROTO_DIR)|\\$$(PROTO_DIR)|g"'
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/math
