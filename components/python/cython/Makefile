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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Cython
COMPONENT_VERSION=	0.28.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=		\
    sha256:b64575241f64f6ec005a4d4137339fb0ba5e156e826db2fdb5f458060d9979e0
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=  http://cython.org/
COMPONENT_ANITYA_ID=	12679
COMPONENT_FMRI=         library/python/cython
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=      "Apache-2.0"
COMPONENT_LICENSE_FILE= LICENSE.txt

# Avoid warnings about use of the deprecated NumPy API. Please see
# http://docs.cython.org/en/latest/src/reference/compilation.html#configuring-the-c-build
# for details.
CPPFLAGS +=		-DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION
CFLAGS +=		$(CPPFLAGS)

PYTHON_VERSIONS = 2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/setup.py.mk

# Since each version of the package delivers the same
# files to usr/bin, we need mediation. This is enabled
# by making a copy of the script with an appropriate
# suffix.
COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTO_DIR)/usr/bin ; \
         if [ \( "$(PYTHON_VERSION)" = "2.7" -o "$(PYTHON_VERSION)" = "3.4" \) -a "$(BITS)" == "64" ]; then \
            $(MKDIR) $(PROTO_DIR)/usr/bin/$(MACH64); \
            for c in cython cythonize cygdb; do \
                $(MV) $$c $(MACH64)/$$c-$(PYTHON_VERSION) ; \
            done; \
         else \
	    for c in cython cythonize cygdb; do \
	         $(MV) $$c $$c-$(PYTHON_VERSION) ; \
	    done; fi )


COMPONENT_TEST_ENV += PREREQ_MAKEFILE=
COMPONENT_TEST_DIR =    $(SOURCE_DIR)
COMPONENT_TEST_CMD =    ./runtests.py
COMPONENT_TEST_ARGS=

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += developer/debug/gdb
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
