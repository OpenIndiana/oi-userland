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

BUILD_BITS=             32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-themes-standard
COMPONENT_VERSION=	3.18.0
COMPONENT_ARCHIVE_HASH= \
	sha256:e646eb04c225282b7df7fff65741adaad4cf9ed2c12616b7310e7edd27d2bacb
COMPONENT_BUGDB=        gnome/themes

TPNO=			24753

TEST_TARGET = $(NO_TESTS)

# Needs updated glib2, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# Assumes GNU find is first in path during build & install process.
CONFIGURE_ENV 		+= PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV 	+= PATH="$(GNUBIN):$(PATH)"
COMPONENT_INSTALL_ENV 	+= PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
