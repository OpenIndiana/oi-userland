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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2023, Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

BUILD_STYLE=setup.py
TEST_STYLE=none
OPENSSL_DEFAULT= 1.1

COMPONENT_NAME=		pycurl
COMPONENT_VERSION=	7.45.2
COMPONENT_PROJECT_URL=	http://pycurl.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:5730590be0271364a5bddd9e245c9cc0fb710c4cbacbdd95264a3122d23224ca
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_BUGDB=	python-mod/pycurl

include $(WS_MAKE_RULES)/common.mk

# to make sure that the docs get installed in the right place.
PYTHON_DATA = /usr

# force pycurl to use openssl-1.1, with above OPENSSL_DEFAULT macro.
PYTHON_ENV += CPPFLAGS="$(CPPFLAGS) -I$(OPENSSL_PREFIX)/include"
PYTHON_ENV += LDFLAGS="$(LDFLAGS) -L$(OPENSSL_PREFIX)/lib/$(MACH64) -R$(OPENSSL_PREFIX)/lib/$(MACH64)"

ASLR_MODE=	$(ASLR_NOT_APPLICABLE)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
