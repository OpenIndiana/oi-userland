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
# Copyright (c) 2012, 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_wsgi
COMPONENT_VERSION=	4.3.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:89dfcc8564bb8781f36370c80c6fbeef9ec0723dec273231f4f760760d8e813d
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/m/mod_wsgi/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://code.google.com/p/modwsgi/
COMPONENT_BUGDB=	utility/apache

TPNO=			19269

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk
include ../modules.mk

APACHE_USR_PREFIX = /usr/apache2/

VARIANT_AP_22_PY26 = $(BUILD_DIR)/apache22-python26
VARIANT_AP_22_PY27 = $(BUILD_DIR)/apache22-python27
VARIANT_AP_22_PY34 = $(BUILD_DIR)/apache22-python34
VARIANT_AP_24_PY26 = $(BUILD_DIR)/apache24-pytohn26
VARIANT_AP_24_PY27 = $(BUILD_DIR)/apache24-python27
VARIANT_AP_24_PY34 = $(BUILD_DIR)/apache24-python34

VARIANTS_32 = $(VARIANT_AP_22_PY26) $(VARIANT_AP_22_PY27)
VARIANTS_64 = $(VARIANT_AP_22_PY26) $(VARIANT_AP_22_PY27) $(VARIANT_AP_22_PY34) \
              $(VARIANT_AP_24_PY26) $(VARIANT_AP_24_PY27) $(VARIANT_AP_24_PY34)

$(BUILD_DIR)/apache22-%/$(MACH32)/.configured: APXS=$(APACHE_USR_PREFIX)/2.2/bin/apxs
$(BUILD_DIR)/apache22-%/$(MACH64)/.configured: APXS=$(APACHE_USR_PREFIX)/2.2/bin/$(MACH64)/apxs
$(BUILD_DIR)/apache24-%/$(MACH64)/.configured: APXS=$(APACHE_USR_PREFIX)/2.4/bin/apxs

$(BUILD_DIR)/apache2%-python26/$(MACH32)/.configured: PYTHON=$(PYTHON.2.6.32)
$(BUILD_DIR)/apache2%-python26/$(MACH64)/.configured: PYTHON=$(PYTHON.2.6.64)
$(BUILD_DIR)/apache2%-python27/$(MACH32)/.configured: PYTHON=$(PYTHON.2.7.32)
$(BUILD_DIR)/apache2%-python27/$(MACH64)/.configured: PYTHON=$(PYTHON.2.7.64)
$(BUILD_DIR)/apache2%-python34/$(MACH32)/.configured: PYTHON=$(PYTHON.3.4.32)
$(BUILD_DIR)/apache2%-python34/$(MACH64)/.configured: PYTHON=$(PYTHON.3.4.64)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --with-python=$(PYTHON)
CONFIGURE_OPTIONS += --with-apxs=$(APXS)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)
