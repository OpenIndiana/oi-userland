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
# Copyright (c) 2012-2013, Igor Kozhukhov <ikozhukhov@gmail.com>. All rights reserved.
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2026 Klaus Ziegler
#

BUILD_BITS=		64_and_32
USE_PARALLEL_BUILD=	yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         trousers
COMPONENT_VERSION=      0.3.15
COMPONENT_SUMMARY=	TrouSerS TCG software to access a TPM device
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=  https://sourceforge.net/projects/trousers/
COMPONENT_ARCHIVE_HASH= \
	sha256:1e5be93e518372acf1d92d2f567d01a46fdb0b730487e544e6fb896c59cac77f
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)files/trousers/0.3.15/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/security/trousers
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE=	LICENSE

COMPONENT_FMRI.$(COMPONENT_NAME)-32 =		$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.$(COMPONENT_NAME)-32 =	$(COMPONENT_SUMMARY) (32-bit)

PATCH_LEVEL=	0
DROP_STATIC_LIBRARIES = yes

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

LIBS = -lnsl -lsocket -lgen -lscf -lbsm -lresolv
CFLAGS += -DSOLARIS -DBI_OPENSSL -D_REENTRANT -D_POSIX_PTHREAD_SEMANTICS
CFLAGS += -Wno-implicit-function-declaration -Wno-incompatible-pointer-types

LDFLAGS += $(CC_BITS)

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

# trousers does not detect openssl-3 by default so force it.
CPPFLAGS += -I$(OPENSSL_INCDIR)
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
LDFLAGS += -L$(OPENSSL_LIBDIR)

# deliver tcsd in /usr/lib*
CONFIGURE_SBINDIR.32 = $(CONFIGURE_LIBDIR.32)
CONFIGURE_SBINDIR.64 = $(CONFIGURE_LIBDIR.64)

COMPONENT_PREP_ACTION= ( cd $(@D); PATH="$(PATH)" autoreconf -vif )

CONFIGURE_OPTIONS += --with-gui=openssl
CONFIGURE_OPTIONS += LD="$(CC)"
CONFIGURE_OPTIONS += LIBS="$(LIBS)"

COMPONENT_POST_CONFIGURE_ACTION = (cd $(COMPONENT_SRC); \
	for f in `ls src/include/tss/*.h` ; do \
		/usr/bin/dos2unix $$f $$f; \
	done; \
	for f in `ls src/include/trousers/*.h` ; do \
		/usr/bin/dos2unix $$f $$f; \
	done; \
	for f in `ls src/include/*.h` ; do \
		/usr/bin/dos2unix $$f $$f; \
	done;)

# Drop files installed for the 32-bit build that overlaps with files installed
# for the 64-bit build.
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOETCDIR) ;
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRINCDIR) ;
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRSHAREMANDIR) ;

# Install additional files
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(INSTALL) -D $(SOURCE_DIR)/dist/system.data.auth $(PROTOVARDIR)/tpm/system/system.data.auth ; \
	$(INSTALL) -D $(SOURCE_DIR)/dist/system.data.noauth $(PROTOVARDIR)/tpm/system/system.data.noauth ; \
	$(SYMLINK) system.data.auth $(PROTOVARDIR)/tpm/system/system.data ; \
	$(INSTALL) -D $(COMPONENT_DIR)/files/auth_attr $(PROTOETCSECDIR)/auth_attr.d/trousers ; \
	$(INSTALL) -D $(COMPONENT_DIR)/files/prof_attr $(PROTOETCSECDIR)/prof_attr.d/trousers ; \
	$(INSTALL) -D $(COMPONENT_DIR)/files/tcsd.xml $(PROTOLIBDIR)/svc/manifest/application/security/tcsd.xml ; \
	$(INSTALL) -D $(COMPONENT_DIR)/files/tcsd.sh $(PROTOLIBDIR)/svc/method/tcsd.sh ;

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)/32
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/iconv/utf-8
