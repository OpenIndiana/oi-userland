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
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		arping
COMPONENT_VERSION=	2.16
COMPONENT_PROJECT_URL=	http://www.habets.pp.se/synscan/programs.php?prog=arping
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6fd444250dd8ab9eca7d14f32fb1072d5a0c6e4a4f0846c87bfbc99f93d2d648
COMPONENT_ARCHIVE_URL=	https://github.com/ThomasHabets/arping/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	diagnostic/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SUMMARY=	ARPing is a program to probe a network segment with ARP who-has packets
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
	(cd $(@D) &&\
		aclocal -I . &&\
		autoheader &&\
		automake -a -f -c --gnu &&\
		autoconf &&\
		$(RM) config.h )

# Missing files in build dir for configure without this
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)

# Note: A few options below were replicated from tcpdump and fping recipes
# fix my alignment issues instead of falling over on sparc
studio_ALIGN.sparc.64=-xmemalign=16i
CONFIGURE_OPTIONS.sparc += ac_cv___attribute__=no
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH))
# lazyloading (indirectly enabled by -Bdirect) seems to cause problems with
# libpcap device enumeration.
LD_B_DIRECT=
#ASLR_MODE =	$(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libnet
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
