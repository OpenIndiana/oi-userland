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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2023 Friedrich Kink
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         swig
COMPONENT_VERSION=	4.3.0
COMPONENT_SUMMARY=      Simplified Wrapper and Interface Generator
COMPONENT_PROJECT_URL=  https://www.swig.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f7203ef796f61af986c70c05816236cbd0d31b7aa9631e5ab53020ab7804aa9e
COMPONENT_ARCHIVE_URL=  https://prdownloads.sourceforge.net/swig/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/swig
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE=	GPL-3.0-or-later

include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		printf -- '--- LICENSE ---------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/LICENSE ; \
		printf '\n\n--- LICENSE-GPL -----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/LICENSE-GPL ; \
		printf '\n\n--- LICENSE-UNIVERSITIES --------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/LICENSE-UNIVERSITIES ; \
		printf '\n--- COPYRIGHT -------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYRIGHT \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# This is needed because the community provided 'check' target is not viewpath aware
CLONEY_MODE = symlink

PHP=/usr/bin/php

CONFIGURE_ENV += JAVA_HOME="$(JAVA_HOME)"
CONFIGURE_OPTIONS += --with-javaincl="$(JAVA_HOME)/include"
CONFIGURE_OPTIONS += --with-python="$(PYTHON)"
CONFIGURE_OPTIONS += --with-perl="$(PERL)"
CONFIGURE_OPTIONS += --with-php="$(PHP)"
CONFIGURE_OPTIONS += --with-ruby="$(RUBY)"

ASLR_MODE = $(ASLR_ENABLE)

# Install additional man pages
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm644 $(COMPONENT_DIR)/files/ccache-swig.1 $(PROTOUSRSHAREMAN1DIR)/ccache-swig.1 ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm644 $(COMPONENT_DIR)/files/swig.1 $(PROTOUSRSHAREMAN1DIR)/swig.1 ;

# Install additional documentation
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm644 $(SOURCE_DIR)/Doc/README $(PROTOUSRSHAREDIR)/swig/$(COMPONENT_VERSION)/doc/README ;
COMPONENT_POST_INSTALL_ACTION += $(CP) -a $(SOURCE_DIR)/Doc/Devel $(PROTOUSRSHAREDIR)/swig/$(COMPONENT_VERSION)/doc/devel ;
COMPONENT_POST_INSTALL_ACTION += $(CP) -a $(SOURCE_DIR)/Doc/Manual $(PROTOUSRSHAREDIR)/swig/$(COMPONENT_VERSION)/doc/manual ;

# The additional swig specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "/Entering directory/d" ' \
	'-e "/^cp:/d" ' \
	'-e "/: Warning /d" ' \
	'-e "/Leaving directory/d" '

# The test-suite can be run in a partialcheck mode where just SWIG is
# executed, that is, the compile, link and running of the testcases is
# not performed. Note that the partialcheck does not require the target
# language to be correctly configured and detected. Just execute the
# languages that we care about and that are known to work.
COMPONENT_TEST_TARGETS = \
        partialcheck-guile-test-suite \
        partialcheck-lua-test-suite \
        partialcheck-ocaml-test-suite \
        partialcheck-perl5-test-suite \
        partialcheck-php-test-suite \
        partialcheck-python-test-suite \
        partialcheck-ruby-test-suite

# Build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += developer/parser/bison-37
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/ocaml
REQUIRED_PACKAGES += library/ocaml/ocaml-findlib
REQUIRED_PACKAGES += runtime/ruby-32

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
