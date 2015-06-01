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
# Copyright 2015 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

#
# Rules to install a common lisp library package.
#
# To use these rules, just include ../make-rules/common-lisp.mk in your
# Makefile and define "build" and "install" targets.  E.g.,
#
#	build: $(BUILD_32)
#
# 	install: $(INSTALL_32)
#
# Since common lisp libraries are all source code, there is no need for
# BUILD_64 and INSTALL_64.

INSTALL_DIR =	$(PROTOCLDIR)/source/$(COMPONENT_NAME)

$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(MKDIR) $(PROTOCLDIR)
	$(MKDIR) $(PROTOCLDIR)/source
	$(MKDIR) $(PROTOCLDIR)/systems
	$(MKDIR) $(INSTALL_DIR)
	$(CP) -a $(SOURCE_DIR)/* $(INSTALL_DIR)
	(cd $(PROTOCLDIR)/systems; \
		$(RM) $(COMPONENT_NAME).asd; \
		$(LN) -s ../source/$(COMPONENT_NAME)/$(COMPONENT_NAME).asd)
	$(TOUCH) $@

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
