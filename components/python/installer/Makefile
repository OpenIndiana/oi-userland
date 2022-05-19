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
# Copyright 20200 Daniel Chan
#

BUILD_BITS=			64
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		installer
COMPONENT_VERSION=	0.5.1
COMPONENT_SUMMARY=	A library for installing Python wheels.
COMPONENT_PROJECT_URL=	https://pypi.org/project/installer/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f970995ec2bb815e2fdaf7977b26b2091e1e386f0f42eafd5ac811953dc5d445
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/installer
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/packaging-37
REQUIRED_PACKAGES += library/python/packaging-39
REQUIRED_PACKAGES += library/python/ply-37
REQUIRED_PACKAGES += library/python/ply-39
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += library/python/toml-37
REQUIRED_PACKAGES += library/python/toml-39
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
