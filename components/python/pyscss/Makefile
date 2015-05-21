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

COMPONENT_NAME=		pyScss
COMPONENT_VERSION=	1.2.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6f486363f5fac20d218dc5d11b8af4e5b52242a59e5067f42ca227152a7df3cc
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/Kronuz/pyScss
COMPONENT_BUGDB=	python-mod/pyscss

TPNO=			20384

# Python 3.4 has build errors.  Need to investigate...
PYTHON_VERSIONS =	2.7 2.6

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) -f pyscss pyscss-$(PYTHON_VERSION))

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# The tarball for this version does not ship unittests.
test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/python/pytest-26
REQUIRED_PACKAGES += library/python/pytest-27
REQUIRED_PACKAGES += library/python/setuptools-26
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/six-26
REQUIRED_PACKAGES += library/python/six-27
