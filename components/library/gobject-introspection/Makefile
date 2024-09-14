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

# IMPORTANT if the umask of the builder isn't set to 0022
# the resulting: /usr/lib/sparcv9/gobject-introspection/giscanner/__pycache__
# directory ends up with 700 - in the final installation and therefore
# can't be used by end-users !!!

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gobject-introspection
HUMAN_VERSION =			1.82.0
COMPONENT_SUMMARY =		Introspection for GObject libraries
COMPONENT_ARCHIVE_HASH =	sha256:0f5a4c1908424bf26bc41e9361168c363685080fbdb87a196c891c8401ca2f09
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

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^Ok/p" ' \
	'-e "/^Expected/p" ' \
	'-e "/^Fail/p" ' \
	'-e "/^Unexpected/p" ' \
	'-e "/^Skipped/p" ' \
	'-e "/^Timeout/p" '

PYTHON_SCRIPTS += usr/bin/g-ir-annotation-tool
PYTHON_SCRIPTS += usr/bin/g-ir-doc-tool
PYTHON_SCRIPTS += usr/bin/g-ir-scanner

# Build dependencies
# Both mako and markdown are needed for doctool (see meson.build)
PYTHON_REQUIRED_PACKAGES += library/python/mako
PYTHON_REQUIRED_PACKAGES += library/python/markdown

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
