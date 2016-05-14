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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=             NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-doc-utils
COMPONENT_VERSION=	0.20.10
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/GnomeDocUtils
COMPONENT_ARCHIVE_HASH= \
    sha256:cb0639ffa9550b6ddf3b62f3b1add92fb92ab4690d351f2353cffe668be8c4a6
COMPONENT_BUGDB=	gnome/dev-tools

TPNO=			24907

# Only supports Python 2.x.
PYTHON_VERSIONS= 2.7

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/gnome-component.mk

# The build process modifies the shebang line to use the version of Python
# automatically found; to avoid using the current system default, one is
# explicitly specified here.
CONFIGURE_ENV += PYTHON="$(PYTHON.2.7)"

# Ensure Python modules are installed to vendor-packages directory;
# the default is site-packages.
CONFIGURE_OPTIONS += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)

# Assumes GNU xgettext in PATH.
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

REQUIRED_PACKAGES += data/docbook
REQUIRED_PACKAGES += data/docbook/docbook-dtds
REQUIRED_PACKAGES += data/docbook/docbook-style-dsssl
REQUIRED_PACKAGES += data/docbook/docbook-style-xsl 
REQUIRED_PACKAGES += data/sgml-common
REQUIRED_PACKAGES += data/xml-common
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/perl-5/xml-parser-522
REQUIRED_PACKAGES += library/python/libxml2-27
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += service/gnome/desktop-cache
