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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk
include $(WS_COMPONENTS)/php/php-metadata.mk

COMPONENT_NAME=		suhosin
COMPONENT_VERSION=	0.9.37.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:322ba104a17196bae63d39404da103fd011b09fde0f02484dc44366511c586ba
COMPONENT_ARCHIVE_URL=	http://download.suhosin.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.suhosin.org/

TPNO=			22432

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

include $(PHP_TOP_DIR)/phpize.mk

CONFIGURE_OPTIONS += --enable-suhosin

# Run MySQL tests - requires MySQL (and maybe configuration!)
#COMPONENT_TEST_ENV += TEST_SUHOSIN_MYSQL=1

configure: $(CONFIGURE_64)
build: $(BUILD_64)
install: $(INSTALL_64)
test: $(TEST_64)

REQUIRED_PACKAGES += system/library
