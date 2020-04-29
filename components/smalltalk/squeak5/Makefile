#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Package Makefile for the "OpenSmalltalk Cog Spur" Squeak Smalltalk V5 system
# See http://squeak.org and http://opensmalltalk.org
#

BUILD_BITS=64
COMPILER=gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		squeak5
COMPONENT_VERSION=	5.0.6
COMPONENT_SUMMARY=	The Squeak V5 Smalltalk System
COMPONENT_PROJECT_URL=	http://www.squeak.org
COMPONENT_FMRI=		runtime/squeak5
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=	LICENSE
COMPONENT_SRC=		opensmalltalk-vm

GIT=			git
GIT_REPO=		https://github.com/cstes/opensmalltalk-vm.git
GIT_BRANCH=		sun
GIT_TAG=		sun-v5.0.6

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# The ugly hack with update-publish target is necessary to update
# source from git repository on each "gmake publish".
publish: update-publish

# the opensmalltalk README says to run scripts/updateSCCSVersions 
# but I believe that we can't do this on unversioned git files
# so we must build from git sources, I believe

$(SOURCE_DIR)/.downloaded: $(ARCHIVES:%=$(USERLAND_ARCHIVES)%)
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	@cd $(SOURCE_DIR); $(GIT) checkout $(GIT_TAG); \
	$(GIT) log -1 --format=%H > .downloaded

# I don't understand the hack but I manually verify the download
update-publish::

download:: $(SOURCE_DIR)/.downloaded

# opensmalltalk configure script checks for plugins files in builddir
COMPONENT_PRE_CONFIGURE_ACTION = ( cp plugins.ext plugins.int $(BUILD_DIR_64); cd $(SOURCE_DIR); ./scripts/updateSCCSVersions  )

# the default CFLAGS.gcc will be -m64 -O3 but this does not work for us
# we have to compile opensmalltalk with -g and we must not -O2or higher
CFLAGS=			-g -DNDEBUG -DDEBUGVM

CONFIGURE_SCRIPT= $(SOURCE_DIR)/platforms/unix/config/configure
CONFIGURE_OPTIONS +=	--with-vmversion=5.0
CONFIGURE_OPTIONS +=	--disable-dynamicopenssl
CONFIGURE_OPTIONS +=	--with-src=spurstack64src
CONFIGURE_OPTIONS +=	--disable-cogit
CONFIGURE_OPTIONS +=	--without-vm-display-fbdev
CONFIGURE_OPTIONS +=	--without-npsqueak

CONFIGURE_ENV +=	TARGET_ARCH="-m64"

# the opensmalltalk Makefile does not use DESTDIR
COMPONENT_INSTALL_ARGS=  	ROOT=$(PROTO_DIR)
COMPONENT_INSTALL_TARGETS= 	install-squeak install-doc install-plugins

REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += system/library/dbus

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxrender
