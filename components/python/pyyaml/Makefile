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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	PyYAML
COMPONENT_VERSION= 	3.11
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	A YAML parser and emitter for the Python language
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:c36c938a872e5ff494938b33b14aaa156cb439ec67548fcab3535bb78b0846e8
COMPONENT_ARCHIVE_URL= \
  http://pyyaml.org/download/pyyaml/PyYAML-3.11.tar.gz
COMPONENT_PROJECT_URL = http://pyyaml.org/

PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_BUILD_ENV += LDFLAGS=$(LDFLAGS)

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
