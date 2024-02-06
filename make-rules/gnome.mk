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
# Copyright 2024 Marcel Telka
#

# Defaults suitable for most GNOME projects
COMPONENT_VERSION ?=		$(HUMAN_VERSION)
GNOME_MAJOR ?=			1	# how many numbers from the version constitutes major version
COMPONENT_VERSION_MAJOR ?=	$(subst $(space),.,$(wordlist 1,$(GNOME_MAJOR),$(subst ., ,$(COMPONENT_VERSION))))
COMPONENT_PROJECT_URL ?=	https://gitlab.gnome.org/GNOME/$(COMPONENT_NAME)
COMPONENT_SRC ?=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE ?=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL ?=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE)
