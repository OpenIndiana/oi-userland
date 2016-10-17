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
# Copyright 2016, Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     oi-docs
COMPONENT_FMRI=     release/openindiana-docs
COMPONENT_SUMMARY=  OpenIndiana Docs - Online Documentation
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Documentation
COMPONENT_PROJECT_URL= https://github.com/OpenIndiana/oi-docs
COMPONENT_ARCHIVE_URL= https://github.com/OpenIndiana/oi-docs
COMPONENT_SRC=      $(COMPONENT_NAME)
COMPONENT_LICENSE= PDL

GIT_REPO=git://github.com/OpenIndiana/oi-docs.git
GIT_BRANCH=master
GIT_CHANGESET=HEAD

include prep-git.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_REVISION= $(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)
COMPONENT_VERSION=  $(BRANCHID)

OI_DOCS_DIR= $(USRSHAREDOCDIR)/openindiana-docs

OI_DOCS_CLEAN_FILES = __init__.py
OI_DOCS_CLEAN_FILES+= __init__.pyc

COMPONENT_PREP_ACTION= \
    $(GSED) -i -e 's/^use_directory_urls[[:space:]]*:.*$$/use_directory_urls: false/' $(SOURCE_DIR)/mkdocs.yml; \
    $(GSED) -i -e 's/^theme[[:space:]]*:.*$$/theme: yeti/' $(SOURCE_DIR)/mkdocs.yml; \
	  $(CP) $(COMPONENT_DIR)/files/openindiana-docs.desktop $(SOURCE_DIR)

COMPONENT_BUILD_ACTION= \
    cd $(@D) && mkdocs build --clean -f $(SOURCE_DIR)/mkdocs.yml

COMPONENT_PRE_INSTALL_ACTION= \
    cd $(@D)/site && $(RM) $(OI_DOCS_CLEAN_FILES)

COMPONENT_INSTALL_ACTION= \
    $(RM) -r $(PROTO_DIR)$(OI_DOCS_DIR)/*; \
    $(MKDIR) $(PROTO_DIR)$(OI_DOCS_DIR); \
    $(MKDIR) $(PROTO_DIR)/usr/share/applications; \
    cd $(@D) && \
    $(CP) -r site/* $(PROTO_DIR)$(OI_DOCS_DIR) && \
    $(CP) openindiana-docs.desktop $(PROTO_DIR)/usr/share/applications;

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

$(PRE_PUBLISH_STAMP): $(GENERATED).p5m
	$(CP) $(GENERATED).p5m $(COMPONENT_NAME).p5m
	
publish: update pre-publish $(PUBLISH_STAMP)
