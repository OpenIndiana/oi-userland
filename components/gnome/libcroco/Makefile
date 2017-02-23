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

BUILD_BITS =		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libcroco
COMPONENT_VERSION=	0.6.8
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Libcroco
COMPONENT_ARCHIVE_HASH=	\
    sha256:ea6e1b858c55219cefd7109756bff5bc1a774ba7a55f7d3ccd734d6b871b8570
COMPONENT_BUGDB=	gnome/libraries
COMPONENT_ANITYA_ID=	11787

TPNO=			24633

include $(WS_MAKE_RULES)/gnome-component.mk

# Needed because of patch to configure.in.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

# Actually, -Bsymbolic-functions; the option is misnamed -- Solaris linker
# doesn't support -Bsymbolic-functions currently.
CONFIGURE_OPTIONS += --disable-Bsymbolic
CONFIGURE_OPTIONS += --disable-static

# Needed to make tests work
COMPONENT_TEST_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_TRANSFORMS += '-e "/^removing tests/d"'
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/glib2
