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
# Copyright 2017, Aurelien Larcher.
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         quilt
COMPONENT_VERSION=      0.67
COMPONENT_SUMMARY=      Quilt - tool to manage series of patches
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://savannah.nongnu.org/projects/quilt/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:3be3be0987e72a6c364678bb827e3e1fcc10322b56bc5f02b576698f55013cc2
COMPONENT_ARCHIVE_URL= 	https://download.savannah.gnu.org/releases/quilt/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/quilt
COMPONENT_CLASSIFICATION= Development/Source Code Management
COMPONENT_LICENSE=      GPLv2 
COMPONENT_LICENSE_FILE= COPYING 

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
    (cd $(@D) ; autoconf )

PATCH_LEVEL= 0

# without this, some make messages end up in the
# generated README and man pages.
COMPONENT_BUILD_ARGS+=	--no-print-directory

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-cp=$(GNUBIN)/cp
CONFIGURE_OPTIONS += --with-date=$(GNUBIN)/date
CONFIGURE_OPTIONS += --with-getopt=$(GNUBIN)/getopt
CONFIGURE_OPTIONS += --with-grep=$(GNUBIN)/grep
CONFIGURE_OPTIONS += --with-tail=$(GNUBIN)/tail
CONFIGURE_OPTIONS += --with-tar=$(GNUBIN)/tar
CONFIGURE_OPTIONS += --with-tr=$(GNUBIN)/tr
CONFIGURE_OPTIONS += --with-sed=$(GNUBIN)/sed
CONFIGURE_OPTIONS += --with-diff=$(GNUBIN)/diff
CONFIGURE_OPTIONS += --with-find=$(GNUBIN)/find
CONFIGURE_OPTIONS += --with-patch=$(GNUBIN)/patch
CONFIGURE_OPTIONS += --with-column=$(USRBINDIR)/column
CONFIGURE_OPTIONS += --with-diffstat=$(USRBINDIR)/diffstat
CONFIGURE_OPTIONS += --with-perl=$(PERL)
CONFIGURE_OPTIONS += --with-pod2man=$(POD2MAN)
CONFIGURE_OPTIONS += --with-xgettext=/usr/bin/gxgettext
CONFIGURE_OPTIONS += --with-msgfmt=/usr/bin/gmsgfmt
CONFIGURE_OPTIONS += --without-rpmbuild
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ARGS += BUILD_ROOT=$(PROTO_DIR)

COMPONENT_TEST_TRANSFORMS += \
 	'-n ' \
	'-e "/commands/p" ' \

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += archiver/gnu-tar
REQUIRED_PACKAGES += compress/p7zip
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += file/gnu-findutils
REQUIRED_PACKAGES += service/network/smtp/postfix
REQUIRED_PACKAGES += service/network/smtp/sendmail
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/gnu-getopt
REQUIRED_PACKAGES += system/network/mailwrapper
REQUIRED_PACKAGES += text/diffstat
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += text/gnu-diffutils
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/gnu-patch
REQUIRED_PACKAGES += text/gnu-sed
REQUIRED_PACKAGES += text/text-utilities
