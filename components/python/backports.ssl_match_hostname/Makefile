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
# Copyright 2016, Aurelien Larcher.
#
include ../../../make-rules/shared-macros.mk


COMPONENT_NAME= backports.ssl_match_hostname
COMPONENT_VERSION= 3.5.0.1
COMPONENT_REVISION= 1
COMPONENT_SRC_VERSION= 29bca6a22953
COMPONENT_FMRI= library/python/backports.ssl_match_hostname
COMPONENT_PROJECT_URL= http://bitbucket.org/brandon/backports.ssl_match_hostname
COMPONENT_SRC= brandon-$(COMPONENT_NAME)-$(COMPONENT_SRC_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bc3aee759eb480bda8c5c0e0521f62fd75afeca73395e3195e55f60644304a99
COMPONENT_ARCHIVE_URL= \
    https://bitbucket.org/brandon/backports.ssl_match_hostname/get/$(COMPONENT_SRC_VERSION).tar.gz

PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += runtime/python-27
