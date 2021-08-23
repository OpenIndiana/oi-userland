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
# Copyright 2021 Gary Mills
#

BUILD_BITS = 64
BUILD_STYLE= setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lazy_object_proxy
ARCH_NAME=		python-lazy-object-proxy
COMPONENT_VERSION=	1.6.0
COMPONENT_FMRI=         library/python/lazy_object_proxy
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_PROJECT_URL=	https://github.com/ionelmc/$(ARCH_NAME)
COMPONENT_SRC=		$(ARCH_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:e97c0edc4b59e392befad3986377769bc33285dab027b78adecd74d9fbd4acaf
COMPONENT_ARCHIVE_URL= \
  https://github.com/ionelmc/$(ARCH_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=      BSD

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =    $(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =    $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

# Typical failures for test target:
#=========================== short test summary info ============================
#...
#ERROR test_lazy_object_proxy.py::test_perf[slots]
#ERROR test_lazy_object_proxy.py::test_perf[cext]
#ERROR test_lazy_object_proxy.py::test_perf[simple]
#ERROR test_lazy_object_proxy.py::test_perf[django]
#ERROR test_lazy_object_proxy.py::test_perf[objproxies]
#ERROR test_lazy_object_proxy.py::test_proto[SimpleProxy]
#ERROR test_lazy_object_proxy.py::test_proto[LocalsSimpleProxy]
#ERROR test_lazy_object_proxy.py::test_proto[CachedPropertyProxy]
#ERROR test_lazy_object_proxy.py::test_proto[LocalsCachedPropertyProxy]
#= 1504 passed, 284 skipped, 36 xfailed, 42 xpassed, 12 warnings, 9 errors in 5.95s =

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
