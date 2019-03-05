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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		psutil
COMPONENT_VERSION=	5.6.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:dca71c08335fbfc6929438fe3a502f169ba96dd20e50b3544053d6be5cb19d82
COMPONENT_ARCHIVE_URL=	https://files.pythonhosted.org/packages/79/e6/a4e3c92fe19d386dcc6149dbf0b76f1c93c5491ae9d9ecf866f6769b45a4/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://pypi.python.org/pypi/psutil/
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_FMRI=	library/python/psutil
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
