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
# Copyright 2022 Till Wegmueller
#
include ../../../make-rules/shared-macros.mk

# NOTE: Before bumping to the new core version, take a look at
#   https://jenkins.io/changelog/ (weekly)
#   https://jenkins.io/changelog-stable/ (LTS)
# for "weather report" (user votes on good/bad state of the release).
# At some point it may make sense to deliver packaged LTS releases,
# and the initial recipe supports that notion already just in case,
# but no LTS issued so far includes updated libzfs.jar (v0.8+ needed).
# Note that for LTS it would make sense to define indexed "additional
# source" variables below, see e.g. docbook for inspiration.

COMPONENT_NAME=				jenkins
JENKINS_RELEASE=			weekly
COMPONENT_MAJOR_VERSION=	2
COMPONENT_MINOR_VERSION=	420
COMPONENT_ARCHIVE_HASH=		sha256:c9e0778a6eb54e652658ee757848d792bfbd702f7af14a8c2e05978155facc62
# See $(COMPONENT_ARCHIVE_URL).sha256 e.g. for current weekly release, run
#   wget -O - http://mirrors.jenkins-ci.org/war/latest/jenkins.war.sha256
# or for LTS
#   wget -O - http://mirrors.jenkins.io/war-stable/latest/jenkins.war.sha256

COMPONENT_VERSION=			$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_ARCHIVE=			$(COMPONENT_NAME)-$(JENKINS_RELEASE)-$(COMPONENT_VERSION).war
COMPONENT_FMRI=				developer/jenkins-core-$(JENKINS_RELEASE)
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_SRC=				$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=		https://jenkins.io/changelog/
COMPONENT_ARCHIVE_URL=		https://get.jenkins.io/war/$(COMPONENT_VERSION)/jenkins.war
COMPONENT_LICENSE=			MIT
COMPONENT_LICENSE_FILE= 	jenkins.license
COMPONENT_SUMMARY=			Jenkins is a Java-based CI automation server

# Note: for the core, we only download a WAR - no unpacking, no building...
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

COMPONENT_INSTALL_ENV += JENKINS_VERSION=$(COMPONENT_VERSION)
COMPONENT_INSTALL_ENV += JENKINS_RELEASE=$(JENKINS_RELEASE)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/java/openjdk17
