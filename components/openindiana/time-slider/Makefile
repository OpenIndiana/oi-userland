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

BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		time-slider
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_VERSION=	0.2.101
COMPONENT_SUMMARY=	Time Slider ZFS snapshot management for GNOME
COMPONENT_FMRI=		desktop/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Configuration and Preferences
COMPONENT_LICENSE=	CDDL
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

COMPONENT_REVISION=$(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)

GIT=git
GIT_REPO=https://github.com/OpenIndiana/time-slider
GIT_BRANCH=master
GIT_CHANGESET=HEAD

SINGLE_PYTHON_VERSION = yes

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_GIT=no

# The ugly hack with update-publish target is necessary to update
# source from git repository on each "gmake publish".
# publish: target should appear before inclusion of common.mk
publish: update-publish

TEST_TARGET = $(NO_TESTS)

include $(WS_TOP)/make-rules/common.mk

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

download:: $(SOURCE_DIR)/.downloaded

# Python modules are installed in non-default location so make sure pkgdepend
# is able to find them
PKGDEPEND_RUNPATH += $(PROTOUSRSHAREDIR)/time-slider/lib
PKGDEPEND_RUNPATH += $(PROTOUSRSHAREDIR)/time-slider/lib/plugin

CLOBBER_PATHS += $(SOURCE_DIR)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
