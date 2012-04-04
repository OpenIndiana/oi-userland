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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

#
# This component is not to be installed. It is used from openssl-0.9.8-fips-140
# to build FIPS-140 certified OpenSSL libraries.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	openssl-fips
COMPONENT_VERSION =	1.2
COMPONENT_SRC =		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:f09c3040da6cdd8bdd8c9cf01af8f14f89ee84d1
COMPONENT_ARCHIVE_URL =	http://www.openssl.org/source/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin:/usr/perl5/bin

# In order to build a 32bit version on a 64bit system the isalist(1) command
# must be substituted for the 32bit build so that amd64|sparcv9 is not part of
# its output. isalist is used internally when configuring the canister before
# building it. In order to allow make install to be run as a no-op we have to
# fake "make install" since we do not want to install the files anywhere. The
# command sets U1 and U2 are defined in the FIPS 1.2 security policy and must be
# run as shown there. Nothing from the tarball can be modified. We use the U2
# command set, see below.
FAKE_ISALIST = 32/isalist
FAKE_MAKE = fips-gmake
FAKE_CC = cc
FAKE_APPS = $(FAKE_ISALIST) $(FAKE_MAKE) $(FAKE_CC)

# Do not use $(PWD), it would not work if run from a different directory with
# "gmake -C" as we do from openssl-0.9.8-fips-140.
# we'll also pick up gcc if we find it in the path, so force it to
# find one that doesn't work like it wants
FIPS_PATH_32 = $(COMPONENT_DIR)/32:$(COMPONENT_DIR)/gcc:$(PATH)
FIPS_PATH_64 = $(COMPONENT_DIR)/gcc:$(PATH)

OPENSSL_FIPS_HMAC_KEY = etaonrishdlcupfm
OPENSSL_FIPS_HMAC = 79193087e8115df76d3de1f346f7410df79cf6e0

# There is a broken link in the tarball which causes cp(1) to fail which would
# fail the whole configure process. It's safer to get rid of the link than
# adding "true" at the end of COMPONENT_PRE_CONFIGURE_ACTION since that could
# hide real issues.
COMPONENT_PRE_CONFIGURE_ACTION = ( cd $(@D); \
    $(RM) $(SOURCE_DIR)/test/fips_aes_data; $(CP) -r $(SOURCE_DIR)/* .; )

# There is a specific way that must be followed to build the FIPS-140 canister.
# It is "./config fipscanisterbuild; make; make install" and is called a command
# set "U2" in the OpenSSL FIPS-140 User Guide.
CONFIGURE_SCRIPT = config
CONFIGURE_OPTIONS = fipscanisterbuild
COMPONENT_BUILD_ARGS =
COMPONENT_BUILD_TARGETS =
COMPONENT_INSTALL_ARGS =
COMPONENT_INSTALL_TARGETS = install
CONFIGURE_ENV += FIPS_SITE_LD=$(LD) PATH=$(FIPS_PATH_$(BITS))
# Add COMPONENT_DIR to PATH so cc wrapper can be found.
COMPONENT_BUILD_ENV += FIPS_SITE_LD=$(LD) REALCC=$(CC) MYMAKE=$(MAKE) PATH=$(COMPONENT_DIR):$(PATH)

$(BUILD_32_and_64): $(FAKE_APPS)

# You should not use this target with this component unless testing or
# debugging. The OpenSSL FIPS-140 policy is strict and full U2 command set
# should be run. See above for more information.
build:		$(BUILD_32_and_64)

# We must make the "install" target a no-op (but must run it to be compliant).
# See above for more information.
install:	GMAKE = $(COMPONENT_DIR)/fips-gmake
install:	$(BUILD_DIR_32)/.verified $(BUILD_DIR_64)/.verified

# This is a recommended set of commands to verify that the FIPS-140 mode can be
# used and that we used the correct tarball.
$(BUILD_DIR)/%/.verified:	$(BUILD_DIR)/%/.installed
	(printf x; \
	$(ENV) - OPENSSL_FIPS=1 LD_LIBRARY_PATH=$(@D) \
	$(@D)/apps/openssl sha1 -hmac $(OPENSSL_FIPS_HMAC_KEY) \
	    $(COMPONENT_ARCHIVE)) | \
	    $(NAWK) '{ if ($$2 != "$(OPENSSL_FIPS_HMAC)") exit 1 }'
	@echo Basic FIPS-140 mode verification passed.
	$(TOUCH) $@	    	

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
