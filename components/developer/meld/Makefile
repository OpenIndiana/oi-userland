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

BUILD_BITS=	64
BUILD_STYLE= meson 

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		meld
COMPONENT_VERSION=	3.21.3
COMPONENT_FMRI=		developer/$(COMPONENT_NAME)
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
COMPONENT_ARCHIVE_HASH= sha256:c5a9c628c68287a6cf576d8d82041e8080a5dd5c12cb4d709ac2994aa0b1b197
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/meld/3.21/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	meld.license
COMPONENT_CLASSIFICATION=	Development/Editors

include $(WS_MAKE_RULES)/common.mk

PYTHON_VERSIONS =	 3.9

PATH=$(PATH.gnu)

# Don't build and package these, they need to be generated on install to
# reflect all the other packages installed on the machine too, not just meld
COMPONENT_SETUP_ARGS += --no-compile-schemas
COMPONENT_SETUP_ARGS += --no-update-icon-cache

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRLIBDIR)/python3.9/vendor-packages; \
        $(MV) $(PROTOUSRLIBDIR)/python3.9/site-packages/* $(PROTOUSRLIBDIR)/python3.9/vendor-packages/; \
	python3.9 -m compileall $(PROTOUSRLIBDIR)/python3.9/vendor-packages;

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*[0-9].[0-9][0-9]s//" '
COMPONENT_TEST_TRANSFORMS += '-e "s/OK      [0-9]//" '
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/OK/p" ' \
        '-e "/Ok/p" ' \
        '-e "/Pass/p" ' \
        '-e "/Fail/p" '

# Runtime dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/desktop/gtksourceview4
REQUIRED_PACKAGES += library/python/pycairo-39
REQUIRED_PACKAGES += text/itstool

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pygobject-3-39
REQUIRED_PACKAGES += runtime/python-39
