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
# Copyright (c) 2018 Jason Martin
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     gdl
HUMAN_VERSION=			3.40.0
COMPONENT_SUMMARY=  Gnome Docking library
COMPONENT_ARCHIVE_HASH=		sha256:3641d4fd669d1e1818aeff3cf9ffb7887fc5c367850b78c28c775eba4ab6a555
COMPONENT_CLASSIFICATION= Development/GNOME and GTK+
COMPONENT_FMRI=     library/libgdl
COMPONENT_LICENSE=		LGPL-2.0-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH = $(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
