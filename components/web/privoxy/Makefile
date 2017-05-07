#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		privoxy
COMPONENT_VERSION=	3.0.26
COMPONENT_SUMMARY=	Privacy-enhancing, ad-removing web proxy
COMPONENT_DESCRIPTION=	Privoxy is a non-caching web proxy with advanced\
 filtering capabilities for enhancing privacy, modifying web page data\
 and HTTP headers, controlling access, and removing ads and other obnoxious\
 Internet junk
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-stable
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_PROJECT_URL=	http://www.privoxy.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:57e415b43ee5dfdca74685cc034053eaae962952fdabd086171551a86abf9cd8
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/ijbswa/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	web/proxy/privoxy
COMPONENT_CLASSIFICATION=	Web Services/Application and Web Servers
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
        (cd $(@D) ; \
            autoheader; \
            autoconf )

# Needed to installed most of the files into the proto area.
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)
	$(CP) $(BUILD_DIR_32)/templates/* $(PROTOETCDIR)/templates

# Regression tests exist for privoxy in tools/privoxy-regression-test.pl,
# however these are not applicable to us since they violate the company policy
# of not allowing third-party programs to communicate outside the company.
#
# To test privoxy, follow the instructions in the privoxy quick start guide:
# http://www.privoxy.org/user-manual/quickstart.html
# 
# Privoxy is disabled by default, so make sure to enable it if necessary:
# 	# svcs privoxy
#	# svcadm enable privoxy
# You may need to set the forward address in /etc/privoxy/config to the 
# Oracle proxy to access pages in your web browser with privoxy running. 

test: 		$(NO_TESTS)

REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
