#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#
# Copyright 2016 by Jim Klimov
#

include ../../../make-rules/shared-macros.mk

# This one only delivers a file if other prereqs are present
# The network-ssh-askpass package is a dispatcher to depend on optional
# implementation packages, such as (initially) the network-ssh-askpass-zenity
COMPONENT_NAME=		ssh-askpass
COMPONENT_VERSION=	1.0
COMPONENT_REVISION=	1

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/prep-download.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

download::

$(BUILD_DIR)/.prep: Makefile network-ssh-askpass.p5m network-ssh-askpass-zenity.p5m
	$(MKDIR) -p "$(@D)"
	$(TOUCH) $@

prep::  $(BUILD_DIR)/.prep

clean::
	$(RM) -r $(BUILD_DIR)

clobber:: clean

build:: $(BUILD_DIR)/.prep

install: $(BUILD_DIR)/.prep

# note: no REQUIRED_PACKAGES needed to BUILD this recipe (we deliver
# some bits from attached files/ directly)
# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/zenity
REQUIRED_PACKAGES += network/ssh
REQUIRED_PACKAGES += shell/ksh93
