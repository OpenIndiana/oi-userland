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

BUILD_STYLE= configure
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         swig
COMPONENT_VERSION=      4.1.1
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      Simplified Wrapper and Interface Generator
COMPONENT_PROJECT_URL=  https://www.swig.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2af08aced8fcd65cdb5cc62426768914bedc735b1c250325203716f78e39ac9b
COMPONENT_ARCHIVE_URL=  https://prdownloads.sourceforge.net/swig/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/swig
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYRIGHT

include $(WS_MAKE_RULES)/common.mk

PATH=$(JAVA_HOME)/bin:/usr/bin

# This is needed because the community provided 'check' target is not viewpath aware
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

PHP=/usr/bin/php
RUBY_VERSION= 2.6

CONFIGURE_ENV += JAVA_HOME="$(JAVA11_HOME)"
CONFIGURE_OPTIONS += --with-javaincl="$(JAVA11_HOME)/include"
CONFIGURE_OPTIONS += --with-python="$(PYTHON)"
CONFIGURE_OPTIONS += --with-perl="$(PERL)"
CONFIGURE_OPTIONS += --with-php="$(PHP)"
CONFIGURE_OPTIONS += --with-ruby="$(RUBY)"

ASLR_MODE = $(ASLR_ENABLE)

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
REQUIRED_PACKAGES += runtime/java/openjdk11
REQUIRED_PACKAGES += developer/parser/bison-37
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/ocaml
REQUIRED_PACKAGES += library/ocaml/ocaml-findlib
REQUIRED_PACKAGES += runtime/ruby-26

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
