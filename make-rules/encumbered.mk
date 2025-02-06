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
# Copyright 2015 Alexander Pyhalov
#

WS_REPO =       $(WS_TOP)/$(MACH)/encumbered-repo

COMPONENT_PKGLINT_ENV += ENCUMBERED=true

PUBLISHER  = hipster-encumbered

BASS_O_MATIC =  $(WS_TOOLS)/bass-o-matic --subdir=components/encumbered

ENCUMBERED = encumbered/

# Support for building with the (non-default) ffmpeg version 6
ifeq ($(strip $(FFMPEG_VERSION)),6)
PKG_CONFIG_PATH.64 := /usr/lib/$(MACH64)/pkgconfig/ffmpeg-6:$(PKG_CONFIG_PATH.64)
endif

# If a component needs ffmpeg libraries then it also needs ffmpeg development
# files (the versioned developer/ffmpeg package) for building.  To avoid the
# need to manually add the ffmpeg development package into the
# REQUIRED_PACKAGES list of all components that needs it we do so automatically
# here.
#
# Since both ffmpeg libraries package and ffmpeg development package are
# encumbered we do this here instead of ips.mk.
REQUIRED_PACKAGES_TRANSFORM += -e '/ library\/ffmpeg/{p;s/library/developer/}'

# If a component needs a runtime x265 library then it also needs the x265
# development files for building.  Add such dependency automatically here.
REQUIRED_PACKAGES_TRANSFORM += -e '/ library\/video\/x265-/{p;s/-.*$$//}'
