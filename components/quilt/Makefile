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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH = /usr/gnu/bin:/usr/bin

COMPONENT_NAME=		quilt
COMPONENT_VERSION=	0.64
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://savannah.nongnu.org/projects/quilt/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c4bfd3282214a288e8d3e921ae4d52e73e24c4fead72b5446752adee99a7affd
COMPONENT_ARCHIVE_URL=	http://download.savannah.gnu.org/releases/quilt/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/quilt

TPNO=			21555

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
    (cd $(@D) ; autoconf )

PATCH_LEVEL=	0

# without this, some make messages end up in the
# generated README and man pages.
COMPONENT_BUILD_ARGS+=	--no-print-directory

CONFIGURE_OPTIONS += --with-cp=/usr/gnu/bin/cp
CONFIGURE_OPTIONS += --with-date=/usr/gnu/bin/date
CONFIGURE_OPTIONS += --with-grep=/usr/gnu/bin/grep
CONFIGURE_OPTIONS += --with-tail=/usr/gnu/bin/tail
CONFIGURE_OPTIONS += --with-tr=/usr/gnu/bin/tr
CONFIGURE_OPTIONS += --with-sed=/usr/gnu/bin/sed
CONFIGURE_OPTIONS += --with-diff=/usr/gnu/bin/diff
CONFIGURE_OPTIONS += --with-find=/usr/gnu/bin/find
CONFIGURE_OPTIONS += --with-patch=/usr/gnu/bin/patch
CONFIGURE_OPTIONS += --with-perl=/usr/perl5/$(PERL_VERSION)/bin/perl
CONFIGURE_OPTIONS += --with-pod2man=/usr/perl5/$(PERL_VERSION)/bin/pod2man
CONFIGURE_OPTIONS += --with-xgettext=/usr/bin/gxgettext
CONFIGURE_OPTIONS += --with-msgfmt=/usr/bin/gmsgfmt

CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ARGS +=	BUILD_ROOT=$(PROTO_DIR)

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.* -> .*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^Generating.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	$(GSED) -e "s|^PATH.*$$|PATH := /usr/gnu/bin:/usr/bin|" \
	$(BUILD_DIR_64)/Makefile > $(BUILD_DIR_64)/Makefile-system-test
COMPONENT_SYSTEM_TEST_ARGS = -f $(BUILD_DIR_64)/Makefile-system-test

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    configure $(SYSTEM_TEST_64)


REQUIRED_PACKAGES += archiver/gnu-tar
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += file/gnu-findutils
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += service/network/smtp/sendmail
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += text/gnu-diffutils
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/gnu-patch
REQUIRED_PACKAGES += text/gnu-sed
