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
# Copyright 2016 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= hacluster-common
COMPONENT_VERSION= 1.0
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_PROJECT_URL= http://www.linux-ha.org/doc/dev-guides/ra-dev-guide.html
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_SUMMARY= Common items for hacluster components.

include $(WS_MAKE_RULES)/ips.mk

download:

prep:

build:

install:
		[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean:
		$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

