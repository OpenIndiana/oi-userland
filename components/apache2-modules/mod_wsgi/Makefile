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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_wsgi
COMPONENT_VERSION=	4.5.1
COMPONENT_ARCHIVE_HASH=	sha256:5ed31abf1978099ec0b4a00970c1be3c9cd3bef47830773cba441ca9770d4a2e
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/m/mod_wsgi/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://code.google.com/p/modwsgi/
COMPONENT_ANITYA_ID=	2001

TPNO=			27758

# Don't use default CPPFLAGS; it causes Apache's custom CPP to fail.
CONFIGURE_CPPFLAGS=
VARIANTS_64 += $(BUILD_DIR)/apache24-python27
VARIANTS_64 += $(BUILD_DIR)/apache24-python34
VARIANTS_64 += $(BUILD_DIR)/apache24-python35
include ../modules.mk

# Python is now built in C99 mode and we need it too (24743682).
studio_C99MODE= $(studio_C99_ENABLE)

$(BUILD_DIR)/apache24-%/$(MACH64)/.configured: APXS=$(APACHE_24_USR_PREFIX)/bin/apxs BITS=64
$(BUILD_DIR)/apache24-%/$(MACH64)/.built: BITS=64
$(BUILD_DIR)/apache24-%/$(MACH64)/.tested: BITS=64

$(BUILD_DIR)/apache2%-python27/$(MACH64)/.configured: PYTHON=$(PYTHON.2.7.64)
$(BUILD_DIR)/apache2%-python34/$(MACH64)/.configured: PYTHON=$(PYTHON.3.4.64)
$(BUILD_DIR)/apache2%-python35/$(MACH64)/.configured: PYTHON=$(PYTHON.3.5.64)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --with-python=$(PYTHON)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library/math
