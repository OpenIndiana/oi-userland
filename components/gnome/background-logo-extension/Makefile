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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		background-logo-extension
COMPONENT_VERSION=	3.20.0
COMPONENT_PROJECT_URL=  https://extensions.gnome.org/extension/889/background-logo
COMPONENT_ARCHIVE_HASH= \
	sha256:9a0480fcf82214c6fac54485d5e91be485b2b8517df2fad853bfeba534c00f6b
COMPONENT_ARCHIVE_URL=	https://git.fedorahosted.org/cgit/$(COMPONENT_NAME).git/snapshot/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13118

TPNO=			29309

TEST_TARGET = $(NO_TESTS)

# This is for Gnome 3 so shouldn't apply to S11
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# configure assumes the extension version matches the gnome-shell version,
# so override that for now, since our version numberss are out of sync
COMPONENT_PREP_ACTION += \
    $(GSED) -i -e 's/@shell_version@/3.18/' $(@D)/metadata.json.in ;

# tarballs include autogen.sh, but not pre-generated configure script
COMPONENT_PREP_ACTION += ( cd $(@D) ; NOCONFIGURE=1 $(CONFIG_SHELL) autogen.sh );

REQUIRED_PACKAGES += gnome/gnome-shell
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/gnome/gnome-desktop
