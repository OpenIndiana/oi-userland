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
# Copyright 2017 Adam Stevko
#

BUILD_STYLE = archive
BUILD_BITS = NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkgtree
COMPONENT_VERSION=	1.1
COMPONENT_REVISION=	4
COMPONENT_PROJECT_URL=	https://github.com/msmark/pkgtree
COMPONENT_FMRI=		developer/pkgtree
COMPONENT_CLASSIFICATION= System/Packaging
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/msmark/pkgtree/archive/v1.1.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:910e5dfc2e504ae48e2e125797cf6621b3b372a58e06f2fe8bb42657a0f8a238
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))
TEST_TARGET = $(TEST_$(MK_BITS))

include $(WS_MAKE_RULES)/common.mk

CLEAN_PATHS += $(BUILD_DIR)

$(BUILD_$(MK_BITS)): $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_$(MK_BITS)): $(BUILD_$(MK_BITS))
	$(MKDIR) $(PROTO_DIR) \
		$(PROTOUSRBINDIR) \
		$(PROTOUSRSHAREMAN1DIR)
	$(MKDIR) $(foreach ver, $(PERL_VERSIONS), $(PROTO_DIR)/usr/perl5/vendor_perl/$(ver))
	$(CP) -a $(SOURCE_DIR)/bin/pkgtree $(PROTOUSRBINDIR)
	$(POD2MAN) $(SOURCE_DIR)/bin/pkgtree $(PROTOUSRSHAREMAN1DIR)/pkgtree.1
	$(foreach ver, $(PERL_VERSIONS), $(CP) -a $(SOURCE_DIR)/lib/perl5/* $(PROTO_DIR)/usr/perl5/vendor_perl/$(ver) ; )
	$(TOUCH) $@

$(TEST_$(MK_BITS)): $(INSTALL_$(MK_BITS))
	$(SOURCE_DIR)/test.sh
	$(TOUCH) $@

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += runtime/perl
