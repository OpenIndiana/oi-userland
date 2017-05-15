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
# Copyright 2017 Gary Mills
# Copyright (c) 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           hunspell
COMPONENT_VERSION=        1.3.4
COMPONENT_PROJECT_URL=    http://hunspell.github.io/
COMPONENT_SUMMARY=        Improved spellchecker
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=        \
    sha256:55918522cb0041748507dd4f5aa92d043cef337aa589b9367c2221da084281ac
COMPONENT_ARCHIVE_URL=        https://github.com/hunspell/hunspell/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING.LGPL
COMPONENT_FMRI= text/hunspell
COMPONENT_CLASSIFICATION = System/Text Tools

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = $(PATH.gnu)

CPPFLAGS += -I/usr/include/ncurses
# We need to check headers with C++ compiler, but configure uses $(CC).
# We can't use $(CXX) as $(CC) as $(CC) is used to compile C files.
# So we make $(CC) behave more like $(CXX) during configure.
CFLAGS += -D_XOPEN_SOURCE=600
CFLAGS += -std=c99

CPPFLAGS +=	-I/usr/include/ncurses

# Check location of ncurses libraries
ifeq ($(shell test -f /usr/gnu/lib/libncurses.so && echo y),y)
LDFLAGS +=	-L$(GNULIB.$(BITS)) -R$(GNULIB.$(BITS))
endif

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
                                        autoreconf -f )


# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"

CONFIGURE_OPTIONS+=        --with-ui
CONFIGURE_OPTIONS+=        --with-readline

ENV=/usr/bin/env -i

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Failed tests: rep.test, checksharps.test, 1463589.test
test:		$(TEST_32)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
