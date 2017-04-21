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
# Copyright 2016 Jim Klimov
#

#
# This Makefile installs groovy into location specified by variables below,
# as defined in common oi-userland framework (this file is included from
# main recipe Makefile).
# List of FS objects below coresponds to groovy-2.4.7 layout.
#

LN_S ?= $(LN) -s
LN_SYM_REL = $(GNUBIN)/ln -s -r

$(BUILD_DIR_$(BITS))/.installed-groovy: $(BUILD_$(BITS)) $(SOURCE_DIR)/.prep
	$(MKDIR) $(PROTOUSRSHAREDIR)/$(COMPONENT_NAME)-$(COMPONENT_VERSION) $(PROTOUSRBINDIR)
	cd $(SOURCE_DIR) && \
		$(CP) -pr \
bin \
conf \
embeddable \
grooid \
indy \
lib \
LICENSE \
licenses \
NOTICE \
		$(PROTOUSRSHAREDIR)/$(COMPONENT_NAME)-$(COMPONENT_VERSION)
	$(RM) $(PROTOUSRSHAREDIR)/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/bin/*.bat
	cd $(PROTOUSRBINDIR) && \
		$(LN_SYM_REL) $(PROTOUSRSHAREDIR)/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/bin/* .
	$(TOUCH) $@

install-groovy: $(BUILD_DIR_$(BITS))/.installed-groovy
