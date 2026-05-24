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
# Copyright 2022 Daniel Bell
# Copyright 2024 Benny Lyons
#

BUILD_STYLE=ant
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= netbeans
COMPONENT_VERSION= 30
COMPONENT_SUMMARY= Apache Netbeans IDE
COMPONENT_FMRI= editor/netbeans
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_DESCRIPTION=  IDE for C/C++, Java, PHP, Perl Python, and more \
                        For C/C++ inlude 8.2 Plugin Portal and install \
                        the C/C++ plugin (CND). The CPPLite Kit is in early \
                        stages of development.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-source.zip
COMPONENT_ARCHIVE_HASH=	sha256:707422e8b60835ea832a9630da85d508e77f8115f4f17491301965e2b43a1586
COMPONENT_ARCHIVE_URL=	https://dlcdn.apache.org/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= Apache-2.0
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_PROJECT_URL= https://www.netbeans.org/

UNPACK_ARGS= --relocate-to=$(COMPONENT_SRC)

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS=

PYTHON_SHEBANG="\#\!\/usr\/bin\/python$(PYTHON_VERSION)"

ifeq ($(MACH), i386)
BINARCH_64=x86_64
endif

ifeq ($(MACH), sparc)
BINARCH_64=sparc_64
endif

# these macros are used in the package manifest
PKG_MACROS += JAVA_DEFAULT=$(JAVA_DEFAULT) BINARCH_64=$(BINARCH_64)

$(BUILD_DIR_64)/.installed: $(BUILD_DIR_64)/.built
	mkdir -p $(PROTO_DIR)/usr/netbeans/;
	[ -d $(PROTO_DIR)/usr/netbeans/$(COMPONENT_VERSION) ] || cp -R $(BUILD_DIR_64)/nbbuild/netbeans $(PROTO_DIR)/usr/netbeans/$(COMPONENT_VERSION);
	for FILE in $(PROTO_DIR)/usr/netbeans/$(COMPONENT_VERSION)/ide/bin/nativeexecution/SunOS-$(BINARCH_64)/{pty,pty_open,process_start,killall}; do \
		/usr/bin/elfedit -e 'dyn:delete RUNPATH' $$FILE; \
		/usr/bin/elfedit -e 'dyn:delete RPATH' $$FILE; \
	done;
	mkdir -p $(PROTO_DIR)/usr/share/applications/;
	cp $(COMPONENT_DIR)/files/apache-netbeans.desktop $(PROTO_DIR)/usr/share/applications/;
	mkdir -p $(PROTO_DIR)/usr/share/icons/hicolor/32x32/apps;
	cp $(COMPONENT_DIR)/files/apache-netbeans.png $(PROTO_DIR)/usr/share/icons/hicolor/32x32/apps/;
	touch $(BUILD_DIR_64)/.installed;

install: $(BUILD_DIR_64)/.installed
	$(GSED) -i -e  "1s?.*?$(PYTHON_SHEBANG)?" $(PROTO_DIR)/usr/netbeans/$(COMPONENT_VERSION)/extide/ant/bin/runant.py;

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
