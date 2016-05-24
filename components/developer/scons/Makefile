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
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		scons
COMPONENT_VERSION=	2.4.1
COMPONENT_PROJECT_URL=	https://serf.apache.org/
COMPONENT_SUMMARY=	SConstruct, a software building tool
COMPONENT_SRC=		$(COMPONENT_NAME)-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b7e6c7c383b75f3cde4005a9f8d009305237c183f59427150c3cbdebd160baf9
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)-src/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=		developer/build/scons
COMPONENT_CLASSIFICATION=	Development/Distribution Tools
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CLEAN_PATHS+= $(BUILD_DIR)

# The package delivery should be fixed in 2.7 (matching dirs in globs
# as bad files and dying). Also, it is in SCons requirements ;)
PYTHON_VERSION = 2.7
PKG_MACROS += PYTHON_VERSION="$(PYTHON_VERSION)"
PKG_MACROS += PYTHON_LIB="$(PYTHON_LIB)"

# see the README.res for building and installation details
$(BUILD_DIR)/$(MACH32)/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	find $(@D) -name '*.sh' -exec $(CHMOD) +X '{}' \;
	find $(@D) -name '*.pyc' -exec $(RM) '{}' \;
	cd $(@D) && \
		$(PYTHON) -m compileall .
	cd $(@D) && \
		$(PYTHON) bootstrap.py build/scons
	$(TOUCH) $@

# Note: subdirs like "lib" and "bin" are hardcoded in scons, so we do not
# use common userland Makefile variables for them here
$(BUILD_DIR)/$(MACH32)/.installed:	$(BUILD_DIR)/$(MACH32)/.built
	$(RM) -r $(PROTO_DIR) || true
	$(MKDIR) $(PROTO_DIR)
	cd $(@D)/build/scons && \
		$(PYTHON) setup.py install \
			--root=$(PROTO_DIR) --prefix=$(USRDIR) \
			--no-version-script --standalone-lib
	cd $(PROTO_DIR)/$(USRDIR)/bin && \
		for F in scons sconsign scons-time ; do \
			sed -e 's,^#! */usr/bin/env python,#!$(PYTHON),' \
				< $$F > $$F.py \
			&& $(CAT) $$F.py > $$F \
			&& $(RM) $$F.py \
			|| exit; \
		done
	cd $(PROTO_DIR)/$(USRDIR) && if [ -d ./man -a ! -d ./share ]; then \
		$(MKDIR) share && $(MV) man share || exit ; \
	fi
	cd $(PROTO_DIR)/$(USRDIR)/lib && \
		if [ -d ./scons -a ! -d $(PROTO_DIR)/$(PYTHON_LIB) ]; then \
			$(MKDIR) "`dirname "$(PROTO_DIR)/$(PYTHON_LIB)"`" && \
				$(MV) scons "$(PROTO_DIR)/$(PYTHON_LIB)" || exit ; \
		fi
	$(TOUCH) $@

build:  	$(BUILD_DIR)/$(MACH32)/.built Makefile

install:	$(BUILD_DIR)/$(MACH32)/.installed Makefile

test:   	$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
