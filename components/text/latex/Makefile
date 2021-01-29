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
# Copyright (c) 2021 David Stes
#
# LaTeX package built using TeX live
# TeX live and latex.profile are in meta-packages/texlive
#
# install-tl --profile latex.profile
#

# for the moment we have a  'packaged texinfo directory' error on pkglint
# "Error: packaged texinfo directory file (%<action.path>)"
PKGLINT=/bin/true

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		latex
COMPONENT_VERSION=	1.0.0
COMPONENT_SUMMARY=	LaTeX from TeXLive 2020
COMPONENT_PROJECT_URL=	http://tug.org
COMPONENT_ARCHIVE_URL=	http://tug.org
COMPONENT_FMRI=		text/latex
COMPONENT_TEXLIVE=	latex.profile

latex.profile : texlive.profile
	$(GSED) 's@/usr@PROTO_DIR/usr@' < texlive.profile > latex.profile

include $(WS_TOP)/make-rules/texlive.mk
include $(WS_TOP)/make-rules/ips.mk

