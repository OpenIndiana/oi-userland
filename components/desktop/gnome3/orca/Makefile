##
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2014 Alexander Pyhalov
# Copyright (c) 2014 Ken Mays
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         orca
COMPONENT_VERSION=      3.24.0
COMPONENT_REVISION=     2
COMPONENT_PROJECT_URL=  http://www.gnome.org
COMPONENT_SUMMARY=      Orca screen reader/magnifier
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:27bd5e4eee12da737176a200b31d33e118d55ae832a4e3f0cbd3e756027246d1
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/3.24/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	gnome/accessibility/orca
COMPONENT_CLASSIFICATION=Applications/Universal Access
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=$(ETCDIR)

CONFIGURE_ENV+= PYTHON="$(PYTHON)"
CONFIGURE_ENV+= am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV+= am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pyatspi2
PYTHON_REQUIRED_PACKAGES += library/python/pygobject-3
PYTHON_REQUIRED_PACKAGES += runtime/python
