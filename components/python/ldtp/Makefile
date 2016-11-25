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
# Copyright 2013 Gary Mills
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=         ldtp
COMPONENT_VERSION=      2.1.1
COMPONENT_REVISION=	1
COMPONENT_MAJOR_VERSION=2.x
COMPONENT_MINOR_VERSION=2.1.x
COMPONENT_PROJECT_URL=	http://ldtp.freedesktop.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:53215930b38edeb980f43130fc29783db4875ce2317c946391a7baa63d98aa0e
COMPONENT_ARCHIVE_URL=  http://ftp.igh.cnrs.fr/pub/os/openindiana/dlc/oi-build/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/ldtp

PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) -f ldtp ldtp$(PYTHON_VERSION))

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += runtime/python-27
