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
# Copyright 2026 isoriano1968
#

BUILD_STYLE=		meson

include ../../../../make-rules/shared-macros.mk

# 45.x is the last GTK3/libhandy release; 46 needs Python >= 3.10
# PyGObject and libgudev
COMPONENT_NAME=		gnome-tweaks
HUMAN_VERSION=		45.1
COMPONENT_SUMMARY=	GNOME Tweaks - advanced GNOME settings
COMPONENT_ARCHIVE_HASH=	\
	sha256:95ffa7f38d9b1dfd5e4cebefb752419fea21cd407021395adc9f112854416d4f
COMPONENT_FMRI=		gnome/preferences/gnome-tweaks
COMPONENT_CLASSIFICATION=	Applications/Configuration and Preferences
COMPONENT_LICENSE=	GPL-3.0-or-later AND CC0-1.0

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		printf '%s\n\n' '--- LICENSES/GPL-3.0 ------------------------------------------------------' ; \
		$(CAT) $(SOURCE_DIR)/LICENSES/GPL-3.0 ; \
		printf '\n\n%s\n\n' '--- LICENSES/CC0-1.0 ------------------------------------------------------' ; \
		$(CAT) $(SOURCE_DIR)/LICENSES/CC0-1.0 \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

CONFIGURE_OPTIONS +=	-Dpython.purelibdir=$(PYTHON_VENDOR_PACKAGES)

PYTHON_SCRIPTS +=	usr/bin/gnome-tweaks

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/pygobject
REQUIRED_PACKAGES.python += runtime/python
