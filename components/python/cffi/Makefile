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
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cffi
COMPONENT_VERSION=	0.8.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8192393640f7bc304ce82669b35eb90592566a30abbb4924456f52079afc18e2
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://cffi.readthedocs.org/
COMPONENT_BUGDB=	python-mod/cffi

TPNO=			16913

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR =	$(@D)/tests
COMPONENT_TEST_ENV =	$(PYTHON_ENV)
COMPONENT_TEST_ENV +=	PYTHONPATH=$(PROTO_DIR)/$(PYTHON_LIB)
COMPONENT_TEST_ENV +=	TESTOWNLIB_CC="$(CC) %s $(CC_BITS) -G -KPIC -o %s"
COMPONENT_TEST_CMD =	$(PYTHON.$(BITS)) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =	--resultlog $(@D)/testresults
COMPONENT_TEST_ARGS +=	-p no:codechecker
COMPONENT_TEST_ARGS +=	$(TEST_SKIPS)
COMPONENT_TEST_ARGS +=	c testing
# The following tests cause core dumps on SPARC (bus error, illegal hardware
# instruction).  We don't skip test_install_and_reload_module{,_package}, which
# fail on both 64-bit platforms, since those don't cause the interpreter to
# crash.
$(BUILD_DIR)/sparcv7-%/.tested: TEST_SKIPS = -k "not test_callback_return_type and not test_struct_packed and not test_opaque_integer_as_function_result"
$(BUILD_DIR)/sparcv9-%/.tested: TEST_SKIPS = -k "not test_callback and not test_a_lot_of_callbacks and not test_struct_packed and not test_opaque_integer_as_function_result and not test_wchar"

# Copy the tests and a few of the source files they read into a scratch
# directory so running the tests don't leave turds in the source directory.
COMPONENT_PRE_TEST_ACTION = \
	$(MKDIR) $(@D)/tests/doc/source; \
	$(CP) -r $(SOURCE_DIR)/c $(SOURCE_DIR)/testing $(@D)/tests; \
	$(CP) $(SOURCE_DIR)/setup.py $(@D)/tests; \
	$(CP) \
	    $(SOURCE_DIR)/doc/source/conf.py \
	    $(SOURCE_DIR)/doc/source/index.rst \
	    $(@D)/tests/doc/source

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
