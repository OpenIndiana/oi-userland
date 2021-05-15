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
# Copyright 2017 Alexander Pyhalov
# Copyright 2018 Michal Nowak
# Copyright 2021 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

BUILD_BITS= 64
BUILD_STYLE= justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	mongodb
COMPONENT_MAJOR_VERSION= 4.4
COMPONENT_MINOR_VERSION= 6
COMPONENT_VERSION= $(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_SUMMARY= MongoDB distributed document-oriented database
COMPONENT_PROJECT_URL=	https://www.mongodb.com/
COMPONENT_FMRI=	database/mongodb-44
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_SRC=		$(COMPONENT_NAME)-src-r$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://fastdl.mongodb.org/src/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:b5189aa87977137574cd75432dac9bb91699d322358f857b7b6d1e191fbd2f32
COMPONENT_LICENSE= SSPL
COMPONENT_LICENSE_FILE=	LICENSE-Community.txt

include $(WS_MAKE_RULES)/common.mk

BUILD_DIR_TOOLS= $(BUILD_DIR)/tools
BUILD_TOOLS= $(BUILD_DIR_TOOLS)/.built
INSTALL_TOOLS= $(BUILD_DIR_TOOLS)/.installed

MONGO_PREFIX=$(USRDIR)/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)

PYTHON_VERSION= 3.9
GCC_VERSION= 10
GMAKE= scons VERBOSE=1 
CORES= $(shell psrinfo -t)
GOROOT= $(shell go env | grep GOROOT | awk -F= '{ print $$2 }' | tr -d '"')

ENV= /usr/bin/env -i

COMPONENT_BUILD_ARGS += DESTDIR=$(PROTO_DIR)
COMPONENT_BUILD_ARGS += PREFIX=$(MONGO_PREFIX)
COMPONENT_BUILD_ARGS += TARGET_ARCH=x86_64
COMPONENT_BUILD_ARGS += CC="$(CC) -DSOLARIS"
COMPONENT_BUILD_ARGS += CXX="$(CXX) -DSOLARIS"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += CXXFLAGS="$(CXXFLAGS) -fpermissive"
COMPONENT_BUILD_ARGS += LIBPATH=/usr/lib/$(MACH64)
COMPONENT_BUILD_ARGS += LINKFLAGS="$(LDFLAGS) -lkstat"
COMPONENT_BUILD_ARGS += AR=/usr/bin/gar
COMPONENT_BUILD_ARGS += CCFLAGS=-I/usr/include/pcre 
COMPONENT_BUILD_ARGS += --js-engine=mozjs
COMPONENT_BUILD_ARGS += --use-system-pcre
COMPONENT_BUILD_ARGS += --use-system-zlib
COMPONENT_BUILD_ARGS += --server-js=on
COMPONENT_BUILD_ARGS += --ssl
COMPONENT_BUILD_ARGS += --release
COMPONENT_BUILD_ARGS += --disable-ggdb
COMPONENT_BUILD_ARGS += --disable-warnings-as-errors
COMPONENT_BUILD_ARGS += -j $(CORES)

COMPONENT_INSTALL_ARGS = $(COMPONENT_BUILD_ARGS)

COMPONENT_BUILD_TARGETS= install-core	

# just a dummy for scons
COMPONENT_INSTALL_TARGETS= --version

TEST_SUITES += core
TEST_SUITES += dbtest
TEST_SUITES += dur_jscore_passthrough
TEST_SUITES += jstestfuzz
TEST_SUITES += jstestfuzz_replication
TEST_SUITES += jstestfuzz_sharded
TEST_SUITES += replica_sets_jscore_passthrough
TEST_SUITES += unittests

# patches must be done before cloney
COMPONENT_PREP_ACTION += \
	$(CP) -r $(COMPONENT_DIR)/files/mozjs-60/solaris  $(SOURCE_DIR)/src/third_party/mozjs-60/platform/x86_64/; \
	cd $(SOURCE_DIR)/src/third_party/mozjs-60/extract; \
	$(GPATCH) $(GPATCH_FLAGS) < $(COMPONENT_DIR)/files/0-gc-memory.patch; \
	$(GPATCH) $(GPATCH_FLAGS) < $(COMPONENT_DIR)/files/0-old-configure.patch; \
	$(GPATCH) $(GPATCH_FLAGS) < $(COMPONENT_DIR)/files/0-wasm-WasmSignalHandlers.patch; 

COMPONENT_PRE_BUILD_ACTION += \
 ($(PYTHON) -m pip install -r $(@D)/etc/pip/compile-requirements.txt) 

$(BUILD_TOOLS):	$(BUILD_64)
	($(MKDIR) $(BUILD_DIR_TOOLS)/src/github.com/mongodb; \
	cd $(BUILD_DIR_TOOLS)/src/github.com/mongodb; \
	git clone https://github.com/mongodb/mongo-tools; \
	cd mongo-tools; \
	git checkout 100.3.1; \
	$(GPATCH) $(GPATCH_FLAGS) < $(COMPONENT_DIR)/files/13-mongotools.patch; \
	GOROOT=$(GOROOT) ./make build)
	$(TOUCH) $(@)

$(INSTALL_TOOLS): $(BUILD_TOOLS) $(INSTALL_64)
	$(MKDIR) $(PROTO_DIR)$(MONGO_PREFIX)/bin
	$(CP) $(BUILD_DIR_TOOLS)/src/github.com/mongodb/mongo-tools/bin/* $(PROTO_DIR)$(MONGO_PREFIX)/bin
	$(TOUCH) $(@)

# A bit of magic to replace spaces with commas
comma:= ,
empty:=
space:= $(empty) $(empty)

COMPONENT_TEST_CMD = $(PYTHON) buildscripts/resmoke.py \
			--continueOnFailure \
			--dbpathPrefix=/tmp/db \
			--suites=$(subst $(space),$(comma),$(TEST_SUITES))

COMPONENT_TEST_TARGETS =

COMPONENT_TEST_TRANSFORMS +=    '-e "s/\[resmoke\][ -+0-9T:\.\-]*//"' \
                                '-e "s/\s\s*[0-9][0-9]*\.[0-9][0-9]* seconds/ SEC seconds/"' \
                                '-n ' \
                                '-e "/Summary of all suites/,\\$$p"'

# Not strictly necessary
$(TEST_64):     $(INSTALL_64) $(INSTALL_TOOLS)

build:		$(BUILD_64) $(BUILD_TOOLS)

install: $(INSTALL_TOOLS)
	$(MKDIR) $(PROTO_DIR)$(MONGO_PREFIX)/man/man1
	$(CP) $(BUILD_DIR_64)/debian/*.1  $(PROTO_DIR)$(MONGO_PREFIX)/man/man1/
	$(CP) $(BUILD_DIR_64)/debian/mongo{,d,s,ldap,kerberos}.1  $(PROTO_DIR)$(MONGO_PREFIX)/man/man1/

test:		$(TEST_64)

# Test requirements
REQUIRED_PACKAGES += library/python/urllib3-39

# Build dependencies
REQUIRED_PACKAGES += developer/gcc-10
REQUIRED_PACKAGES += developer/build/scons
REQUIRED_PACKAGES += developer/golang
REQUIRED_PACKAGES += library/python/psutil
REQUIRED_PACKAGES += library/python/typing

# Auto-generated dependencies via `gmake GMAKE=gmake REQUIRED_PACKAGES`
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
