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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pycountry
COMPONENT_VERSION=	0.17
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:1d1781ae6c42b15c26f45da7f53200defe00b6b2cad0512f05fdd43e539dd539
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/pycountry
COMPONENT_BUGDB=	python-mod/pycountry

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Regenerate the message object (mo) files for the patched 
# iso3166 (country) translations.
COMPONENT_PRE_BUILD_ACTION = \
	cd $(SOURCE_DIR)/src/$(COMPONENT_NAME)/locales; \
	for pofile in */LC_MESSAGES/iso3166.po; \
	do \
		dir=`dirname $$pofile`; \
		mofile=$$dir/iso3166.mo; \
		/bin/rm -f $$mofile; \
		gmsgfmt $$pofile -o $$mofile; \
	done

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

#  Tests require the tox package
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
