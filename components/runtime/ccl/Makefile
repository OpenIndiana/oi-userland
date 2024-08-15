#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Alexander Pyhalov
# Copyright 2024 Andreas Wacknitz
#

BUILD_STYLE= justmake
CLONEY_ARGS= CLONEY_MODE="copy"
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ccl
COMPONENT_VERSION=	1.13
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	ccl - Clozure Common Lisp
COMPONENT_PROJECT_URL=	https://ccl.clozure.com/
COMPONENT_SRC=		ccl
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-solarisx86.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:be96b859681e5032d0e484b9fb8e0fa63ab36311e5d903eee98bd5a19b508b7a
COMPONENT_ARCHIVE_URL=  https://github.com/Clozure/ccl/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	runtime/ccl
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Don't remove libraries that seem not to be used.
# Removal of libraries (eg. libsocket or libmath) will lead to errors when ffi is being used with ccl.
#
# We will get errors like this in such situations:
# Error: Can't resolve foreign symbol "socket"
# Error: Can't resolve foreign symbol "log"
#
LD_Z_IGNORE=

CCL_DIRECTORY = /usr/lib/ccl

INST_FILES = bin compiler doc examples level-0 level-1
INST_FILES += lib library objc-bridge solarisx64-headers
INST_FILES += sx86-boot64 sx86cl64 sx86cl64.image tools xdump

COMPONENT_BUILD_ARGS += -C $(BUILD_DIR_$(BITS))/lisp-kernel/solarisx64

# ccl doesn't have a Makefile. Thus, we define our own build action
COMPONENT_BUILD_ACTION= \
	cd $(@D) && \
	$(ENV) $(COMPONENT_BUILD_ENV) ./sx86cl64 --no-init --batch --quiet --eval "(ccl:rebuild-ccl :full t)" --eval "(quit)"

# We also need to provide our own install action
COMPONENT_INSTALL_ACTION= \
	[ -d $(PROTO_DIR)/$(CCL_DIRECTORY) ] || $(MKDIR) $(PROTO_DIR)/$(CCL_DIRECTORY) && \
	cd $(@D); $(CP) -r $(INST_FILES) $(PROTO_DIR)/$(CCL_DIRECTORY) && \
	$(RM) -rf $(PROTO_DIR)/usr/lib/ccl/doc/internals/.gitignore $(PROTO_DIR)/usr/lib/ccl/doc/manual/.gitignore

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
