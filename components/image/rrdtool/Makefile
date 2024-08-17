#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
# Copyright 2023 Friedrich Kink.  All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rrdtool
COMPONENT_VERSION=	1.9.0
COMPONENT_SUMMARY=	Data analysis tool generating graphical representations
COMPONENT_DESCRIPTION=	RRDtool is the OpenSource industry standard, high performance data \
			logging and graphing system for time series data. RRDtool can be \
			easily integrated in shell scripts, perl, python, ruby, lua or tcl \
			applications.
COMPONENT_SRC=		$(COMPONENT_NAME)-1.x-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	rrdtool-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE2=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:405f4ce365e2e37bdeff9bbb844cbedf9b36dde7344b31449e369315a3df5ef0
COMPONENT_ARCHIVE_URL=	https://github.com/oetiker/$(COMPONENT_NAME)-1.x/archive/refs/tags/$(COMPONENT_ARCHIVE2)
COMPONENT_PROJECT_URL=	https://oss.oetiker.ch/rrdtool/
COMPONENT_FMRI=		image/rrdtool
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	LICENSE

RUBY_VER= 3.2
RUBY_LIB_VER= 3.2

PATH= /usr/ruby/$(RUBY_VER)/bin:$(PATH.gnu)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= (cd $(@D) && ./bootstrap ) 

CONFIGURE_ENV +=		PYTHON=python$(PYTHON_VERSION)
CONFIGURE_ENV +=		PERL=$(PERL)
CONFIGURE_ENV +=		PERLCC=$(CC)

CONFIGURE_OPTIONS +=	--with-ruby-options="sitedir=/usr/ruby/$(RUBY_VER)/lib/ruby/$(RUBY_LIB_VER)/$(MACH64)-solaris$(SOLARIS_VERSION) libdir=/usr/ruby/$(RUBY_VER)/lib/$(MACH64)"
CONFIGURE_OPTIONS +=	--with-perl-options="CC=$(CC) LD=$(CC) LIB=/usr/perl5/$(PERL_VERSION)/lib"
CONFIGURE_OPTIONS += 	--enable-ruby
CONFIGURE_OPTIONS += 	--enable-tcl
CONFIGURE_OPTIONS += 	--enable-python
CONFIGURE_OPTIONS += 	--enable-static=no
CONFIGURE_OPTIONS +=	--without-systemdsystemunitdir

# Building the tests will fail without this
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Trying to convince configure to use vendor-packages instead of site-packages failed. So we do it manually.
# It is not necessary to run compileall as no sources are being moved in this action.
COMPONENT_POST_INSTALL_ACTION += \
    if [ -d $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION) ]; then \
        $(MKDIR) -p $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages && \
        $(MV) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/ && \
        $(RM) -fr $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages; \
    fi;

# Manually added build dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += runtime/ruby-32

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
