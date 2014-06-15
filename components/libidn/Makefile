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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):$(JAVA_HOME)/bin:/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		libidn
COMPONENT_VERSION=	1.19
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/libidn/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8ed2e936b1ae3e30b45b54ca3672deaa83ee0f4d20db5ad83dc1af7222d39f41
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/libidn/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libidn

COMPONENT_ARCHIVE_1 =   tld-0.7.tar.gz
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:7423f48d15fb1377ee0050c3e1f22e8a91668c2f158afed57b8ead3fed908785
COMPONENT_ARCHIVE_URL_1 = http://download.berlios.de/tldchk/$(COMPONENT_ARCHIVE_1)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0
LINT_FLAGS += -I$(PROTOUSRINCDIR)/idn

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_POSIX)
CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += -std=c99

GUNZIP = /usr/bin/gunzip
TAR = /usr/bin/tar
FIND = /usr/bin/find

CONFIGURE_ENV +=	INSTALL="$(INSTALL)"

CONFIGURE_OPTIONS  +=		--includedir=/usr/include/idn
CONFIGURE_OPTIONS  +=		--localstatedir=/var
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--disable-csharp
CONFIGURE_OPTIONS  +=		--disable-rpath
CONFIGURE_OPTIONS  +=		--disable-valgrind-tests
CONFIGURE_OPTIONS  +=		--enable-tld
CONFIGURE_OPTIONS  +=		--enable-nls
CONFIGURE_OPTIONS  +=		--disable-gtk-doc
CONFIGURE_OPTIONS  +=		--enable-java
CONFIGURE_OPTIONS  +=		--with-libiconv-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-libintl-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-html-dir=$(CONFIGURE_PREFIX)/share/doc
CONFIGURE_OPTIONS  +=		--with-pic

PROTOUSRSHAREDOCDIR = $(PROTOUSRSHAREDIR)/doc
IDNDOCDIR = $(PROTOUSRSHAREDOCDIR)/idn
HTMLDOCDIR = $(IDNDOCDIR)/html
HTMLDOCLIST = libidn-components.png libidn.html
DOCLIST = libidn-components.pdf libidn.pdf

ifeq ($(strip $(USERLAND_ARCHIVES)),)
  TLD_FILE=$(COMPONENT_DIR)/$(COMPONENT_ARCHIVE_1)
else 
  TLD_FILE=$(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1)
endif

# We must unpack the TLD database and touch the perl scripts in order
# to force re-generation of the TLD tables after augmenting them
COMPONENT_PRE_CONFIGURE_ACTION = \
	( cd $(SOURCE_DIR) ; \
	    $(TAR) zxf $(TLD_FILE); \
	    $(RM) java/libidn-1.19.jar ; \
	    $(RM) tld/no.tld tld/fr.tld ; \
	    $(CP) doc/tld/fr.tld tld/ ; \
	    $(CP) doc/tld/no.tld tld/ ; \
	    $(FIND) . -type d -exec chmod 0755 {} + ; \
	    $(FIND) ./tld -type f -name "*.tld" -exec chmod 0644 {} + ; \
	    $(FIND) ./tld -type f -name "*.tld" -exec touch -acm {} + ; \
	    $(FIND) ./tld/templates -type f -exec chmod 0644 {} + ; \
	    $(FIND) ./tld/templates -type f -exec touch -acm {} + ; \
	    $(FIND) ./lib -type f -name "*.pl" -exec touch -acm {} + ; \
	    $(FIND) ./lib -type f -name "*.pl" -exec chmod 0755 {} + )

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
	$(MKDIR) $(HTMLDOCDIR) ; \
	list1='$(HTMLDOCLIST)' ; for f in $$list1; do \
	    $(INSTALL) -m 0644 $(COMPONENT_DIR)/$(COMPONENT_SRC)/doc/$$f \
	    $(HTMLDOCDIR)/ ; \
	    done
	list2='$(DOCLIST)' ; for f in $$list2; do \
	      $(INSTALL) -m 0644 $(COMPONENT_DIR)/$(COMPONENT_SRC)/doc/$$f \
	      $(IDNDOCDIR)/ ; \
	      done
	$(CP) -Rp $(COMPONENT_DIR)/$(COMPONENT_SRC)/doc/java \
	    $(IDNDOCDIR)/ ; \
	$(CP) -Rp $(COMPONENT_DIR)/$(COMPONENT_SRC)/tld \
	    $(IDNDOCDIR)/
	$(CP) -Rp $(PROTOUSRSHAREDIR)/locale/en@boldquot \
	    $(PROTOUSRSHAREDIR)/locale/en

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

