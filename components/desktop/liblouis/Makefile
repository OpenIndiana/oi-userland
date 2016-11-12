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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		liblouis
COMPONENT_VERSION=	2.1.1
COMPONENT_PROJECT_URL=	http://liblouis.org/
COMPONENT_ARCHIVE_HASH= \
	sha256:e7b4f1aee9b1cd595b49a2fab1c545d1c7aad70dc427aa5c6d413a3dba17722c
# liblouis upstream didn't migrate the 2.1.1 download from google code to
# github, so we use a mirror site for now, until we upgrade to a current version
# COMPONENT_ARCHIVE_URL=	https://github.com/liblouis/liblouis/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL=	https://distfiles.macports.org/liblouis/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/accessibility

TPNO=			4317

# Orca uses python 3.5, so we need to match
PYTHON_VERSION=		3.5

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=    --enable-shared
CONFIGURE_OPTIONS +=    --disable-static

# While the main library is built with configure, the python module is
# built & installed with separate invocations of setup.py
PYTHON_ENV +=	CC="$(CC)"
PYTHON_ENV +=	CFLAGS="$(CFLAGS)"
PYTHON_ENV +=	PYTHONPATH='$(@D)/python'

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D)) ;
COMPONENT_POST_BUILD_ACTION += \
	(cd $(@D)/python ; \
	    $(ENV) $(COMPONENT_BUILD_ENV) $(PYTHON_ENV) \
		LD_LIBRARY_PATH_$(BITS)=$(@D)/liblouis/.libs/ \
	        $(PYTHON) ./setup.py build );
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(@D)/python ; \
	    $(ENV) $(COMPONENT_INSTALL_ENV) $(PYTHON_ENV) \
		LD_LIBRARY_PATH_$(BITS)=$(PROTO_DIR)$(USRLIB.$(BITS)) \
	        $(PYTHON) ./setup.py install --root $(PROTO_DIR) \
		--install-lib $(PYTHON_LIB) );

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS

# Standard automake test framework results transform
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL/p" ' \
        '-e "/SKIP/p" ' \
        '-e "/PASS/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/ERROR/p" '

# additional transforms for brltty
COMPONENT_TEST_TRANSFORMS += \
        '-e "/^==*$$/p" ' \
        '-e "/expected/p" '

REQUIRED_PACKAGES += developer/documentation-tool/help2man
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
