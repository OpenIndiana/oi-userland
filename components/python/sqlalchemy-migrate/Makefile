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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sqlalchemy-migrate
COMPONENT_VERSION=	0.9.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:16e327c9642ca4c99a70dcac3b39aeb821edaf5214834b47fb0a89bac44af23b
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://code.google.com/p/sqlalchemy-migrate/
COMPONENT_BUGDB=	python-mod/sqlalchemy-mig

TPNO=			21740

# Syntax issues: not Python 3 ready.
PYTHON_VERSIONS=	2.7 2.6

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTO_DIR)/usr/bin ; \
	 $(MV) -f migrate migrate-$(PYTHON_VERSION) ; \
         $(MV) -f migrate-repository migrate-repository-$(PYTHON_VERSION))

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

#
# Tests require:
# SQLAlchemy, Tempita and unittest2
# which haven't been integrated yet.
#
test:		$(NO_TESTS)


REQUIRED_PACKAGES += library/python/decorator-26
REQUIRED_PACKAGES += library/python/decorator-27
REQUIRED_PACKAGES += library/python/setuptools-26
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/six-26
REQUIRED_PACKAGES += library/python/six-27
REQUIRED_PACKAGES += library/python/sqlalchemy-26
REQUIRED_PACKAGES += library/python/sqlalchemy-27
