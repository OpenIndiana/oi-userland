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
# Copyright 2019 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ddu
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_VERSION=	1.3.1
COMPONENT_LICENSE=	CDDL
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_FMRI= diagnostic/ddu
COMPONENT_CLASSIFICATION= System/Hardware
COMPONENT_LICENSE= CDDL,BSD3
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

COMPONENT_REVISION=$(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)

COMPONENT_SUMMARY=	Device Driver Utility (DDU)

GIT=git
GIT_REPO=https://github.com/OpenIndiana/ddu
GIT_BRANCH=oi/hipster
GIT_CHANGESET=HEAD

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk

# The ugly hack with update-publish target is necessary to update
# source from git repository on each "gmake publish".
# publish: target should appear before inclusion of ips.mk
publish: update-publish

include $(WS_TOP)/make-rules/ips.mk

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

$(SOURCE_DIR)/.prep: $(SOURCE_DIR)/.downloaded Makefile

COMPONENT_COPY_ACTION = \
        $(CP) -a $(SOURCE_DIR)/*  $(SOURCE_DIR)/.[^.]* $(@D)

ENV=/usr/bin/env -i

COMPONENT_BUILD_ARGS += CC=$(CC)

build: $(BUILD_32)

install: $(INSTALL_32)

download:: $(SOURCE_DIR)/.downloaded

REQUIRED_PACKAGES += developer/versioning/git
REQUIRED_PACKAGES += system/header
REQUIRED_PACKAGES += system/library/storage/libmpapi
REQUIRED_PACKAGES += text/locale

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/help-viewer/yelp
REQUIRED_PACKAGES += library/python/notify2-35
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += library/python/simplejson-35
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
