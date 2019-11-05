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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		swig
COMPONENT_VERSION=	3.0.10
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=	Simplified Wrapper and Interface Generator
COMPONENT_PROJECT_URL=	http://www.swig.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2939aae39dec06095462f1b95ce1c958ac80d07b926e48871046d17c0094f44c
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/swig/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/swig
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=	GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(JAVA_HOME)/bin:/usr/bin

# This is needed because the community provided 'check' target is not viewpath aware
COMPONENT_PRE_CONFIGURE_ACTION =      ($(CLONEY) $(SOURCE_DIR) $(@D))

PHP.32=/usr/php/bin/php
PHP.64=/usr/php/bin/$(MACH64)/php
PHP=$(PHP.$(BITS))

CONFIGURE_ENV += JAVA_HOME="$(JAVA_HOME)"
CONFIGURE_OPTIONS +=	--with-javaincl="$(JAVA_HOME)/include"
CONFIGURE_OPTIONS +=	--with-python="$(PYTHON)"
CONFIGURE_OPTIONS +=	--with-perl="$(PERL)"
CONFIGURE_OPTIONS +=	--with-php="$(PHP)"
CONFIGURE_OPTIONS +=	--with-ruby="$(RUBY)"

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The additional swig specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "/Entering directory/d" ' \
	'-e "/Leaving directory/d" '

# The test-suite can be run in a partialcheck mode where just SWIG is
# executed, that is, the compile, link and running of the testcases is
# not performed. Note that the partialcheck does not require the target
# language to be correctly configured and detected. Just execute the
# languages that we care about and that are known to work.
COMPONENT_TEST_TARGETS = \
        partialcheck-guile-test-suite \
        partialcheck-lua-test-suite \
        partialcheck-perl5-test-suite \
        partialcheck-php-test-suite \
        partialcheck-python-test-suite \
        partialcheck-ruby-test-suite

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += developer/java/openjdk7
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/ocaml
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/ruby-23
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += web/php-73
