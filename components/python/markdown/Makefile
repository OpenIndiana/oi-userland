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


COMPONENT_NAME= markdown
COMPONENT_SRC_NAME= Python-Markdown
COMPONENT_VERSION= 2.6.9
COMPONENT_FMRI= library/python/markdown
COMPONENT_PROJECT_URL=  https://pythonhosted.org/Markdown/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4aca6f069776e5e45bf4fdedd1512137ee345e860e842e583c464ab670197e80
# Pypi download link is broken
COMPONENT_ARCHIVE_URL= \
    https://github.com/Python-Markdown/markdown/archive/$(COMPONENT_VERSION).tar.gz

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += runtime/python-27
