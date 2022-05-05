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
# Copyright 2022 Gary Mills
# Copyright 2015 Alexander Pyhalov
#

BUILD_STYLE=	setup.py
BUILD_BITS=	NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	docutils
COMPONENT_VERSION= 	0.18.1
# COMPONENT_REVISION=	0
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:679987caf361a7539d76e584cbeddc311e3aee937877c87346f31debc63e9d06
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/source/d/docutils/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/docutils
COMPONENT_FMRI=		library/python/docutils
COMPONENT_SUMMARY=	Docutils is a modular system for processing documentation into useful formats, such as HTML, XML, and LaTeX
COMPONENT_CLASSIFICATION= org.opensolaris.category.2008:Development/Python
COMPONENT_LICENSE_FILE=	COPYING.txt
COMPONENT_LICENSE=	Public domain

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; \
    for i in rst2html.py rst2html4.py rst2html5.py rst2latex.py \
      rst2man.py rst2odt_prepstyles.py rst2odt.py rst2pseudoxml.py \
      rst2s5.py rst2xetex.py rst2xml.py rstpep2html.py; \
    do $(MV) $$i $$i-$(PYTHON_VERSION); done)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/lxml-37
REQUIRED_PACKAGES += library/python/lxml-39
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
