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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

# parfait is suddenly unhappy with us (21638460)
export PARFAIT_BUILD=no
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		swig
COMPONENT_VERSION=	3.0.10
COMPONENT_PROJECT_URL=	http://www.swig.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:2939aae39dec06095462f1b95ce1c958ac80d07b926e48871046d17c0094f44c
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/swig/$(COMPONENT_ARCHIVE)

TPNO=			30244	

include $(WS_MAKE_RULES)/common.mk

PATH=$(SPRO_VROOT)/bin:$(JAVA_HOME)/bin:$(USRBINDIR)

# This is needed because the community provided 'check' target is not viewpath aware
COMPONENT_PRE_CONFIGURE_ACTION =      ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += JAVA_HOME="$(JAVA_HOME)"
CONFIGURE_OPTIONS +=	--with-javaincl="$(JAVA_HOME)/include"

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

REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime 
REQUIRED_PACKAGES += system/library/math
