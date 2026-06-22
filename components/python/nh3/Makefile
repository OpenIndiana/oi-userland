#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project nh3
#

BUILD_STYLE = pyproject
CARGO_VENDOR = yes
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nh3
HUMAN_VERSION =			0.3.6
COMPONENT_SUMMARY =		Python binding to Ammonia HTML sanitizer Rust crate
COMPONENT_ARCHIVE_HASH =	\
	sha256:f3736c9dd3d1856f80cd031715b84ca75cda2bbb1ac802c3da26bfce590838d7
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES.python += library/python/maturin
REQUIRED_PACKAGES.python += runtime/python
