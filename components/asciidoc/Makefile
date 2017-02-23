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

#
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		asciidoc
COMPONENT_VERSION=	8.6.9
COMPONENT_PROJECT_URL=	http://www.methods.co.nz/asciidoc/
COMPONENT_ARCHIVE_HASH= \
    sha256:78db9d0567c8ab6570a6eff7ffdf84eadd91f2dfc0a92a2d0105d323cab4e1f0
COMPONENT_ARCHIVE_URL=	 http://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13262

TPNO=			30220

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL = 0

# AsciiDoc configuration and data files belong in /usr/share, not /etc based
# on discussion from ARC pre-review.
#
CONFIGURE_OPTIONS +=    --sysconfdir=$(USRSHAREDIR)

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python$(PYTHON_VERSION)'
#
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's?env python?python$(PYTHON_VERSION)?' \
                $(PROTOUSRBINDIR)/asciidoc.py;
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's?env python?python$(PYTHON_VERSION)?' \
                $(PROTOUSRBINDIR)/a2x.py;

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# common targets
# Tests require image/graphviz to be installed.  Some tests also want to run
# programs which are not automatically available on Solaris (latex, abc2ly
# and lilypad), so these tests will output messages of the form:
# latex2png.py: failed command: latex ...
# music2png.py: failed command: abc2ly ...
# music2png.py: failed command: lilypond ...
COMPONENT_PRE_TEST_ACTION = \
	(cd $(@D); ln -s asciidoc.py asciidoc)

COMPONENT_TEST_DIR =	$(@D)/tests
COMPONENT_TEST_ENV_CMD =
COMPONENT_TEST_ENV =	export PATH=$(@D):$$PATH;
COMPONENT_TEST_CMD =	\
	python$(PYTHON_VERSION) ./asciidocapi.py; \
	if [ $$? -eq 0 ] ; \
		then print "asciidocapi test passed"; \
		else print "asciidocapi test failed"; \
	fi; \
	python$(PYTHON_VERSION) ./testasciidoc.py update; \
	python$(PYTHON_VERSION) ./testasciidoc.py run
COMPONENT_TEST_TARGETS =
COMPONENT_POST_TEST_ACTION = \
	(cd $(@D); rm asciidoc)

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/passed/p" ' \
	'-e "/^[1-9]: /p" ' \
	'-e "/^[1-9][0-9]: /p" ' \
	'-e "/^SOURCE/p" ' \
	'-e "/^PASSED/p" ' \
	'-e "/^FAILED/p" ' \
	'-e "/^TOTAL/p" '

COMPONENT_SYSTEM_TEST_DIR =    $(@D)/tests
COMPONENT_SYSTEM_TEST_ENV_CMD =
COMPONENT_SYSTEM_TEST_CMD =    \
	python$(PYTHON_VERSION) ./asciidocapi.py; \
	if [ $$? -eq 0 ] ; \
		then print "asciidocapi test passed"; \
		else print "asciidocapi test failed"; \
	fi; \
	python$(PYTHON_VERSION) ./testasciidoc.py update; \
	python$(PYTHON_VERSION) ./testasciidoc.py run
COMPONENT_SYSTEM_TEST_TARGETS =

REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += web/browser/lynx
