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
# Copyright 2021 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved. 
#

BUILD_BITS= 64
BUILD_STYLE= justmake

include ../../../make-rules/shared-macros.mk

GCC_VERSION= 10
PATH= $(PATH.gnu)

COMPONENT_NAME=           couchdb
COMPONENT_VERSION=        3.1.1
COMPONENT_VERSION_MAJOR=  3.1
COMPONENT_FMRI=           database/$(COMPONENT_NAME)-31
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_PROJECT_URL=    http://couchdb.apache.org/
COMPONENT_SRC=            apache-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=   sha256:8ffe766bba2ba39a7b49689a0732afacf69caffdf8e2d95447e82fb173c78ca3
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=    http://apache.mirror.iphh.net/$(COMPONENT_NAME)/source/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=        Apache CouchDB is a document-oriented database.
COMPONENT_LICENSE=        Apache 2.0
COMPONENT_LICENSE_FILE=   $(USRDIR)/couchdb/$(COMPONENT_VERSION_MAJOR)/LICENSE

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += COMPONENT_VERSION_MAJOR=$(COMPONENT_VERSION_MAJOR)

# fix build on jenkins
COMPONENT_BUILD_ENV += HOME=/tmp
COMPONENT_INSTALL_ENV += HOME=/tmp
COMPONENT_TEST_ENV += HOME=/tmp

CFLAGS += $(gcc_C99_ENABLE) -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS -lm
CXXFLAGE += $(gcc_C99_ENABLE) -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS -lm

ENV += CC="$(CC)" CXX="$(CXX)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"

# we use the configure in the prep action
# if not configure ignores all arguments and falls back to the defaults
CONFIGURE_OPTIONS += --user $(COMPONENT_NAME)
CONFIGURE_OPTIONS += --with-curl
CONFIGURE_OPTIONS += --spidermonkey-version 60

COMPONENT_PREP_ACTION = ( \
	$(RM) $(SOURCE_DIR)/bin/rebar; \
	cd $(SOURCE_DIR); \
	./configure $(CONFIGURE_OPTIONS); \
	$(CP) $(COMPONENT_DIR)/files/Makefile.openindiana $(@D); \
	$(CP) $(COMPONENT_DIR)/files/local.ini $(@D); )

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_INSTALL_TARGETS = release

# The project doesn't have an install section but let the user copy the folder rel/couchdb.
# Here we prepare manually the image in the prototype folder with a makefile.
COMPONENT_POST_INSTALL_ACTION= \
   cd $(@D); \
	 $(RM) -r $(PROTO_DIR); \
   $(GMAKE) -f Makefile.openindiana \
      DESTDIR=$(PROTO_DIR) \
      MANDIR=$(USRSHAREMANDIR) \
      BINDIR=$(USRBINDIR) \
      DOCDIR=$(USRSHAREDOCDIR) \
      ETCDIR=$(ETCDIR) \
      USRDIR=$(USRDIR) \
      COMPONENT_VERSION_FOLDER=/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)

COMPONENT_TEST_ENV += http_proxy= https_proxy=
COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = /OK/

# Build dependencies
REQUIRED_PACKAGES += developer/icu

# only required for target test
# this modules are in the repository
REQUIRED_PACKAGES += library/python/nose-27
REQUIRED_PACKAGES += library/python/requests-27
# and install this via pip
# pip install hypothesis

# manually added build time
REQUIRED_PACKAGES += developer/gcc-10

# manually added not found by REQUIRED_PACKAGES
REQUIRED_PACKAGES += runtime/erlang

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/mozjs-60
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
