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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

#
# This file contains all the macros used for the libsif module compilation.
#
LIBSIF_COMPONENT_NAME=	libsif
LIBSIF_COMPONENT_VERSION=	1.1
LIBSIF_COMPONENT_SRC=	$(LIBSIF_COMPONENT_NAME)-$(LIBSIF_COMPONENT_VERSION)
LIBSIF_COMPONENT_ARCHIVE=	$(LIBSIF_COMPONENT_SRC).tar.gz
LIBSIF_COMPONENT_SERVER=       download.oracle.com
LIBSIF_COMPONENT_ARCHIVE_URL= http://$(LIBSIF_COMPONENT_SERVER)/otn-pub/oss/networking/$(LIBSIF_COMPONENT_ARCHIVE)
