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

include ../../../make-rules/shared-macros.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		mod_wsgi
COMPONENT_VERSION=	3.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d96e1078990484cfe5579df1e95dc73f009495e9c3f9a066b0983650bd9e3243
COMPONENT_ARCHIVE_URL=	http://modwsgi.googlecode.com/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://code.google.com/p/modwsgi/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# The following four paragraphs are copied from setup.py.mk
# but since mod_wsgi doesn't use setup.py, we can't just include
# setup.py.mk
$(BUILD_DIR)/%-2.6/.built:		PYTHON_VERSION=2.6
$(BUILD_DIR)/%-2.7/.built:		PYTHON_VERSION=2.7
$(BUILD_DIR)/$(MACH32)-%/.built:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64

$(BUILD_DIR)/%-2.6/.installed:	PYTHON_VERSION=2.6
$(BUILD_DIR)/%-2.7/.installed:  PYTHON_VERSION=2.7
$(BUILD_DIR)/$(MACH32)-%/.installed:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64

BUILD_32 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.built)
BUILD_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)

INSTALL_32 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.installed)
INSTALL_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)

$(BUILD_32): CONFIGURE_OPTIONS += --with-python=$(PYTHON.32)
$(BUILD_64): CONFIGURE_OPTIONS += --with-apxs=/usr/bin/$(MACH64)/apxs --with-python=$(PYTHON.64)

$(INSTALL_32): COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/apache2/2.2/libexec ; \
		$(MV) mod_wsgi.so mod_wsgi-$(PYTHON_VERSION).so)

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/apache2/2.2/libexec/$(MACH64) ; \
		$(MV) mod_wsgi.so mod_wsgi-$(PYTHON_VERSION).so)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)
