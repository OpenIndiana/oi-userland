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
# Copyright 2017 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved. 
#

include ../../../make-rules/shared-macros.mk

PATH= $(USRBINDIR64):$(PATH.illumos)

COMPONENT_NAME=           couchdb
COMPONENT_VERSION=        2.1.1
COMPONENT_VERSION_MAJOR=  2.1
COMPONENT_FMRI=           database/$(COMPONENT_NAME)-21
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_PROJECT_URL=    http://couchdb.apache.org/
COMPONENT_SRC=            apache-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=   sha256:d5f255abc871ac44f30517e68c7b30d1503ec0f6453267d641e00452c04e7bcc
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=    http://apache.mirror.iphh.net/$(COMPONENT_NAME)/source/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=        Apache CouchDB is a document-oriented database.
COMPONENT_LICENSE=        Apache 2.0
COMPONENT_LICENSE_FILE=   $(USRDIR)/couchdb/$(COMPONENT_VERSION_MAJOR)/LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_MACROS += COMPONENT_VERSION_MAJOR=$(COMPONENT_VERSION_MAJOR)

# fix build on jenkins
COMPONENT_BUILD_ENV += HOME=/tmp
COMPONENT_INSTALL_ENV += HOME=/tmp
COMPONENT_TEST_ENV += HOME=/tmp

CFLAGS += $(gcc_C99_ENABLE) -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS 
CXXFLAGE += $(gcc_C99_ENABLE) -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS

ENV += CC="$(CC)" CXX="$(CXX)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT= $(@D)/configure

COMPONENT_PREP_ACTION = ( \
	$(CP) $(COMPONENT_DIR)/files/Makefile.openindiana $(@D); \
	$(CP) $(COMPONENT_DIR)/files/default.ini $(@D); )

CONFIGURE_OPTIONS = --user $(COMPONENT_NAME)
CONFIGURE_OPTIONS = --with-curl

COMPONENT_BUILD_ENV += --docdir="$(USRSHAREDOCDIR)"

#
# This is a mixed 64bit and 32bit installation.
# All binary applications are built as 64bit but not couchjs.
# With patch 01-rebarconfigscript.patch couchjs is forced to be built as 32bit and
# link against /usr/lib/libmozjs185.so (Spidermonkey).
# Spidermonkey is 32bit only.
# CouchDB uses couchjs as external process over STDOUT/STDIN/STDERR.
#

COMPONENT_INSTALL_ARGS += COMPONENT_DIR=$(USRDIR)/$(COMPONENT_NAME)/$(COMPONENT_VERSION) V=1

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
      DOCDIR=$(USRSHAREDOCDIR)/couchdb/$(COMPONENT_VERSION_MAJOR) \
      ETCDIR=$(ETCDIR)/couchdb/$(COMPONENT_VERSION_MAJOR) \
      RELDIR=$(USRDIR)/couchdb/$(COMPONENT_VERSION_MAJOR)

COMPONENT_TEST_ENV += http_proxy= https_proxy=
COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = /OK/

build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(TEST_64)

# Build dependencies
REQUIRED_PACKAGES += runtime/erlang
REQUIRED_PACKAGES += developer/icu

# only required for target test
# this modules are in the repository
# REQUIRED_PACKAGES += library/python/nose-27
# REQUIRED_PACKAGES += library/python/requests-27
# and install this via pip
# pip install hypothesis

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/spidermonkey
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
