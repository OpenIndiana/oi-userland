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
# Copyright (c) 2022 Niklas Poslovski
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_wsgi
COMPONENT_VERSION=	4.9.4
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		mod_wsgi plugin for Apache Web Server v2.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8e762662ea5b01afc386bbcfbaa079748eb6203ab1d6d3a3dac9237f5666cfc9
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/m/mod_wsgi/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://pypi.python.org/pypi/mod_wsgi/
COMPONENT_FMRI =		web/server/apache-24/module/apache-wsgi
COMPONENT_CLASSIFICATION =	Web Services/Application and Web Servers
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

SINGLE_PYTHON_VERSION = no

# The following four paragraphs are copied from setup.py.mk
# but since mod_wsgi doesn't use setup.py, we can't just include
# setup.py.mk
define python-rule
$(BUILD_DIR)/%-$(1)/.built:		PYTHON_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.installed:		PYTHON_VERSION=$(1)
endef

$(foreach pyver, $(PYTHON_VERSIONS), $(eval $(call python-rule,$(pyver))))

$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64

BUILD_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
INSTALL_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

APACHE_USR_PREFIX = /usr/apache2/2.4

# mod_wsgi does not support VPATH builds
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --with-apxs=$(APACHE_USR_PREFIX)/bin/apxs
CONFIGURE_OPTIONS += --with-python=$(PYTHON)

# Without this the build is unable to find right C compiler
COMPONENT_BUILD_ENV += PATH="$(GCC_BINDIR):$(PATH)"

# The following is copied from setup.py.mk and adjusted
COMPONENT_POST_INSTALL_ACTION += \
	for f in $(PROTO_DIR)$(APACHE_USR_PREFIX)/libexec/*.so ; do \
		[[ -f $$f ]] || continue ; \
		for v in $(PYTHON_VERSIONS) ; do \
			[[ "$$f" == "$${f%%$$v.so}" ]] || continue 2 ; \
		done ; \
		$(MV) $$f $${f%%.so}-$(PYTHON_VERSION).so ; \
	done ;

# We need to add -$(PYV) to package fmri
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's/^\(set name=pkg.fmri [^@]*\)\(.*\)$$/\1-$$(PYV)\2/'

# Manually added dependencies
REQUIRED_PACKAGES += web/server/apache-24

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
