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
# Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=             64
COMPILER=               gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		speech-dispatcher
COMPONENT_VERSION=	0.8.6
COMPONENT_PROJECT_URL=	https://devel.freebsoft.org/speechd
COMPONENT_ARCHIVE_HASH= \
   sha256:c233dc3757c1f0d3676480d1052d42d88d18d29ab0cb0c8b5ce8edc3e7386ff8
COMPONENT_ARCHIVE_URL=	\
    https://devel.freebsoft.org/pub/projects/speechd/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/accessibility
COMPONENT_ANITYA_ID=    13411

TPNO=			32940

TEST_TARGET = $(NO_TESTS)

# Needs updated glib2, not available on S11
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# Delete this when build servers are installed with dotconf
DOTCONF_BASE = $(WS_COMPONENTS)/desktop/dotconf/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(DOTCONF_BASE)$(PKG_CONFIG_PATH.$(BITS))
LD_OPTIONS += -L $(DOTCONF_BASE)$(USRLIB.$(BITS))
CPPFLAGS += -I$(DOTCONF_BASE)$(USRINCDIR)

# The dependency isn't installed, so add it manually since pkgdepend
# can't resolve them yet: 15708323
DEPENDED += $(WS_TOP)/components/desktop/dotconf/build/manifest-$(MACH)-dotconf.depend

# Temporary until dependencies are all on build machines
REQUIRED_PACKAGES += $(shell $(GSED) -n 's/REQUIRED_PACKAGES +=//p' ../dotconf/Makefile)
#end Delete

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-espeak
CONFIGURE_OPTIONS += --with-pulse

# Assumes GNU xgettext & msgfmt are first in PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += library/audio/pulseaudio
# Put this back in once the pkg is installed on the build server
#REQUIRED_PACKAGES = library/desktop/dotconf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/speech/espeak

