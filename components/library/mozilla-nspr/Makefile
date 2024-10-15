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
# Copyright 2011, Andrzej Szeszo
# Copyright 2013, Jon Tibble
# Copyright 2019, Michal Nowak
# Copyright 2022, Andreas Wacknitz
#

BUILD_BITS=			64_and_32
DROP_STATIC_LIBRARIES = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         nspr
COMPONENT_VERSION=      4.35
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Netscape Portable Runtime
COMPONENT_PROJECT_URL=  https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSPR
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7ea3297ea5969b5d25a5dd8d47f2443cda88e9ee746301f6e1e1426f8a6abc8f
COMPONENT_ARCHIVE_URL=	https://ftp.mozilla.org/pub/nspr/releases/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/System
COMPONENT_LICENSE=		MPL-2.0
COMPONENT_LICENSE_FILE=		nspr/LICENSE

COMPONENT_FMRI.nspr-32 =		$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.nspr-32 =		$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_SCRIPT = $(SOURCE_DIR)/nspr/configure

CONFIGURE_LIBDIR.32 = /usr/lib/mps
CONFIGURE_LIBDIR.64 = /usr/lib/mps/$(MACH64)
CONFIGURE_LIBSECDIR.32 = /usr/lib/mps/secv1
CONFIGURE_LIBSECDIR.64 = /usr/lib/mps/secv1/$(MACH64)

CONFIGURE_OPTIONS.64 += --enable-64bit

CONFIGURE_OPTIONS +=	--includedir=/usr/include/mps

# Generate the nspr-config(1) man page
COMPONENT_POST_BUILD_ACTION.64 += \
	$(GSED) -e 's/@version@/$(COMPONENT_VERSION)/' $(COMPONENT_DIR)/files/nspr-config.xml > $(BUILD_DIR_$(BITS))/nspr-config.xml ; \
	/usr/bin/xmlto -o $(BUILD_DIR_$(BITS)) man $(BUILD_DIR_$(BITS))/nspr-config.xml ;

# Install the nspr-config(1) man page
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(INSTALL) -D $(BUILD_DIR_$(BITS))/nspr-config.1 $(PROTOUSRSHAREMAN1DIR)/nspr-config.1 ;

# Fix RPATH/RUNPATH in libraries
COMPONENT_POST_INSTALL_ACTION += \
	for i in $(PROTO_DIR)$(CONFIGURE_LIBDIR.$(BITS))/*.so ; do \
		$(ELFEDIT) -e 'dyn:value -s RPATH "$(CONFIGURE_LIBDIR.$(BITS))"' $$i ; \
		$(ELFEDIT) -e 'dyn:value -s RUNPATH "$(CONFIGURE_LIBDIR.$(BITS))"' $$i ; \
	done ;

# Create compatibility symlinks for libraries
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(SYMLINK) $(MACH64) $(PROTO_DIR)$(CONFIGURE_LIBDIR.$(BITS))/../64 ; \
	$(INSTALL) -d $(PROTO_DIR)$(CONFIGURE_LIBSECDIR.$(BITS)) ; \
	$(SYMLINK) $(MACH64) $(PROTO_DIR)$(CONFIGURE_LIBSECDIR.$(BITS))/../64 ;
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTO_DIR)$(CONFIGURE_LIBSECDIR.$(BITS)) ; \
	( cd $(PROTO_DIR)$(CONFIGURE_LIBDIR.$(BITS)) ; \
	D=$(if $(filter 64,$(BITS)),../$(MACH64)/) ; \
	for f in *.so ; do \
		$(SYMLINK) ../$$D$$f $(PROTO_DIR)$(CONFIGURE_LIBSECDIR.$(BITS))/$$f ; \
	done ) ;

# Move the pkg-config file to our preferred location
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTOUSRLIBDIR.$(BITS))/pkgconfig ; \
	$(MV) $(PROTO_DIR)$(CONFIGURE_LIBDIR.$(BITS))/pkgconfig/nspr.pc $(PROTOUSRLIBDIR.$(BITS))/pkgconfig ;

# Drop binaries we do not want to distribute
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTO_DIR)$(CONFIGURE_BINDIR.$(BITS))/compile-et.pl ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTO_DIR)$(CONFIGURE_BINDIR.$(BITS))/prerr.properties ;

# Drop include files installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRINCDIR) ;
# Drop the aclocal file installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) $(PROTOUSRSHAREDIR)/aclocal/nspr.m4 ;

# Test suite is just this script
COMPONENT_TEST_CMD=	$(PERL) $(SOURCE_DIR)/nspr/pr/tests/runtests.pl
COMPONENT_TEST_ENV_CMD=
COMPONENT_TEST_ARGS=
COMPONENT_TEST_TARGETS=
COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/Passed/p" ' \

# Build dependencies
REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
