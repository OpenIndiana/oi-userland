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

COMPONENT_NAME=		cssutils
COMPONENT_VERSION=	0.9.6
COMPONENT_PROJECT_URL=	http://code.google.com/p/cssutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
    sha256:18f3cffb2ff413e0796d0c9192db3a56f18fe57524cc54edc57d20239614eb87
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/c/cssutils/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/cssutils

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_TEST_DIR= $(COMPONENT_SRC)
COMPONENT_TEST_ARGS= ./setup.py test

# Remove the trailing Control-M's from the Python source files.
COMPONENT_PRE_BUILD_ACTION = \
	/usr/bin/find $(SOURCE_DIR)/src \
		-name *.py -exec $(GSED) -i -e 's///g' "{}" \; ;

# After we have done each Python build, copy it to its own version specific
# source hierarchy and then adjust the shebang lines as needed, before we 
# build for Python 2.6. Note that this assumes we are only doing Python 2.7
# and Python 2.6, and we are doing them in that order.
COMPONENT_POST_BUILD_ACTION = \
	(cd $(SOURCE_DIR); cp -rp src src-$(PYTHON_VERSION) ; \
	cd $(SOURCE_DIR)/src ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' cssutils/__init__.py ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' cssutils/codec.py ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' cssutils/errorhandler.py ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' cssutils/parse.py ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' cssutils/scripts/csscapture.py ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' cssutils/scripts/csscombine.py ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' cssutils/scripts/cssparse.py ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' cssutils/serialize.py ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' cssutils/tokenize2.py ; \
	$(GSED) -i -e 's/2[.]7/2.6/g' encutils/__init__.py )

# Copy over the source hierarchy for the appropriate Python build before
# installing it.
COMPONENT_PRE_INSTALL_ACTION = \
	(cd $(SOURCE_DIR); $(RM) -r src ; $(CP) -rp src-$(PYTHON_VERSION) src )

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(TEST_NO_ARCH)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
