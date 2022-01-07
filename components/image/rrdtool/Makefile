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
# Copyright 2022 Friedrich Kink.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rrdtool

COMPONENT_VERSION=	1.7.2
COMPONENT_FMRI=		image/rrdtool
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SUMMARY=	Data analysis tool generating graphical representations
COMPONENT_DESCRIPTION=	RRDtool is the OpenSource industry standard, high performance data \
			logging and graphing system for time series data. RRDtool can be \
			easily integrated in shell scripts, perl, python, ruby, lua or tcl \
			applications.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a199faeb7eff7cafc46fac253e682d833d08932f3db93a550a4a5af180ca58db
COMPONENT_ARCHIVE_URL=	http://oss.oetiker.ch/rrdtool/pub/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://oss.oetiker.ch/rrdtool/
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

#rrd_config.h is obviously a leftover of a configure run in original source directors
#as such it has precedence in include search path (includes features.h which does not exist 
#in openindiana. Simply deleting is save as configure run will just create a correct 
#rrd_config.h ind build directory
COMPONENT_PREP_ACTION= (cd $(@D) && /bin/rm -f src/rrd_config.h ) 

COMPONENT_POST_INSTALL_ACTION=	$(shell /bin/chmod -R u+w $(@D) )

CONFIGURE_ENV.32+=	PERL=$(PERL)
CONFIGURE_ENV.32+=	PERLCC=$(CC)
CONFIGURE_ENV.64+=	PERL=$(PERL.5.24)
CONFIGURE_ENV.64+=	PERLCC=$(CC)
CONFIGURE_ENV.64+=	PERL_VERSION=5.24
CONFIGURE_OPTIONS.64+=	--with-perl-options="CC=$(CC) LD=$(CC) LIB=/usr/perl5/5.24/lib"
CONFIGURE_OPTIONS.32+=	--with-perl-options="CC=$(CC) LD=$(CC) LIB=/usr/perl5/$(PERL_VERSION)/lib"
CONFIGURE_OPTIONS+= 	-disable-python
CONFIGURE_OPTIONS+= 	-disable-ruby
CONFIGURE_OPTIONS+= 	-enable-static=no
CONFIGURE_OPTIONS+=	--without-systemdsystemunitdir

build: $(BUILD_32_and_64)

#RRDs.so is installed with perm 555 which breaks RUNPATH stripping
install: $(INSTALL_32_and_64) ; $(shell /bin/chmod -R u+w $(@D) )

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/rrdtool-amd64
REQUIRED_PACKAGES += image/rrdtool-i86
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
