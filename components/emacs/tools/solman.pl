#!/usr/bin/perl

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
# Copyright (c) 2008, 2011, Oracle and/or its affiliates. All rights reserved.
#

# Copy the manpage text on stdin to stdout, adding an Attribute
# block to the end:
#
#	solman pkgname
#
# where pkgname is the name of the Solaris package to show.
#

die "usage: solman pkgname\n" 
    if (scalar(@ARGV) != 1);

$pkgname = $ARGV[0];

print <<TEXT;
'\\" t\
.\\"\
.\\" Modified for Solaris to to add the Solaris stability classification,\
.\\" and to add a note about source availability.\
.\\"
TEXT

# Input to output, unmodified
while ($line = <STDIN>) {
	print $line;
}

print <<TEXT;
.\\" Begin Solaris update\
.SH ATTRIBUTES\
See\
.BR attributes (5)\
for descriptions of the following attributes:\
.sp\
.TS\
box;\
cbp-1 | cbp-1\
l | l .\
ATTRIBUTE TYPE	ATTRIBUTE VALUE\
=\
Availability	$pkgname\
=\
Interface Stability	Uncommitted\
.TE\
.PP\
.SH NOTES\
Source for GNU emacs is available on http://opensolaris.org.\
.\\" End Solaris update
TEXT
