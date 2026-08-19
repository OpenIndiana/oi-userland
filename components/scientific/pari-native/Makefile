#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2025,2026 David Stes

#
# IPS mediator "pari" mediator-implementation set to "native".
# The native or classical PARI kernel does not use GNU gmp.
#
# NOTE: the PARI manifest files are NOT covered by the CDDL.
# The manifest files hold no license and copyright info per explicit request from Bill Allombert from the PARI team.
#

USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pari-native
COMPONENT_VERSION=	2.17.4
COMPONENT_SUMMARY=	PARI/GP (with Native Kernel) is a computer algebra system with the main aim of facilitating number theory computations
COMPONENT_PROJECT_URL=	https://pari.math.u-bordeaux.fr
COMPONENT_SRC=		pari-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:02651d99c391007d384b3fadbc20abc6916b77036f9e496c99e9ce8688ca4b53
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/pub/pari/unix/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/math/pari-native
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=     	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Configure has an option --builddir but this fails when built outside of source tree
# The PARI script config/genfunclist uses find -type f and skips symlinks
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# PARI/gp Configure is not autoconf 
CONFIGURE_SCRIPT= $(SOURCE_DIR)/Configure

# reset all options because Configure does not understand --sbindir= only --dir
CONFIGURE_OPTIONS= --prefix=$(CONFIGURE_PREFIX)
# PARI/gp installs its 64bit library in /usr/lib
CONFIGURE_OPTIONS += --libdir=$(USRLIBDIR64)
# multi-threaded libraries (enables tls, or thread local stack)
CONFIGURE_OPTIONS += --mt=pthread
CONFIGURE_OPTIONS += --with-readline
CONFIGURE_OPTIONS += --without-gmp

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"

# all does not work because documentation requires Tex typesetting
COMPONENT_BUILD_TARGETS= gp

# dobench is a quicktest, test-all takes more time and also compares gp-static
# try to do all regression tests but only on the dynamic executable gp-dyn
COMPONENT_TEST_TARGETS= dyntest-all

# I believe PARI measures with test-all diffs between static and dyn linked gp
# the test script is in : src/test/dotest
# I think it prints timing information and checks for correctness
# the timing info could be useful but for our purprose remove/transform it
COMPONENT_TEST_TRANSFORMS += '-e "s/gp-sta..TIME=[ ]*[0-9]*//g"'
COMPONENT_TEST_TRANSFORMS += '-e "s/gp-dyn..TIME=[ ]*[0-9]*//g"'
COMPONENT_TEST_TRANSFORMS += '-e "/Total bench/d"'

# gmake test dependencies
TEST_REQUIRED_PACKAGES += library/math/pari-elldata

# Auto-generated dependencies
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += library/math/pari
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
