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
# Copyright (c) 2010, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2023 Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		a2ps
COMPONENT_VERSION=	4.15.4
#COMPONENT_REVISION=	4
COMPONENT_SUMMARY=	GNU a2ps - 'Anything to PostScript' converter and pretty printer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/a2ps/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4a063f84ba89d86be14a6704ca35fd130083b572f1376b439a1b79b67b206dd7
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/a2ps/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		print/filter/a2ps
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE=	GPLv3

include $(WS_MAKE_RULES)/common.mk

# don't use LD_Z_IGNORE: causes linker problems
LD_Z_IGNORE=

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --sysconfdir=/etc/gnu
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --with-medium=a4

# because viewpathing isn't quite right in this version of a2ps
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; ln -s $(SOURCE_DIR)/auxdir/mkinstalldirs)

COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D)/contrib ; \
	 ln -s $(SOURCE_DIR)/contrib/shell.m4) ; \
	(cd $(@D)/doc ; \
	 ln -s $(SOURCE_DIR)/doc/make-authors.pl ; \
	 ln -s $(SOURCE_DIR)/doc/translators.txt) ; \
	(cd $(@D)/sheets ; \
	 for sheet in $(SOURCE_DIR)/sheets/*.ssh ; do \
	     ln -s $$sheet ; \
	 done)

# Enable ASLR for this component
ASLR_MODE= $(ASLR_ENABLE)

# Build dependency manually added
REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += editor/gnu-emacs

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += library/libpaper
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
