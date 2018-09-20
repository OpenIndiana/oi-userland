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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	dulwich
COMPONENT_VERSION= 	0.14.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	Python implementation of the Git file formats and protocols
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:7c1f49e6e72fa8635328d32bfeb7103e86e175d87fa80a9cefdd63a360f7ba93
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/d8/be/8cb595710e7bf2a32b0ac64f1455e1f0554ec8aa9ed62c49b084afe22ab6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/dulwich

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMMANDS = dul-receive-pack  dul-upload-pack  dulwich

COMPONENT_POST_INSTALL_ACTION= \
	( $(MKDIR) $(PROTO_DIR)/$(dir $(PYTHON.$(PYTHON_VERSION).$(BITS))); \
        for cmd in $(COMMANDS) ; \
        do $(MV) -f $(PROTO_DIR)/usr/bin/$${cmd} \
                $(PROTO_DIR)/$(dir $(PYTHON.$(PYTHON_VERSION).$(BITS)))/$${cmd}$(PYTHON_VERSION); \
        done;)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test:	$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
