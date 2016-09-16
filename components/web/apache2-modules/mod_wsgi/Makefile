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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_wsgi
COMPONENT_VERSION=	4.5.7
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:5d8e7789f6b2c84696bf58da6e6489246722e13a7ed137f7c9b32f8010017250
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/28/a7/de0dd1f4fae5b2ace921042071ae8563ce47dac475b332e288bc1d773e8d/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://code.google.com/p/modwsgi/
COMPONENT_BUGDB=	utility/apache

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSIONS = 2.7 3.4

APACHE_USR_PREFIX=/usr/apache2/2.2

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# The following four paragraphs are copied from setup.py.mk
# but since mod_wsgi doesn't use setup.py, we can't just include
# setup.py.mk
$(BUILD_DIR)/%-2.7/.built:		PYTHON_VERSION=2.7
$(BUILD_DIR)/%-3.4/.built:		PYTHON_VERSION=3.4
$(BUILD_DIR)/$(MACH32)-%/.built:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64

$(BUILD_DIR)/%-2.7/.installed:  PYTHON_VERSION=2.7
$(BUILD_DIR)/%-3.4/.installed:  PYTHON_VERSION=2.7
$(BUILD_DIR)/$(MACH32)-%/.installed:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64

BUILD_32 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.built)
BUILD_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)

INSTALL_32 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.installed)
INSTALL_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)

$(BUILD_32): CONFIGURE_OPTIONS += --with-apxs=$(APACHE_USR_PREFIX)/bin/apxs --with-python=$(PYTHON.32) 
$(BUILD_64): CONFIGURE_OPTIONS += --with-apxs=$(APACHE_USR_PREFIX)/bin/$(MACH64)/apxs --with-python=$(PYTHON.64)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/server/apache-22
