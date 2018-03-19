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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	python-ldap
COMPONENT_VERSION= 	3.0.0
COMPONENT_FMRI= 	library/python/python-ldap
COMPONENT_SUMMARY= 	Python modules for implementing LDAP clients
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:86746b912a2cd37a54b06c694f021b0c8556d4caeab75ef50435ada152e2fbe1
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/c1/52/dfb508364bce92bb2a6ccbe718b69c8857b5d6fcd6af259ab0c36ee68730/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/python-ldap
COMPONENT_LICENSE_FILE=	LICENCE
COMPONENT_LICENSE=	PYTHON_STYLE

PYTHON_VERSIONS=	2.7

CFLAGS += -I/usr/include/openldap

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
