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
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openindiana-welcome
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_VERSION=	1.0
COMPONENT_REVISION=	$(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_SUMMARY=	OpenIndiana Welcome Document
COMPONENT_FMRI=		release/os-welcome
COMPONENT_CLASSIFICATION=	System/Text Tools

PKG_MACROS+=	GIT_REPO="$(GIT_REPO)"

GIT=		git
GIT_REPO=	https://github.com/OpenIndiana/openindiana-welcome
GIT_BRANCH=	master
GIT_CHANGESET=	HEAD

PATH=$(PATH.gnu)

PYTHON_VERSION=3.5

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk

CONFIGURE_ENV += PYTHON=$(PYTHON)

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
	cd $(@D) &&\
		touch config.rpath src/config.h.in&&\
		libtoolize --force &&\
		aclocal -Im4  &&\
		intltoolize --copy --force --automake &&\
		automake --add-missing -f -i &&\
		autoconf -f
	touch $(SOURCE_DIR)/.prep

build: $(BUILD_32)

install: $(INSTALL_32)

download:: $(SOURCE_DIR)/.downloaded

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += runtime/python-35
