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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pep8
COMPONENT_VERSION=	1.4.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://pypi.python.org/pypi/pep8
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:603a46e5c358ce20ac4807a0eeafac7505d1125a4c1bd8378757ada06f61bed8
COMPONENT_ARCHIVE_URL=	http://pypi.python.org/packages/source/p/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/pep8

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_PRE_BUILD_ACTION = \
	/usr/bin/find $(SOURCE_DIR) -name *.py \
		-exec $(GSED) -i -e 's/env python/python$(PYTHON_VERSION)/' "{}" \; ;

# Put the correct pep8 version number on the .TH line in the man page in
# the proto area.
COMPONENT_POST_INSTALL_ACTION += \
	($(MKDIR) $(PROTO_DIR)/usr/share/man/man1; \
	$(GSED) -e 's/XXX/$(COMPONENT_VERSION)/' \
	    $(COMPONENT_DIR)/files/pep8.1 > \
	    $(PROTO_DIR)/usr/share/man/man1/pep8.1);

COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) -f pep8 pep8-$(PYTHON_VERSION))

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
