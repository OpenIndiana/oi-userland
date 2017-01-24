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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		groovy
# Commit timestamp and previous known release (none here)
COMPONENT_VERSION=	2.4.7
COMPONENT_ARCHIVE=	apache-$(COMPONENT_NAME)-binary-$(COMPONENT_VERSION).zip
COMPONENT_FMRI=		developer/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://groovy-lang.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:438dd6098252647e88ff12ac5737d0d0f7e16a8e4e42e8be3e05a4c43abefbd5
COMPONENT_ARCHIVE_URL=	https://bintray.com/artifact/download/groovy/maven/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Apache-2.0,BSD,MIT,Eclipse,PublicDomain
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_SUMMARY=	Groovy is a Java-based scripting language

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# This is an archive with prebuilt binaries, nothing to build
$(BUILD_$(BITS)): $(SOURCE_DIR)/.prep
	$(MKDIR) $(BUILD_DIR_$(BITS))
	$(TOUCH) $@

build: $(BUILD_32)

# There are many "intimate" variables to pass into the other Makefile,
# so rather than run a sub-make we include it into our context.
include $(COMPONENT_DIR)/files/Makefile

$(INSTALL_32): install-groovy
	$(TOUCH) $@

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
