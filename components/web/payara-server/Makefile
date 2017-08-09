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
# Copyright 2017 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

# The Payara Server project took off where GlassFish 4.1-GA development
# stalled. Over the years it was re-synced with GF-4.1.1 and GF-4.1.2
# releases, to keep the capability of enhanced drop-in replacements.
# Payara project releases are on GitHub:
#   https://github.com/payara/Payara/releases
# e.g. https://github.com/payara/Payara/releases/download/payara-server-4.1.2.172/payara-4.1.2.172.zip
# Note to not pull Payara Blue (those are builds against IBM JDK)

# Note: this recipe does not provide a default SMF service since it is
# expected that the consumer sets up an administrative domain instance
# (default "domain1" is provided with a default admin and application
# server instances, https on 4848 and 8181 respectively), and after
# perhaps setting up admin passwords to this instance, etc. they can
# register it in system service framework like SMF with
#   /usr/share/payara/bin/asadmin create-service
# Alternately, a cluster-worker node or some other instnance types can
# be set up. So, we should not guess for the enterprisish users what
# they desire to achieve.

# Smaller subsets of Payara posed as middleware for microservices,
# embedded usage etc. without running a full application server
#   java -jar payara-micro.jar --deploy test.war
# are on project site with CDN links, but I saw no direct link yet:
#   https://www.payara.fish/downloads

COMPONENT_NAME=		payara
GLASSFISH_BASELINE=	4.1.2
PAYARA_VERSION=	172
PAYARA_PATCH=	0
PAYARA_RELEASE=	server

# The downloadable ZIP contains one top-level subdirectory which we strip
TARBALL_TOPDIR=	payara41

# Remote files for initial version do not include trailing ".0", we do
# Add suffix to initial releases, like "8.2": rename into "8.2.0"
# but keep subsequent ones intact like "8.2.1"
COMPONENT_VERSION=	$(GLASSFISH_BASELINE).$(PAYARA_VERSION).$(PAYARA_PATCH)
ifeq ($(strip $(PAYARA_PATCH)),0)
COMPONENT_SOURCE_VERSION=$(GLASSFISH_BASELINE).$(PAYARA_VERSION)
else
COMPONENT_SOURCE_VERSION=$(GLASSFISH_BASELINE).$(PAYARA_VERSION).$(PAYARA_PATCH)
endif

# Local filename including trailing ".0" if needed
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(PAYARA_RELEASE)-$(COMPONENT_VERSION).zip
# Local dir
COMPONENT_SRC=		$(COMPONENT_NAME)-$(PAYARA_RELEASE)-$(COMPONENT_VERSION)
# Remote filename might avoid trailing ".0"
COMPONENT_ARCHIVE_URL=\
	https://github.com/payara/Payara/releases/download/payara-$(PAYARA_RELEASE)-$(COMPONENT_SOURCE_VERSION)/payara-$(COMPONENT_SOURCE_VERSION).zip
COMPONENT_ARCHIVE_HASH=	\
	sha256:5ca8e79822cf9a9e7adca84a21ab79acb91b5b86489bcd5c9b34f62ec86dcd4a

COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_PROJECT_URL=	https://www.payara.fish/
COMPONENT_FMRI=		web/java-servlet/$(COMPONENT_NAME)-$(PAYARA_RELEASE)
COMPONENT_LICENSE=		GPLv2,CDDL
COMPONENT_LICENSE_FILE= payara.license
COMPONENT_SUMMARY=	Payara is a drop-in replacement for Glassfish application server

# Note: we only download a ZIP - no unpacking via fetcher, no building...
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
# of storage overhead (do not need to copy the ZIP 3 extra times)
COMPONENT_COPY_ACTION = ( $(CLONEY) $(SOURCE_DIR)/ $(@D)/ )

COMPONENT_INSTALL_ENV += COMPONENT_VERSION=$(COMPONENT_VERSION)
COMPONENT_INSTALL_ENV += PAYARA_RELEASE=$(PAYARA_RELEASE)
COMPONENT_INSTALL_ENV += TARBALL_TOPDIR=$(TARBALL_TOPDIR)
COMPONENT_INSTALL_ENV += COMPONENT_ARCHIVE=$(SOURCE_DIR)/$(COMPONENT_ARCHIVE)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Note: this recipe just downloads and packages stuff.
# No real build, no magic tools, no java even, should be needed!
# So, no custom REQUIRED_PACKAGES
