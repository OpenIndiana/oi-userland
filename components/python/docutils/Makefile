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

COMPONENT_NAME= 	docutils
COMPONENT_VERSION= 	0.12
COMPONENT_REVISION=	1
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:c7db717810ab6965f66c8cf0398a98c9d8df982da39b4cd7f162911eb89596fa
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/source/d/docutils/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/docutils

PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

build: $(BUILD_32)

install: $(INSTALL_32)

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; for i in rst2html.py rst2latex.py rst2man.py rst2odt_prepstyles.py \
						rst2odt.py rst2pseudoxml.py rst2s5.py rst2xetex.py rst2xml.py\
						rstpep2html.py; \
					do $(MV) $$i $$i-$(PYTHON_VERSION); done)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/lxml-27
REQUIRED_PACKAGES += runtime/python-27
