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
COMPONENT_VERSION= 	2.4.25
COMPONENT_FMRI= 	library/python/python-ldap
COMPONENT_SUMMARY= 	Python modules for implementing LDAP clients
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:62d00dbc86f3f9b21beacd9b826e8f9895f900637a60a6d4e7ab59a1cdc64e56
COMPONENT_ARCHIVE_URL= \
  $(call pypi_url)
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/python-ldap
COMPONENT_LICENSE_FILE=	LICENCE
COMPONENT_LICENSE=	PYTHON_STYLE

CFLAGS += -I/usr/include/openldap

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += runtime/python-26
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
