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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
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
COMPONENT_ANITYA_ID=	11989

TPNO=			14503

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR =     $(COMPONENT_SRC)/src/pycountry/tests
COMPONENT_TEST_ARGS =    test_general.py
COMPONENT_TEST_CMD =     /usr/bin/nosetests

# Regenerate the message object (mo) files for the patched 
# iso3166 (country) and iso3166-2 (country subdivisions) translations.
COMPONENT_PRE_BUILD_ACTION = \
	cd $(SOURCE_DIR)/src/$(COMPONENT_NAME)/locales; \
	for pofile in */LC_MESSAGES/iso3166.po \
	              */LC_MESSAGES/iso3166_2.po ; \
	do \
		mofile=`echo $$pofile | $(GSED) -e 's/\.po$$/\.mo/'` ; \
		/bin/rm -f $$mofile; \
		gmsgfmt $$pofile -o $$mofile; \
	done

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

