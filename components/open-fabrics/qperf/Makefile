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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../ofed-component-macros.mk

COMPONENT_NAME=		qperf
COMPONENT_VERSION=	0.4.6
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-0.1.gb81434e.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:304b89d1b006c959cad3b132346a6d061526fe626953ef99c764df396e43f959
COMPONENT_BUGDB=	utility/ofuv_tools

include ../ofed-component.mk

LIBS += -lkstat -lrdmacm -libverbs

COMPONENT_INSTALL_ENV +=	INSTALL="$(INSTALL) -m 755"

COMPONENT_PRE_CONFIGURE_ACTION = \
        (mkdir $(@D)/src ; cd $(@D)/src ; ln -s $(SOURCE_DIR)/src/help.txt ; \
         ln -s $(SOURCE_DIR)/src/mkhelp ; ln -s $(SOURCE_DIR)/src/mkman)

