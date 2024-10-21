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
# Copyright 2022, Benny Lyons
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py


include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glances
COMPONENT_VERSION=	3.2.7
COMPONENT_SUMMARY=      Monitoring system resources
COMPONENT_FMRI=         diagnostic/glances
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_PROJECT_URL=	https://github.com/nicolargo/glances
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8eee819667b39e20f8ba3881dbe5c148146baf2da880a78e5ed184a8f790abd0
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
#https://github.com/nicolargo/glances/archive/refs/tags/v3.2.7.tar.gz
#COMPONENT_ARCHIVE_URL=$(call pypi_url)
COMPONENT_LICENSE=      LGPL-3.0-only
COMPONENT_LICENSE_FILE=$(COMPONENT_SRC)/LICENSES/LGPL-3.0-only.txt
#PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)
PYTHON_VERSIONS=	3.9
PYTHON_VERSION=	3.9

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += PYVER=$(PYTHON_VERSION)
# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python$(PYTHON_VERSION)'
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's?env python?python$(PYTHON_VERSION)?' \
                $(PROTOUSRBINDIR)/*;

SHARE_DIR=$(PROTO_DIR)/usr/share
PIXMAPS_DIR=$(PROTOUSRSHAREDIR)/pixmaps
APPLICATIONS_DIR=$(PROTOUSRSHAREDIR)/applications

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) -p $(PIXMAPS_DIR); \
	$(CP) $(COMPONENT_SRC)/glances/outputs/static/images/glances.png $(PIXMAPS_DIR)/glances.png;
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) -p $(PROTOUSRSHAREDIR)/applications; \
	$(CP) $(COMPONENT_DIR)/glances.desktop $(PROTOUSRSHAREDIR)/applications/glances.desktop;
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) -p $(PROTOUSRSHAREDIR)/man/man1; \
	$(CP) $(COMPONENT_SRC)/docs/man/glances.1 $(PROTOUSRSHAREDIR)/man/man1/glances.1;

REQUIRED_PACKAGES += print/psutils

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
