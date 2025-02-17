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
# Copyright 2015 Alexander Pyhalov
#

BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         rtmpdump
COMPONENT_VERSION=      2.6
COMPONENT_SUMMARY=      RTMPdump -- a toolkit for RTMP streams
COMPONENT_SRC=          $(COMPONENT_NAME)
COMPONENT_PROJECT_URL=  http://rtmpdump.mplayerhq.hu/
COMPONENT_LICENSE=      GPLv2,LGPLv2
COMPONENT_LICENSE_FILE= rtmpdump.license
COMPONENT_CLASSIFICATION=Applications/Sound and Video
COMPONENT_FMRI=         video/rtmpdump

GIT_REPO=https://git.ffmpeg.org/rtmpdump
GIT_BRANCH=master
# mtekla identified that GIT_COMMIT_ID should be used to specify cloning
# the git repo by a specific commmit number, as per discussion in
# https://github.com/OpenIndiana/oi-userland/pull/20822
# Not certain if this commit ID is being used since gmake download shows this:
#  * branch            HEAD       -> FETCH_HEAD
GIT_COMMIT_ID=6f6bb1353fc84f4cc37138baa99f586750028a01

COMPONENT_PREP_GIT=no

include $(WS_MAKE_RULES)/encumbered.mk

# copied from sysding Makefile:
# The ugly hack with update-publish target is necessary to update
# source from git repository on each "gmake publish".
# publish: target should appear before inclusion of ips.mk/common.mk
publish: update-publish

include $(WS_MAKE_RULES)/common.mk

COMPONENT_ENV += CC="$(CC)"
COMPONENT_ENV += XCFLAGS="$(CFLAGS) -I$(OPENSSL_INCDIR)"
COMPONENT_ENV += XLDFLAGS="$(LDFLAGS) -L$(OPENSSL_LIBDIR) -R$(OPENSSL_LIBDIR)"
COMPONENT_ENV += XLIBS="-lnsl -lsocket"

COMPONENT_BUILD_ENV += $(COMPONENT_ENV)

COMPONENT_INSTALL_ENV.64 = ARCH=/$(MACH64)
COMPONENT_INSTALL_ENV += $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV += $(COMPONENT_INSTALL_ENV.$(BITS))

# download source from git and then build it using method found in sysding Makefile recipe
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

build: $(BUILD_64)

install: $(INSTALL_64)

download:: $(SOURCE_DIR)/.downloaded

# Erase source code during gmake clean.   Fixes error if patches tried to get reapplied during gmake build .
clean::
	$(RM) -rf rtmpdump

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
