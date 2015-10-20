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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Imaging
COMPONENT_VERSION=	1.1.7
COMPONENT_PROJECT_URL=	http://www.pythonware.com/products/pil/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:895bc7c2498c8e1f9b99938f1a40dc86b3f149741f105cf7c7bd2e0725405211
COMPONENT_ARCHIVE_URL=	http://effbot.org/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/pil

TPNO=			7909

# Syntax issues: not Python 3 ready.
PYTHON_VERSIONS = $(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# This binary image file accompanies the test which is created along with a fix
# in patches/04-CVE-2014-9601.patch
COMPONENT_PRE_TEST_ACTION= \
	if [ ! -e $(SOURCE_DIR)/Images/png_decompression_dos.png ]; then \
		$(CP) files/png_decompression_dos.png \
		$(SOURCE_DIR)/Images/png_decompression_dos.png ; \
	fi

COMPONENT_TEST_DIR= $(COMPONENT_SRC)
COMPONENT_TEST_ARGS= ./selftest.py
COMPONENT_TEST_ENV= PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES.32)

# Master test results are the same for both 32-bit and 64-bit, 
# for all versions of Python, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^PIL [0-9]\{1,\}\(\.[0-9]\{1,\}\)\{1,\}|PIL|" ' \
	'-e "s|\(^Python modules loaded from \).*|\1|" ' \
	'-e "s|\(^Binary modules loaded from \).*|\1|" '

# This binary image file accompanies the test which is created along with a fix
# in patches/04-CVE-2014-9601.patch
COMPONENT_PRE_SYSTEM_TEST_ACTION= \
	if [ ! -e $(SOURCE_DIR)/Images/png_decompression_dos.png ]; then \
		$(CP) files/png_decompression_dos.png \
		$(SOURCE_DIR)/Images/png_decompression_dos.png ; \
	fi
COMPONENT_SYSTEM_TEST_DIR= $(COMPONENT_SRC)
COMPONENT_SYSTEM_TEST_ARGS= ./selftest.py
COMPONENT_SYSTEM_TEST_ENV= PYTHONPATH=$(PYTHON_VENDOR_PACKAGES.32)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TEST_32_and_64)


REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
