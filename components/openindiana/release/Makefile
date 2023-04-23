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
# Copyright 2016-2017 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           release
COMPONENT_VERSION=        0.$(PKG_SOLARIS_VERSION)	
COMPONENT_REVISION=       16
COMPONENT_SUMMARY=        OpenIndiana Release Files 
COMPONENT_PROJECT_URL=    https://www.openindiana.org/
COMPONENT_FMRI=           release
COMPONENT_CLASSIFICATION= System/Core
COMPONENT_LICENSE=        CDDLv1.0
COMPONENT_LICENSE_FILE=   $(COMPONENT_NAME).license	

include $(WS_MAKE_RULES)/ips.mk

RELEASE_DATE=$(shell LC_ALL=C date +'%d %B %Y')

download:

prep:

build:

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)
	mkdir -p $(PROTO_DIR)$(ETCDIR) && \
	cat files/release | \
		sed -e 's|\%\%DATE\%\%|$(RELEASE_DATE)|' \
		    -e 's|\%\%DISTRIBUTION_NAME\%\%|$(DISTRIBUTION_NAME)|' \
		    -e 's|\%\%DISTRIBUTION_VERSION\%\%|$(DISTRIBUTION_VERSION)|' > $(PROTO_DIR)$(ETCDIR)/release

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

