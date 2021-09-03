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
# Copyright 2021 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           py3c
COMPONENT_VERSION=        1.3
COMPONENT_PROJECT_URL=    https://pypi.org/project/py3c/#files
COMPONENT_FMRI=           library/python/py3c
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_LICENSE=        MIT

GIT=git
GIT_REPO=https://github.com/encukou/py3c.git
GIT_BRANCH=master
GIT_CHANGESET=HEAD

COMPONENT_PREP_GIT=no
include $(WS_MAKE_RULES)/ips.mk

SOURCE_DIR= $(COMPONENT_NAME)
CLOBBER_PATHS= $(COMPONENT_NAME)
PYTHON= python3.9

$(SOURCE_DIR)/.downloaded: $(ARCHIVES:%=$(USERLAND_ARCHIVES)%)
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone $(GIT_REPO)
	@cd $(SOURCE_DIR); $(GIT) checkout $(GIT_BRANCH); $(GIT) pull \
	  $(GIT_REPO); $(GIT) log -1 --format=%H > .downloaded

download:: $(SOURCE_DIR)/.downloaded

prep: $(SOURCE_DIR)/.downloaded

build: prep install

install: prep
	mkdir -p $(PROTO_DIR)
	mkdir -p $(PROTO_DIR)$(USRINCDIR)/$(PYTHON)/py3c && \
	mkdir -p $(PROTO_DIR)$(USRLIBDIR64)/pkgconfig && \
	cp -p $(SOURCE_DIR)/include/py3c.h $(PROTO_DIR)$(USRINCDIR)/$(PYTHON) && \
	cp -rp $(SOURCE_DIR)/include/py3c/* $(PROTO_DIR)$(USRINCDIR)/$(PYTHON)/py3c && \
	sed \
		-e "/^# Template/d" \
		-e "/^# Requires/d" \
		-e 's#@includedir@#/usr/include/python3.9#g' \
		-e "s@^#Requires: python3@Requires: python-3.9@g" \
		-e "/^#Requires/d" $(SOURCE_DIR)/py3c.pc.in > \
	$(PROTO_DIR)$(USRLIBDIR64)/pkgconfig/py3c.pc

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

clobber::	clean
	$(RM) -r $(CLOBBER_PATHS)
