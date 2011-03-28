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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

COMPONENT_NAME=		DBI
COMPONENT_VERSION=	1.58
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz

COMPONENT_ARCHIVE_HASH=	sha1:5f5861728c85b3998eb5a6db3703f46d0fc6faf1
COMPONENT_ARCHIVE_URL=	http://cr.opensolaris.org/~neuron/dbi/$(COMPONENT_ARCHIVE)

include ../../../make-rules/perl-variants.mk
include ../../../make-rules/perl-generic.mk

$(VARIANT_584)/.installed: \
	PERL_FILES_TO_UPDATE_MAGIC_LINE=\
	usr/perl5/vendor_perl/5.8.4/$(PERL_ARCH)-solaris-64int/goferperf.pl \
	usr/perl5/vendor_perl/5.8.4/$(PERL_ARCH)-solaris-64int/dbixs_rev.pl
