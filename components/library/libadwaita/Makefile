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
# Copyright 2024 Geoff Weiss
#

include ../../../make-rules/shared-macros.mk
ENV= /usr/bin/env

COMPONENT_NAME=		libadwaita
COMPONENT_VERSION=	1.5.4
COMPONENT_SUMMARY=	Building blocks for modern GNOME applications.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:1c7ebf9d03fbd50485831099c6a04670dc5399a5a832d900832301dbf22f9589
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/1.5/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://gnome.pages.gitlab.gnome.org/libadwaita/doc/
COMPONENT_LICENSE=	LGPLv2.1+
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_FMRI=		library/desktop/libadwaita

BUILD_STYLE=		meson

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Some warnings are treated as errors by default but we do not want that
CFLAGS += -Wno-error=format-nonliteral

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Remove the empty line after the 'Summary of Failures:'
COMPONENT_TEST_TRANSFORMS += "-e '/^Summary of Failures:/{n; N; D; }' | $(COMPONENT_TEST_TRANSFORMER)"
# Remove the list of failed tests so we do not see the failed tests twice
COMPONENT_TEST_TRANSFORMS += "-e '/^Summary of Failures:/,/^\$$/d'"
# By default ignore all lines
COMPONENT_TEST_TRANSFORMS += "-n"
# Print the individual test result with removed test number and timing
COMPONENT_TEST_TRANSFORMS += "-e '/^ *[0-9]\{1,\}\/[0-9]\{1,\} /{s///; s/ \{1,\}[0-9]*[0-9]\.[0-9][0-9]s//; p; }'"
# Print the test summary too
COMPONENT_TEST_TRANSFORMS += "-e '/^Ok:/,/^\$$/p'"
# Include empty line before the test summary
COMPONENT_TEST_TRANSFORMS += "| $(COMPONENT_TEST_TRANSFORMER) -e '/^Ok:/{H; x; }'"
# Sort test results
COMPONENT_TEST_TRANSFORMS += "| ( \
		$(GSED) -u -e '/^\$$/Q' | $(SORT) | $(COMPONENT_TEST_TRANSFORMER) -e '\$$G' ; \
		$(CAT) \
	) | $(COMPONENT_TEST_TRANSFORMER) -e ''"

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/appstream
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
