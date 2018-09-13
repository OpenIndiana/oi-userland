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
# Copyright 2018 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pexpect
COMPONENT_VERSION= 	4.6.0
COMPONENT_PROJECT_URL=	https://github.com/pexpect/pexpect
COMPONENT_FMRI=	library/python/pexpect
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:2a8e88259839571d1251d278476f3eec5db26deb73a70be5ed5dc5435e418aba
COMPONENT_ARCHIVE_URL= \
  $(call pypi_url)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	ISC
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build: $(BUILD_NO_ARCH)

install: $(INSTALL_NO_ARCH)

test:	$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
