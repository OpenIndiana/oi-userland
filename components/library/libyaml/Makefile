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
# Copyright (c) 2013 David Hoeppner. All rights reserved.
#
BUILD_BITS=	32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yaml
COMPONENT_VERSION=	0.2.5
COMPONENT_FMRI=	library/libyaml
COMPONENT_SUMMARY= LibYAML is a YAML parser and emitter written in C
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_PROJECT_URL=	https://pyyaml.org/wiki/LibYAML
COMPONENT_SRC_NAME= libyaml
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:fa240dbf262be053f3898006d502d514936c818e422afdcf33921c63bed9bf2e
COMPONENT_ARCHIVE_URL=	https://github.com/yaml/libyaml/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= 	MIT
COMPONENT_LICENSE_FILE=	libyaml.license

USE_DEFAULT_TEST_TRANSFORMS = yes

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= (cd $(@D); PATH="$(PATH)" ./bootstrap )

CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--enable-shared

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
