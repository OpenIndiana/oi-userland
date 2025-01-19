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
# Copyright 2023 Niklas Poslovski
# Copyright 2025 Andreas Wacknitz
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsoup
HUMAN_VERSION=		3.6.4
COMPONENT_SUMMARY= Libsoup is an HTTP client/server library for GNOME
COMPONENT_ARCHIVE_HASH=	sha256:9b54c76f5276b05bebcaf2b6c2a141a188fc7bb1d0624eda259dac13a6665c8a
COMPONENT_PROJECT_URL= https://wiki.gnome.org/Projects/libsoup
COMPONENT_FMRI= library/libsoup3
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	LGPL-2.0-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH= $(PATH.gnu)

# Testing needs apachectl and httpd
PATH.prepend += /usr/apache2/2.4/bin

# Manually added dependencies
PYTHON_REQUIRED_PACKAGES += library/python/gi-docgen
TEST_REQUIRED_PACKAGES += web/server/apache-24
REQUIRED_PACKAGES += library/glib-networking

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpsl
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
