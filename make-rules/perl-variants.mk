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

# Give each variant its own build directory
VARIANT_584 = $(BUILD_DIR)/$(MACH32)-5.8.4
VARIANT_510 = $(BUILD_DIR)/$(MACH32)-5.10.0
VARIANT_512 = $(BUILD_DIR)/$(MACH32)-5.12.3

# List all variants here. You can override this variable locally to build given
# module with just selected perl revision
VARIANTS = $(VARIANT_584) # $(VARIANT_510) $(VARIANT_512)

# This has to be included prior to re-defining PERL variable
include ../../../make-rules/shared-macros.mk

P584=/usr/perl5/5.8.4/bin/perl
P510=/usr/perl5/5.10.0/bin/perl
P512=/usr/perl5/5.12.3/bin/perl
# Set perl used for each variant
$(VARIANT_584)/.built:  PERL=$(P584)
$(VARIANT_584)/.prep:  PERL=$(P584)
$(VARIANT_584)/.configured:  PERL=$(P584)
$(VARIANT_584)/.installed:  PERL=$(P584)

$(VARIANT_510)/.built:  PERL=$(P510)
$(VARIANT_510)/.prep:  PERL=$(P510)
$(VARIANT_510)/.configured:  PERL=$(P510)
$(VARIANT_510)/.installed:  PERL=$(P510)

$(VARIANT_512)/.built:  PERL=$(P512)
$(VARIANT_512)/.prep:  PERL=$(P512)
$(VARIANT_512)/.configured:  PERL=$(P512)
$(VARIANT_512)/.installed:  PERL=$(P512)
