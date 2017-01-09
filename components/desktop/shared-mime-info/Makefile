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
# Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		shared-mime-info
COMPONENT_VERSION=	0.80
COMPONENT_PROJECT_URL=	https://freedesktop.org/wiki/Software/shared-mime-info/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:80857ba19f8066bfc8d998bfc72b492e241ebd52d49c245aae9fd5b3d233b024
COMPONENT_ARCHIVE_URL=	http://freedesktop.org/~hadess/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/libraries

TPNO=			9300

# Does not build correctly with S11 version of intltool, and cannot be
# installed on S11 since it conflicts with S11 gnome-vfs package
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# Requires gnu versions of xgettext & msgfmt first in $PATH
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += developer/intltool
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += text/gnu-gettext
