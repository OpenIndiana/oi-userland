#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Till Wegmueller
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=futures
COMPONENT_VERSION=3.2.0
COMPONENT_SUMMARY='Backport of Python futures for 2.7'
COMPONENT_PROJECT_URL=https://github.com/agronholm/pythonfutures
COMPONENT_FMRI=library/python/futures
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          python$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=https://github.com/agronholm/pythonfutures/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=sha256:fc959e162a3ea775c827f8a5e1810ecd175dbb986c2b16864b47fe491ad6950b
COMPONENT_LICENSE='PYTHON SOFTWARE FOUNDATION LICENSE VERSION 2'
COMPONENT_LICENSE_FILE=LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR = $(COMPONENT_SRC)
COMPONENT_TEST_ARGS = ./test_futures.py

COMPONENT_TEST_TRANSFORMS += \
        '-e "s/[0-9\.]*s$$/Ns/" '

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(TEST_NO_ARCH)
