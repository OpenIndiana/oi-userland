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
# Copyright 2013 Adam Stevko. All rights reserved.
# Copyright 2014 Alexander Pyhalov. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sysding
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_VERSION=	0.5.11
COMPONENT_REVISION=	$(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)
COMPONENT_SUMMARY=	Simple tool for initial system configuration
COMPONENT_LICENSE=	CDDL
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_PROJECT_URL=	http://openindiana.org
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_FMRI=	service/management/sysding

GIT=git
GIT_REPO=https://github.com/OpenIndiana/sysding
GIT_BRANCH=oi
GIT_CHANGESET=HEAD

PATH= $(PATH.gnu)

CLEAN_PATHS += $(BUILD_DIR)
CLOBBER_PATHS += $(SOURCE_DIR)

COMPONENT_PREP_GIT=no
# The ugly hack with update-publish target is necessary to update
# source from git repository on each "gmake publish".
# publish: target should appear before inclusion of ips.mk
publish: update-publish

include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/common.mk

$(SOURCE_DIR)/.downloaded: $(ARCHIVES:%=$(USERLAND_ARCHIVES)%)
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	@cd $(SOURCE_DIR) ; $(GIT) checkout $(GIT_BRANCH) ; $(GIT) pull \
	  $(GIT_REPO) ; $(GIT) log -1 --format=%H > .downloaded

update-publish:
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	cd $(SOURCE_DIR) ; $(GIT) pull $(GIT_REPO) ; \
	  [ "$$($(GIT) log -1 --format=%H)" == "$$(cat .downloaded)" ] || \
	  ( $(GIT) log -1 --format=%H > .downloaded && $(MAKE) -C $$OLDPWD publish )

COMPONENT_BUILD_TARGETS = all

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

download:: $(SOURCE_DIR)/.downloaded

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
