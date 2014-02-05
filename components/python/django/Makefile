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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Django
COMPONENT_VERSION=	1.4.10
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3d1f083c039fdab1400c32b5406a60891c9dd16f880999c4a53d054742ac29de
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://www.djangoproject.com/
COMPONENT_BUGDB=	python-mod/django

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_POST_BUILD_ACTION = \
        /usr/bin/find $(BUILD_DIR)/$(MACH)-$(PYTHON_VERSION)/lib/django -name *.py \
                -exec $(GSED) -i -e 's/env python/python$(PYTHON_VERSION)/' "{}" \; ;

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; $(MV) -f django-admin.py django-admin-$(PYTHON_VERSION))

# add 1 extra transform to get rid of the facet created on
# locale/__init__.py
PUBLISH_TRANSFORMS += $(COMPONENT_DIR)/django-locale-transform

# reset the test environment to only contain PATH and PYTHONPATH
COMPONENT_TEST_DIR=     $(SOURCE_DIR)/tests
COMPONENT_TEST_ARGS +=  --settings test_sqlite
COMPONENT_TEST_ENV=     PYTHONPATH=$(SOURCE_DIR)
COMPONENT_TEST_ENV +=   PATH=$(PATH)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

#
# tests require:
#
# docutils Markdown PIL py-bcrypt python-memcached pytz PyYAML
# selenium and Textile, some of which haven't been integrated yet.
# The tests will run, but there are errors.
#
test:		$(TEST_NO_ARCH)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
