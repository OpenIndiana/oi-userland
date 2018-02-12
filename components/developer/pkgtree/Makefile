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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkgtree
COMPONENT_VERSION=	1.1
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	https://github.com/msmark/pkgtree
COMPONENT_FMRI=		developer/pkgtree
COMPONENT_CLASSIFICATION= System/Packaging
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/msmark/pkgtree/archive/v1.1.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:910e5dfc2e504ae48e2e125797cf6621b3b372a58e06f2fe8bb42657a0f8a238
COMPONENT_LICENSE=	Apache 2.0 license
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

CLEAN_PATHS += $(BUILD_DIR)

$(BUILD_32):    $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_32): $(BUILD_32)
	$(MKDIR) $(PROTO_DIR) \
		$(PROTOUSRBINDIR) \
		$(PROTOUSRSHAREMAN1DIR)
	$(MKDIR) $(foreach ver, $(PERL_VERSIONS), $(PROTO_DIR)/usr/perl5/vendor_perl/$(ver))
	$(CP) -a $(SOURCE_DIR)/bin/pkgtree $(PROTOUSRBINDIR)
	$(POD2MAN) $(SOURCE_DIR)/bin/pkgtree $(PROTOUSRSHAREMAN1DIR)/pkgtree.1
	$(foreach ver, $(PERL_VERSIONS), $(CP) -a $(SOURCE_DIR)/lib/perl5/* $(PROTO_DIR)/usr/perl5/vendor_perl/$(ver) ; )
	$(TOUCH) $@

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
