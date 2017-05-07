#!/usr/bin/perl -w

# Copyright (C) 1997,1998,1999, Roger Espel Llima
# Copyright (C) 2000, Sergey Babkin
# Copyright (C) 2009, Alex Kozlov
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and any associated documentation files (the "Software"), to 
# deal in the Software without restriction, including without limitation the 
# rights to use, copy, modify, merge, publish, distribute, sublicense, 
# and/or sell copies of the Software, and to permit persons to whom the 
# Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
# SOFTWARE'S COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE

# (whew, that's done!)

# why does the world need another rpm2cpio?  because the existing one
# won't build unless you have half a ton of things that aren't really
# required for it, since it uses the same library used to extract RPM's.
# in particular, it won't build on the HPsUX box i'm on.

use strict;

my ($f, $rpm, $filter) = ();

if ($#ARGV == -1) {
	$f = "STDIN";
} elsif ($#ARGV == 0) {
	open($f, "< $ARGV[0]") or die "Can't read file $ARGV[0]\n";
} else {
	print "rpm2cpio v1.3, perl version by orabidoo\n";
	print "use: rpm2cpio [file.rpm]\n";
	print "dumps the contents to stdout as a GNU cpio archive\n";
	exit 0;
}

read $f, $rpm, 96;

my ($magic, $major, undef) = unpack("NCC", $rpm);

die "Not an RPM\n" if $magic != 0xedabeedb;
die "Not a version 3 or 4 RPM\n" if $major != 3 and $major != 4;

read $f, $rpm, 16 or die "No header\n";
while(1) {
	($magic, undef, my $sections, my $bytes) = unpack("N4", $rpm);
	my ($smagic, $smagic2) = unpack("nN", $rpm);

	#printf(STDERR "0x%x 0x%x 0x%x 0x%x 0x%x\n",
	#	tell($f)-16, $magic, $sections, $bytes, $smagic);

	if ($smagic == 0x1f8b) {
		$filter = "gzip -cd";
		last;
	}
	# BZh
	if ($smagic == 0x425a and ($smagic2 & 0xff000000) == 0x68000000) {
		$filter = "bzip2 -cd";
		last;
	}
	# 0xFD, '7zXZ', 0x0
	if ($smagic == 0xfd37 and $smagic2 == 0x7a585a00) {
		$filter = "xz -cd";
		last;
	}
	# assume lzma if there is no sig
	if ($magic != 0x8eade801) {
		$filter = "lzma -cd";
		last;
	}

	# skip the headers
	seek $f, 16 * $sections + $bytes, 1 or die "File is too small\n";
	do {
		read $f, $rpm, 1 or die "No header\n" ;
	} while(0 == unpack("C", $rpm));
	read $f, $rpm, 15, 1 or die "No header\n" ;
}

open(ZCAT, "| $filter") or die "can't pipe to $filter\n";

while($rpm ne '') {
	print ZCAT $rpm;
	read $f, $rpm, 10240; # read in blocks
}

close ZCAT;
close $f;
