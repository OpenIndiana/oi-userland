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
# Copyright 2019 Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gsoap
COMPONENT_VERSION=	2.8.83
COMPONENT_SUMMARY=	Toolkit for SOAP/REST-based C/C++ server and client web service applications
COMPONENT_PROJECT_URL=	https://www.genivia.com/products.html
COMPONENT_FMRI=		library/gsoap
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-2.8
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/gsoap2/gsoap-2.8/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:879ab40d40e379add9d3526c0592f891eaea16f7487be160157dbc40216e1633
COMPONENT_LICENSE=	GPLv2+ with exceptions
COMPONENT_LICENSE_FILE=	gsoap.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Some samples need extra libraries, which are not autodetected
LDFLAGS += -lsocket -lxnet -lnsl

# gsoap zip file contain a lot of enexpected files (binaries, non-GPL-licensed
# files, etc), files we don't want, don't need, or perhaps can't even ship.
#
# What follows is a list of files to be removed according to Fedora gsoap.spec
# (openSUSE does a simmilar thing):
#
# * XML files non-executable
# * Documentation fonts non-executable
# * we want all txt files to have unix end-of-line encoding
# * remove stuff with gsoap license only - not GPL
# * remove pre-compiled binaries
# * Remove .DS_Store files
COMPONENT_PRE_CONFIGURE_ACTION += \
	cd $(SOURCE_DIR) ; \
	find gsoap/samples/autotest/databinding/examples -name '*.xml' -exec chmod a-x {} ';' ; \
	chmod a-x gsoap/doc/fonts/* ; \
	for txt in `find . -name '*.txt'`; do \
		dos2unix $$txt $$txt ; \
	done ; \
	rm -rf gsoap/extras gsoap/mod_gsoap gsoap/Symbian ; \
	sed 's!$$(top_srcdir)/gsoap/extras/\*!!' -i gsoap/Makefile.am ; \
	rm -rf gsoap/bin rm gsoap/samples/calc_vs2005/calc_vs2005/soapcpp2.exe \
		gsoap/samples/rest/person gsoap/samples/wcf/Basic/TransportSecurity/calculator \
		rm gsoap/VisualStudio2005/wsdl2h/wsdl2h/soapcpp2.exe ; \
	find . -name .DS_Store -exec rm {} ';' ; \
	autoreconf --install --force ; \
	cp -a $(SOURCE_DIR)/* $(@D) ;

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS +=	--enable-ipv6
# Build and runs tests
CONFIGURE_OPTIONS +=	--enable-samples

# Parallel build fails. We either disable it, or build soapcpp2_yacc.c first.
# We opt for the former.
COMPONENT_BUILD_ARGS=

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# dos2unix
REQUIRED_PACKAGES += system/extended-system-utilities
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
