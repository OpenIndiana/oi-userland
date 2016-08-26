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

include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:

install:

test:		$(NO_TESTS)

# note: no REQUIRED_PACKAGES needed to BUILD this recipe (we deliver
# some bits from attached files/ directly)
