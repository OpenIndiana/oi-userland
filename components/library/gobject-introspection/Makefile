#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Marcel Telka <marcel@telka.sk>
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2019 Michal Nowak
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

# Odd minor versions are unstable.
# https://gi.readthedocs.io/en/latest/changelog.html

COMPONENT_NAME =		gobject-introspection
HUMAN_VERSION =			1.86.0
COMPONENT_SUMMARY =		Introspection for GObject libraries
COMPONENT_ARCHIVE_HASH =	sha256:920d1a3fcedeadc32acff95c2e203b319039dd4b4a08dd1a2dfd283d19c0b9ae
COMPONENT_FMRI =		library/desktop/gobject/gobject-introspection
COMPONENT_CLASSIFICATION =	Development/GNOME and GTK+
COMPONENT_LICENSE =		GPL-2.0-or-later AND LGPL-2.0-or-later AND MIT

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		$(CAT) $(SOURCE_DIR)/COPYING ; \
		printf '\n--- COPYING.GPL -----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.GPL ; \
		printf '\n--- COPYING.LGPL ----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.LGPL \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

CONFIGURE_ENV += PYTHON=$(PYTHON)

PYTHON_SCRIPTS += usr/bin/g-ir-annotation-tool
PYTHON_SCRIPTS += usr/bin/g-ir-doc-tool
PYTHON_SCRIPTS += usr/bin/g-ir-scanner

# Build dependencies
# Both mako and markdown are needed for doctool (see meson.build)
REQUIRED_PACKAGES.python += library/python/mako
REQUIRED_PACKAGES.python += library/python/markdown

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES.python += runtime/python
