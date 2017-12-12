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
# Copyright 2017 Gary Mills
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nwam-manager
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_VERSION=	1.151.0
COMPONENT_LICENSE=	CDDL
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_FMRI=		desktop/administration/nwam-manager
COMPONENT_CLASSIFICATION=       System/Administration and Configuration

COMPONENT_REVISION=$(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)

COMPONENT_SUMMARY=	Network Auto-Magic User Interface

GIT=git
GIT_REPO=https://github.com/OpenIndiana/nwam-manager
GIT_BRANCH=oi/hipster
GIT_CHANGESET=HEAD

PATH = $(PATH.gnu)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk

# The ugly hack with update-publish target is necessary to update
# source from git repository on each "gmake publish".
# publish: target should appear before inclusion of ips.mk
publish: update-publish

include $(WS_MAKE_RULES)/ips.mk

$(SOURCE_DIR)/.downloaded: $(ARCHIVES:%=$(USERLAND_ARCHIVES)%)
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	@cd $(SOURCE_DIR) ; $(GIT) checkout $(GIT_BRANCH) ; $(GIT) pull \
	  $(GIT_REPO) ; $(GIT) log -1 --format=%H > .downloaded

COMPONENT_PREP_ACTION = \
        (cd $(@D);  $(MKDIR) m4 && \
		libtoolize --copy --force && \
		gnome-doc-prepare --force && \
		intltoolize --force --copy --automake && \
		aclocal -I m4 && \
		autoheader && \
		automake --add-missing --copy --force && \
		autoconf)

# Missing include files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=/usr/lib
CONFIGURE_OPTIONS += --localstatedir=/var/lib
CONFIGURE_OPTIONS += --enable-private-nwam-headers

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

update-publish:
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	cd $(SOURCE_DIR) ; $(GIT) pull $(GIT_REPO) ; \
	  [ "$$($(GIT) log -1 --format=%H)" == "$$(cat .downloaded)" ] || \
	  ( $(GIT) log -1 --format=%H > .downloaded && $(MAKE) -C $$OLDPWD publish )

$(SOURCE_DIR)/.prep: $(SOURCE_DIR)/.downloaded Makefile

build: $(BUILD_32)

install: $(INSTALL_32)

download:: $(SOURCE_DIR)/.downloaded

REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
