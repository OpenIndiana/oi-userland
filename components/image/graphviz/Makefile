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

# build 64-bit only
BUILD_BITS =	64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		graphviz
COMPONENT_VERSION =		2.50.0
COMPONENT_PROJECT_URL =		https://www.graphviz.org/
COMPONENT_CLASSIFICATION =	Applications/System Utilities
COMPONENT_LICENSE_FILE =	COPYING
COMPONENT_LICENSE =		EPL1.0
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH = \
    sha256:6b16bf990df114195be669773a1dae975dbbffada45e1de2849ddeb5851bb9a8
COMPONENT_ARCHIVE_URL = \
    https://gitlab.com/api/v4/projects/4207231/packages/generic/graphviz-releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

# explicit versions
PERL_VERSION =		5.34
PYTHON_VERSION =	3.9
RUBY_VERSION =		2.6

# preparation
COMPONENT_PREP_ACTION = (cd $(@D) && libtoolize -cf && \
				aclocal && \
				autoconf -f -I m4 && \
				autoheader && \
				automake --add-missing)

# configure
CONFIGURE_ENV +=	LIBPOSTFIX="/$(MACH64)"
# --with-javaincludedir allows for only one directory and we need two
CONFIGURE_ENV +=	JAVA_INCLUDES="-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/solaris"
CONFIGURE_ENV +=	PERL=$(PERL)
CONFIGURE_ENV +=	PYTHON=$(PYTHON)
CONFIGURE_ENV +=	RUBY=$(RUBY)
CONFIGURE_ENV +=	RUBY_VER=$(RUBY_VERSION)
CONFIGURE_OPTIONS +=	--disable-man-pdfs
CONFIGURE_OPTIONS +=	--disable-sharp
CONFIGURE_OPTIONS +=	--disable-go
CONFIGURE_OPTIONS +=	--disable-guile
CONFIGURE_OPTIONS +=	--disable-php
CONFIGURE_OPTIONS +=	--disable-python
CONFIGURE_OPTIONS +=	--enable-python3
CONFIGURE_OPTIONS +=	--disable-r
CONFIGURE_OPTIONS +=	--enable-lefty
CONFIGURE_OPTIONS +=	--without-included-ltdl
CONFIGURE_OPTIONS +=	--without-devil
CONFIGURE_OPTIONS +=	--without-visio
CONFIGURE_OPTIONS +=	--without-lasi
CONFIGURE_OPTIONS +=	--without-gtkgl
CONFIGURE_OPTIONS +=	--without-gtkglext
CONFIGURE_OPTIONS +=	--without-ann
CONFIGURE_OPTIONS +=	--without-qt
CONFIGURE_OPTIONS +=	--without-smyrna

# graphviz.7 -> graphviz.5
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTOUSRSHAREMAN5DIR) ; \
	$(MV) $(PROTOUSRSHAREMANDIR)/man7 $(PROTOUSRSHAREMAN5DIR) ; \
	$(MV) $(PROTOUSRSHAREMAN5DIR)/graphviz.7 \
	    $(PROTOUSRSHAREMAN5DIR)/graphviz.5 ;

# fix java, lua, ocaml, python, ruby man pages
COMPONENT_POST_INSTALL_ACTION += \
	cd $(PROTOUSRSHAREMAN3DIR) ; \
	for e in java lua ocaml python ruby ; do \
		for f in *.3$$e ; do \
			$(MV) $$f $${f%.3$$e}-$$e.3 ; \
		done ; \
	done ;

# fix tcl man pages
COMPONENT_POST_INSTALL_ACTION += \
	cd $(PROTOUSRSHAREMAN3DIR) ; \
	$(RM) -r ../man3tcl ; \
	$(MKDIR) ../man3tcl ; \
	for f in *.3tcl ; do \
		$(MV) $$f ../man3tcl ; \
		$(SYMLINK) ../man3tcl/$$f $${f%.3tcl}-tcl.3 ; \
	done ;

# python vendor-packages
COMPONENT_POST_INSTALL_ACTION += \
	cd $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) ; \
	$(RM) -r vendor-packages ; \
	$(MV) site-packages vendor-packages ;

# no usable tests available
TEST_TARGET = $(NO_TESTS)

# various build dependencies not detected automatically
REQUIRED_PACKAGES += developer/java/openjdk8
REQUIRED_PACKAGES += runtime/ocaml
REQUIRED_PACKAGES += runtime/tcl-8

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
#REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/math/gts
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += print/filter/ghostscript
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += runtime/ruby-26
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
