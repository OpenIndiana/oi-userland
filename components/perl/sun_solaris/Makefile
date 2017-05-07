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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= sun-solaris

COMPONENT_SUMMARY=Perl Sun::Solaris Modules
COMPONENT_SRC= src

PERL_VERSIONS = 5.16
# Illumos component, no explicit version
COMPONENT_VERSION= 5.11

include ../../../make-rules/prep.mk
include ../../../make-rules/ips.mk
include ../../../make-rules/makemaker.mk

CLEAN_PATHS=required-pkgs.mk

MODULES:=BSM  Exacct Exacct/Catalog Exacct/File Exacct/Object Intrs  Kstat  Lgrp  PerlGcc  Pg  Privilege  Project  Task  Ucred  Utils

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

$(BUILD_DIR)/%/.installed:      $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(for i in $(MODULES); do \
		cd $(@D)/Sun/Solaris/$$i ; $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) \
                        $(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS) ; done)
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

install: $(INSTALL_32) 

build: $(BUILD_32)

install: $(INSTALL_32)

clean::  $(NO_CLEAN)

