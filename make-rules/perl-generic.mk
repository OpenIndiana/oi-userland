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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/prep.mk
include ../../../make-rules/ips.mk

# Maybe not necessary, but won't do any harm neither
PERL_ENV = MAKE=$(GMAKE)
# PATH has to contain the same CC compiler which was used for perl component
# itself
PERL_ENV += PATH=$(dir $(CC.studio.32)):$(PATH)

PERL_ARCH=$(shell arch)

PKG_MACROS             +=      PERL_ARCH=$(PERL_ARCH)
PKG_MACROS             +=      PERL_VERSION=$(PERL_VERSION)


################
# Prepare
################
$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; $(PERL_ENV) $(PERL) Makefile.PL)
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@


################
# Build
################
COMPONENT_BUILD_ENV	+= $(PERL_ENV)

# build the configured source
$(BUILD_DIR)/%/.built:	$(BUILD_DIR)/%/.configured
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

build:		$(VARIANTS:%=%/.built)


################
# Install
################
COMPONENT_INSTALL_TARGETS = \
	DESTDIR="$(PROTO_DIR)" install_vendor

$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) \
			$(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS))
	# Now walk the files which should have the magic line #!/usr/bin/perl
	# changed to comply with Solaris standards
	(cd $(PROTO_DIR); \
		for file in $(PERL_FILES_TO_UPDATE_MAGIC_LINE); do \
			$(CHMOD) +w $$file; \
			$(PERL) -pi -e 's,^#!.*?perl,#!$(PERL), if $$.==1' $$file; \
		done)
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

install:	$(VARIANTS:%=%/.installed)


################
# Test
################
# Do not create .tested file, so that test can be re-run anytime
$(BUILD_DIR)/%/.tested:	$(BUILD_DIR)/%/.built
	@cd $(@D); $(GMAKE) test

test:  $(VARIANTS:%=%/.tested)


################
# General stuff
################
BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

clean:: 
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR) $(VARIANTS)

include ../../../make-rules/depend.mk
