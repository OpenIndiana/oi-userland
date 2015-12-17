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
# Fixes to make it compile under Solaris and run under SMF Copyright (c) 2011-2015 by Jim Klimov
# Build/package procedure ported to OI/Hipster Copyright (c) 2015-2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		p0f
# For up-to-date latest version see http://lcamtuf.coredump.cx/p0f3/releases/
COMPONENT_VERSION=	3.09b
# IPS requires this to be numeric, no alpha, no leading zeroes
IPS_COMPONENT_VERSION=	3.0.9
COMPONENT_PROJECT_URL=	http://lcamtuf.coredump.cx/p0f3
# *Unofficial* Git source at https://github.com/p0f/p0f
COMPONENT_SUMMARY=	p0f - the passive OS fingerprinter daemon
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:543b68638e739be5c3e818c3958c3b124ac0ccb8be62ba274b4241dbdec00e7f
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		diagnostic/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	docs/COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

# lazyloading (indirectly enabled by -Bdirect) seems to cause problems with
# libpcap device enumeration.
LD_B_DIRECT=

CFLAGS +=		"-DFP_FILE=\"$(USRSHAREDIR)/$(COMPONENT_NAME)/p0f.fp\""

# Using direct make via ./build.sh script
COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)" VERSION="$(COMPONENT_VERSION_TXT)-hipster"
COMPONENT_BUILD_ENV_DEBUG +=	CFLAGS="$(CFLAGS) -g" VERSION="$(COMPONENT_VERSION_TXT)-hipster"

COMPONENT_PRE_BUILD_ACTION = \
	( $(RM) -r $(@D) && $(MKDIR) $(@D) && $(CLONEY) $(SOURCE_DIR) $(@D) )

# custom target, adapted from shared-macros.mk and configure.mk
$(BUILD_DIR)/%/.built: $(SOURCE_DIR)/.prep
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) && $(ENV) $(COMPONENT_BUILD_ENV_DEBUG) \
		$(GMAKE) debug && $(MV) p0f p0f-debug)
	(cd $(@D) && $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) clean)
	(cd $(@D) && $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) all)
	$(TOUCH) $@

# Common targets; currently some pointer macros are specifically 32-bit
# in the sources, so we do not make a 64-bit build
build:		$(BUILD_32)

install:	build
	$(TOUCH) $(INSTALL_32)

test:		$(NO_TESTS)

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
