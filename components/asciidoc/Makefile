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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		asciidoc
COMPONENT_VERSION=	8.6.8
COMPONENT_PROJECT_URL=	http://www.methods.co.nz/asciidoc/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:ffb67f59dccaf6f15db72fcd04fdf21a2f9b703d31f94fcd0c49a424a9fcfbc4
COMPONENT_ARCHIVE_URL=	 http://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/asciidoc

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# AsciiDoc configuration and data files belong in /usr/share, not /etc based
# on discussion from ARC pre-review.
#
CONFIGURE_OPTIONS +=    --sysconfdir=/usr/share

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python$(PYTHON_VERSION)'
#
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's?env python?python$(PYTHON_VERSION)?' \
                $(PROTOUSRBINDIR64)/asciidoc.py;
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's?env python?python$(PYTHON_VERSION)?' \
                $(PROTOUSRBINDIR64)/a2x.py;

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

# Tests require image/graphviz to be installed.  Some tests also want to run
# programs named latex, lilypad, abc2ly and source-highlight which are not
# available on Solaris, so these tests fail.
#
COMPONENT_PRE_TEST_ACTION = \
    (cd $(@D); \
     ln -s asciidoc.py asciidoc; \
     export PATH=$(@D):$$PATH; \
     cd tests; \
     python$(PYTHON_VERSION) ./asciidocapi.py; \
     if [ $$? -eq 0 ] ; \
       then print "asciidocapi test passed"; else print "asciidocapi test failed"; \
     fi; \
     python$(PYTHON_VERSION) ./testasciidoc.py update; \
     python$(PYTHON_VERSION) ./testasciidoc.py run; )

test:           $(TEST_64)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
