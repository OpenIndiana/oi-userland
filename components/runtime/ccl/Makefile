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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ccl
COMPONENT_VERSION=	1.12.2
COMPONENT_SUMMARY=	ccl - Clozure Common Lisp
COMPONENT_PROJECT_URL=	https://ccl.clozure.com/
COMPONENT_SRC=		ccl
COMPONENT_ARCHIVE=	ccl-$(COMPONENT_VERSION)-solarisx86.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f058137c92349ccce86a2725c68f4129ed660d07d834b0794de441339366dc8d
COMPONENT_ARCHIVE_URL=  https://github.com/Clozure/ccl/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	runtime/ccl
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# We need libsocket to be linked into ccl, despite of linker opinion about it.
# Otherwise we receive
# Error: Can't resolve foreign symbol "socket"
# when sockets are used
LD_Z_IGNORE=

COMPONENT_COPY_ACTION = cp -r $(SOURCE_DIR)/* $(@D)

BUILD_CCL_64 = $(BUILD_DIR_64)/.built_ccl
MY_INSTALL = $(BUILD_DIR_64)/.my_installed

CCL_DIRECTORY = /usr/lib/ccl

INST_FILES = bin compiler doc examples level-0  level-1
INST_FILES += lib  library  objc-bridge  solarisx64-headers 
INST_FILES += sx86-boot64 sx86cl64 sx86cl64.image  tools  xdump

COMPONENT_BUILD_ARGS += -C $(BUILD_DIR_$(BITS))/lisp-kernel/solarisx64

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"


$(BUILD_CCL_64):	$(BUILD_64)
	cd $(BUILD_DIR_64) ; $(ENV) $(COMPONENT_BUILD_ENV) \
        ./sx86cl64  --no-init --batch --quiet  --eval "(ccl:rebuild-ccl :full t)" \
	--eval "(quit)"
	$(TOUCH) $(@)

$(MY_INSTALL): $(BUILD_CCL_64)
	[ -d $(PROTO_DIR)/$(CCL_DIRECTORY) ] || $(MKDIR) $(PROTO_DIR)/$(CCL_DIRECTORY)
	cd $(@D); cp -r $(INST_FILES) $(PROTO_DIR)/$(CCL_DIRECTORY) 
	rm -fr $(PROTO_DIR)/usr/lib/ccl/solarisx64-headers/.svn
	$(TOUCH) $@

build:	$(BUILD_64) $(BUILD_CCL_64)

install: $(MY_INSTALL)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
