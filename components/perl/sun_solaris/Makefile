#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
# Copyright 2022 (c) Tim Mooney.  All rights reserved
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sun-solaris
# Illumos component, no explicit version
COMPONENT_VERSION=	0.5.11
COMPONENT_REVISION=	1
# keep FMRI in the manifest for now
#COMPONENT_FMRI=
COMPONENT_SUMMARY=	Perl Sun::Solaris Modules
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		src
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	sun-solaris.license


PERL_VERSION  = 5.34
PERL_VERSIONS = 5.34
PERL_64_ONLY_VERSIONS= 5.34

# because the manifest does not use -PERLVER and the version we're building
# for may not be the default version, we need to ensure that PERL_ARCH is
# defined correctly
PERL = $(PERL.$(PERL_VERSION))
PERL_ARCH = $(shell $(PERL) -e 'use Config; print $$Config{archname}')

# these modules currently have no test suite
TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk


CLEAN_PATHS=required-pkgs.mk

MODULES:=BSM  Exacct Exacct/Catalog Exacct/File Exacct/Object Intrs  Kstat  Lgrp  Pg  Privilege  Project  Task  Ucred  Utils

$(BUILD_DIR)/%/.configured:     $(SOURCE_DIR)/.prep
	($(RM) -r $(@D) ; $(MKDIR) $(@D))
	cp -a $(SOURCE_DIR)/* $(@D)
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	( for i in $(MODULES); do \
			cd $(@D)/Sun/Solaris/$$i ; $(COMPONENT_CONFIGURE_ENV) $(PERL) $(PERL_FLAGS) \
				Makefile.PL $(PERL_STUDIO_OVERWRITE) $(CONFIGURE_OPTIONS) ; done )
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

COMPONENT_BUILD_ARGS+= DESTDIR=$(PROTO_DIR)
$(BUILD_DIR)/%/.built:  $(BUILD_DIR)/%/.configured
	$(COMPONENT_PRE_BUILD_ACTION)
	(for i in $(MODULES); do \
		cd $(@D)/Sun/Solaris/$$i ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
		$(COMPONENT_BUILD_TARGETS) ; done)
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

#
# add u+w to the shared objects so publish can run elfedit on them.
#
COMPONENT_POST_INSTALL_ACTION = \
	(for s in $$(find $(PROTO_DIR) -type f -name '*.so') ; do \
		chmod u+w $$s ; \
	done)

$(BUILD_DIR)/%/.installed:      $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(for i in $(MODULES); do \
		cd $(@D)/Sun/Solaris/$$i ; $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) \
                        $(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS) ; done)
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

clean::  $(NO_CLEAN)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += system/library
