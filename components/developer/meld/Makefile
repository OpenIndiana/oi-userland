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
# Copyright 2016 Jim Klimov
# Copyright 2021 Nona Hansel
# Copyright (c) 2011, 2021, Oracle and/or its affiliates.
#

BUILD_STYLE= meson
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		meld
COMPONENT_MJR_VERSION=	3.22
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).3
COMPONENT_SUMMARY=	meld - graphical diff and merge tool
COMPONENT_DESCRIPTION=\
Meld is a visual diff and merge tool. You can compare two or three files \
and edit them in place (diffs update dynamically). You can compare two or \
three folders and launch file comparisons. You can browse and view a working \
copy from popular version control systems such such as Git, CVS, Subversion, \
Bazaar-ng and Mercurial.
COMPONENT_PROJECT_URL=	https://meld.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:37f7f29eb1ff0fec4d8b088d5483c556de1089f6d018fe6d481993caf2499d84
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/meld/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Editors
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Don't build and package these, they need to be generated on install to
# reflect all the other packages installed on the machine too, not just meld
COMPONENT_SETUP_ARGS += --no-compile-schemas
COMPONENT_SETUP_ARGS += --no-update-icon-cache

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRLIBDIR)/python3.9/vendor-packages; \
	$(MV) $(PROTOUSRLIBDIR)/python3.9/site-packages/* $(PROTOUSRLIBDIR)/python3.9/vendor-packages/; \
	$(PYTHON) -m compileall $(PROTOUSRLIBDIR)/python3.9/vendor-packages;

# Manually added dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pycairo
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/desktop/gtksourceview4
REQUIRED_PACKAGES += text/itstool

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pygobject
PYTHON_REQUIRED_PACKAGES += library/python/tkinter
PYTHON_REQUIRED_PACKAGES += runtime/python
