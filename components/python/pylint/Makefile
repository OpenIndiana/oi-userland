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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pylint
COMPONENT_VERSION=	0.25.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:757f2b97071a87fb7e4d017fc7c9eb74f26dcf412e683b614d3c5d54b217212d
COMPONENT_ARCHIVE_URL= \
  https://github.com/PyCQA/pylint/archive/$(COMPONENT_NAME)-version-$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=  http://www.logilab.org/project/pylint/

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/setup.py.mk

# There are several pylint documentation files that setup.py isn't installing
# but are present in the pylint package on other distributions. Copy them into
# the proto area "manually", so they can be included in the package.
PDOC =			$(PROTO_DIR)/usr/share/doc
PDOC_PYLINT =		$(PDOC)/pylint
PDOC_PYLINT_EXAMPLES =	$(PDOC_PYLINT)/examples

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/beginner_pylint_tutorial.txt $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/FAQ.txt $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/features.txt $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/manual.txt $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/quickstart.txt $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/README $(PDOC_PYLINT) ;

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/custom.py $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/custom_raw.py $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/elisp/pylint.el $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/pylintrc_camelcase $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/pylintrc $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) epylint epylint-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) pylint pylint-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) pylint-gui pylint-gui-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) pyreverse pyreverse-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) symilar symilar-$(PYTHON_VERSION)) ;


# common targets

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# The tests are run using python 2.7 only and require that
# the python-27 package is installed (does not have to be the default python).

# Use the python 2.7 libraries for testing.
test: PYTHON_VERSION=2.7

# logilab-common and logilab-astng are runtime dependencies of pylint,
# and we need to use their latest versions from this workspace.
# We can't just add their install targets as dependencies here,
# so just "gmake install" in the logilab-common and logilab-astng
# component directories before running the pylint tests.
COMPONENT_PRE_TEST_ACTION = ($(GMAKE) -C \
	$(COMPONENT_DIR)/../logilab-common install; \
	$(GMAKE) -C $(COMPONENT_DIR)/../logilab-astng install )

COMPONENT_TEST_ENV = PYTHONPATH=$(COMPONENT_DIR)/../logilab-common/build/prototype/$(MACH)$(PYTHON_VENDOR_PACKAGES):$(COMPONENT_DIR)/../logilab-astng/build/prototype/$(MACH)$(PYTHON_VENDOR_PACKAGES):$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES)

# Run pytest-2.7 from logilab-common's proto area for now, until the
# new version of logilab-common containing pytest is in CBE.
# Then we can change it to /usr/bin/pytest-$(PYTHON_VERSION).
COMPONENT_TEST_CMD = $(COMPONENT_DIR)/../logilab-common/build/prototype/$(MACH)/usr/bin/pytest-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# Expected failures for test target:
# 799 test cases, 2 errors, 3 skipped
# 10 modules OK (1 failed)

test:		$(TEST_NO_ARCH)

REQUIRED_PACKAGES += runtime/python-27
