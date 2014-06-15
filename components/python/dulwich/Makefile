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
COMPONENT_VERSION= 	0.9.5
COMPONENT_SUMMARY= 	Python implementation of the Git file formats and protocols
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:751fe9e1d32b61e21f086b4fa07ca96b69165a7ad24c5cebaef4f8803f512c0b
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/source/d/dulwich/dulwich-0.9.5.tar.gz#md5=7ace33f90cd61c7fcd32816eb73d1f5a
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/dulwich

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMMANDS = dul-daemon  dul-receive-pack  dul-upload-pack  dul-web  dulwich

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

COMPONENT_POST_INSTALL_ACTION= \
        (for cmd in $(COMMANDS) ; \
        do $(MV) -f $(PROTO_DIR)/usr/bin/$${cmd} \
                $(PROTO_DIR)/usr/bin/$${cmd}$(PYTHON_VERSION).$(BITS); \
        done;)
