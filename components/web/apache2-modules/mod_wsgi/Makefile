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
COMPONENT_VERSION=	4.5.22
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d8205b1ebe6042e21a7a59fbfe10c4c5a12753bac531879758bdf2fa8e2bf301
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/aa/a5/909ecab8a101afb57de4815250d6fa23fcc1b94d095f6d56a9c15d7425fa/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://pypi.python.org/pypi/mod_wsgi/
COMPONENT_BUGDB=	utility/apache

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSIONS = 2.7 3.4

APACHE_USR_PREFIX=/usr/apache2/2.4

CFLAGS += -D__EXTENSIONS__

COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fi)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS+= -std=c99 $(CPP_XPG6MODE)

# The following four paragraphs are copied from setup.py.mk
# but since mod_wsgi doesn't use setup.py, we can't just include
# setup.py.mk
$(BUILD_DIR)/%-2.7/.built:		PYTHON_VERSION=2.7
$(BUILD_DIR)/%-3.4/.built:		PYTHON_VERSION=3.4
$(BUILD_DIR)/$(MACH32)-%/.built:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64

$(BUILD_DIR)/%-2.7/.installed:  PYTHON_VERSION=2.7
$(BUILD_DIR)/%-3.4/.installed:  PYTHON_VERSION=3.4
$(BUILD_DIR)/$(MACH32)-%/.installed:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64

BUILD_32 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.built)
BUILD_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)

INSTALL_32 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.installed)
INSTALL_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)

$(BUILD_32): CONFIGURE_OPTIONS += --with-apxs=$(APACHE_USR_PREFIX)/bin/apxs --with-python=$(PYTHON.32) 
$(BUILD_64): CONFIGURE_OPTIONS += --with-apxs=$(APACHE_USR_PREFIX)/bin/$(MACH64)/apxs --with-python=$(PYTHON.64)

COMPONENT_POST_INSTALL_ACTION = $(TOUCH) $(BUILD_DIR)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/server/apache-24
