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

BUILD_BITS=		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-common
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/GnomeCommon
COMPONENT_ARCHIVE_HASH= \
    sha256:22569e370ae755e04527b76328befc4c73b62bfd4a572499fde116b8318af8cf
COMPONENT_BUGDB=	gnome/libraries
COMPONENT_ANITYA_ID=	8421

TPNO=			25944

# Forked from gnome/gettext, which was in Gnome in 11.3 => do-not-publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_NO_ARCH=
INSTALL_NO_ARCH=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

REQUIRED_PACKAGES += developer/build/automake-115
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/intltool
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-common
REQUIRED_PACKAGES += text/gnu-gettext
