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

COMPONENT_NAME=		cryptography
COMPONENT_VERSION=	0.8.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1c9a022ab3decaf152093e2ef2d5ee4258c72c7d429446c86bd68ff8c0929db6
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://cryptography.io/
COMPONENT_BUGDB=	python-mod/cryptography

TPNO=			22524

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

#
# Until enum is available in the build environment, it needs to be built
# in order for setuptools to work here.
#
ENUM=	$(WS_COMPONENTS)/python/enum/build/prototype/$(MACH)/$(PYTHON_LIB)

$(ENUM):
	(cd ../enum ; $(MAKE) install)

COMPONENT_BUILD_ENV +=		PYTHONPATH=$(ENUM)

COMPONENT_INSTALL_ENV +=	PYTHONPATH=$(ENUM)

$(BUILD_32_and_64):		$(ENUM)

clean::
	(cd ../enum ; $(MAKE) clean)

clobber::
	(cd ../enum ; $(MAKE) clobber)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

#
# tests require cryptography_vectors, iso8601, pretend, pytest, and six,
# some of which have not yet integrated.
#
test:		$(NO_TESTS)


REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
