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
# Copyright 2016-2021 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				jenkins-swarm-client
COMPONENT_VERSION=			3.25
COMPONENT_ARCHIVE_HASH=		sha256:f4039299ae006a7c52f4c750b49a43f9273b4d2638b53d9b4fc811c8a954a4af
COMPONENT_ARCHIVE=			$(COMPONENT_NAME)-$(COMPONENT_VERSION).jar
COMPONENT_FMRI=				developer/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_SRC=				$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=		https://plugins.jenkins.io/swarm/
COMPONENT_ARCHIVE_URL=\
	https://repo.jenkins-ci.org/releases/org/jenkins-ci/plugins/swarm-client/$(COMPONENT_VERSION)/swarm-client-$(COMPONENT_VERSION).jar
COMPONENT_LICENSE=			MIT
COMPONENT_LICENSE_FILE= 	jenkins.license
COMPONENT_SUMMARY=			Self-registering agent for Jenkins automation server

# Note: for the agent, we only download and place a JAR - no unpacking, no building...
include $(WS_MAKE_RULES)/prep-download.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CLEAN_PATHS += $(SOURCE_DIR)

download::

$(SOURCE_DIR)/.prep:    download
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::  $(SOURCE_DIR)/.prep

clean::
	$(PRE_CLEAN_ACTION)
	$(RM) -r $(CLEAN_PATHS)

clobber::   clean
	$(RM) -r $(CLOBBER_PATHS)

COMPONENT_PREP_ACTION = ( $(MKDIR) $(@D)/ && ln -sfr $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) $(COMPONENT_DIR)/files/Makefile $(@D)/ )

# This, and the symlinks in the custom Makefile, save quite a bit
# of storage overhead (do not need to copy the WAR 3 extra times)
COMPONENT_COPY_ACTION = ( $(CLONEY) $(SOURCE_DIR)/ $(@D)/ )

COMPONENT_INSTALL_ENV += COMPONENT_VERSION=$(COMPONENT_VERSION)
COMPONENT_INSTALL_ENV += COMPONENT_NAME=$(COMPONENT_NAME)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Service method script relies on bashisms
REQUIRED_PACKAGES += shell/bash

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += file/gnu-coreutils
