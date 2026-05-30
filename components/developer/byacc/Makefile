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
# Copyright (c) 2025, 2026 David Stes
# IPS Makefile for Berkeley Yacc (sometimes called Better Yacc)
# Berkeley Yacc was written by Robert Corbett according to the README 
# Also see ACKNOWLEDGEMENTS and AUTHORS in the sources
# See sources yysccsid[] = \"@(#)yaccpar	1.9 (Berkeley) 02/21/93\" */"
# The invisible-island.net byacc version is a version of byacc maintained by Thomas E. Dickey
# The component version is taken from VERSION in that version of byacc
# Other versions of byacc exist, see for example https://ftp.math.utah.edu/pub/byacc
# or see for example the FreeBSD/NetBSD/OpenBSD source code or FreeBSD ports collection
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		byacc
COMPONENT_VERSION=	20260126
COMPONENT_SUMMARY=	byacc - Berkeley Yacc is an LALR(1) parser generator
COMPONENT_PROJECT_URL=	https://invisible-island.net/archives/byacc
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b618c5fb44c2f5f048843db90f7d1b24f78f47b07913c8c7ba8c942d3eb24b00
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/parser/byacc
COMPONENT_CLASSIFICATION=	Development/Other Languages
# Berkeley Yacc is reportedly not BSD software but PublicDomain (see LICENSE file in the package)
COMPONENT_LICENSE=	PublicDomain
COMPONENT_LICENSE_FILE= LICENSE

# configure in byacc sources from Invisible-Island is created by autoconf 2.52 and does not understand --localedir
CONFIGURE_DEFAULT_DIRS= pre-2.60

include $(WS_MAKE_RULES)/common.mk

# delete date and time with GSED (delete second line of test output)
COMPONENT_TEST_TRANSFORMS += '-e "2d"'

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
