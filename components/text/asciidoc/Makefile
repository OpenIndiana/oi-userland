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

BUILD_BITS=			64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	asciidoc
COMPONENT_VERSION= 	9.1.0
COMPONENT_SUMMARY= 	Text based document generation tool
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:fd499fcf51317b1aaf27336fb5e919c44c1f867f1ae6681ee197365d3065238b
COMPONENT_ARCHIVE_URL=	https://github.com/asciidoc/asciidoc-py3/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://asciidoc.org/
COMPONENT_LICENSE=	GPLv2

PYTHON_VERSION=		3.7

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += PYTHON=$(PYTHON)

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python$(PYTHON_VERSION)'
#
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's?env python3?python$(PYTHON_VERSION)?' \
                $(PROTOUSRBINDIR)/asciidoc.py;
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's?env python3?python$(PYTHON_VERSION)?' \
                $(PROTOUSRBINDIR)/a2x.py;

# AsciiDoc configuration and data files belong in /usr/share, not /etc based
# (Following what Oracle does for Solaris
CONFIGURE_OPTIONS +=    --sysconfdir=$(USRSHAREDIR)

COMPONENT_TEST_DIR =    $(@D)/tests
COMPONENT_TEST_ENV_CMD =
COMPONENT_TEST_ENV =    export PATH=$(@D):$$PATH;
COMPONENT_TEST_CMD =    \
    $(PYTHON) ../asciidocapi.py; \
    if [ $$? -eq 0 ] ; \
        then print "asciidocapi test passed"; \
        else print "asciidocapi test failed"; \
    fi; \
    $(PYTHON) ./testasciidoc.py update --force; \
    $(PYTHON) ./testasciidoc.py run
COMPONENT_TEST_TARGETS =

COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/passed/p" ' \
    '-e "/^[1-9]: /p" ' \
    '-e "/^[1-9][0-9]: /p" ' \
    '-e "/^SOURCE/p" ' \
    '-e "/^PASSED/p" ' \
    '-e "/^FAILED/p" ' \
    '-e "/^TOTAL/p" '

# Manually added dependencies:
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/python/pygments
REQUIRED_PACKAGES += web/browser/w3m

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
