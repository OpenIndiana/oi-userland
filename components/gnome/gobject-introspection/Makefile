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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

# gobject-introspection must be built with gcc as gobject-introspection does
# not produce correct results when using Studio and the source code itself does
# not build successfully.
COMPILER =		gcc
BUILD_BITS =		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gobject-introspection
COMPONENT_VERSION=	1.46.0
COMPONENT_ARCHIVE_HASH= \
    sha256:6658bd3c2b8813eb3e2511ee153238d09ace9d309e4574af27443d87423e4233
COMPONENT_BUGDB=        gnome/libraries

TPNO=			25403

# Requires newer version of library/glib2, not buildable on 11.3, so do not
# publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

# Not compatible with Python 3.x.
PYTHON_VERSION =	2.7
PYTHON_VERSIONS =	$(PYTHON_VERSION)

# Ensure system default Python is not used.
CONFIGURE_ENV += PYTHON=$(PYTHON)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-cairo

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env ...' so turn it into '#!/usr/bin/python2.7'
GIR_PY_SCRIPTS = g-ir-annotation-tool g-ir-doc-tool g-ir-scanner
# This uses $(PROTO_DIR)$(USRBIN) instead of $(PROTOUSRBINDIR)
# so that it expands to the right path for each BUILD_BITS type
PYTHON_SCRIPTS += $(GIR_PY_SCRIPTS:%=$(PROTO_DIR)$(USRBIN)/%)

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS
COMPONENT_TEST_ENV += GI_SCANNER_DISABLE_CACHE=""
COMPONENT_TEST_ENV += CC="$(CC)"
COMPONENT_TEST_ENV += CFLAGS="$(strip $(CFLAGS))"
COMPONENT_TEST_ENV += LDFLAGS="$(strip $(LDFLAGS))"
COMPONENT_TEST_ENV += PATH="$(GNUBIN):$(PATH)"

# Standard automake test framework results transform
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL/p" ' \
        '-e "/SKIP/p" ' \
        '-e "/PASS/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/ERROR/p" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Requires bison >= 3.0
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/iconv/iconv-core
REQUIRED_PACKAGES += system/library/math
