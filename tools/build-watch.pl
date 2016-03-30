#!/usr/perl5/bin/perl
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
# Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
#
#
# build-watch.pl - a simple utility to watch a process and it's children under
# 		   dtrace and process the results for dependency information.
#
# Ex:
#	$ export WS_TOP=/top/of/your/workspace
#	$ cd $(WS_TOP)/components/{component}
#	$ $(WS_TOP)/tools/build-watch.pl -c "gmake install"
#

use File::Temp qw/tempfile/;
use Getopt::Long;

my $verbose = 0;

my @ignore = (
	'^[^/\.].*',		# ignore paths that don't begin with / or .	
	'^/dev/',		# ignore devices
	'^/etc/',		# ignore config files
	'^/proc/',		# ignore /proc
	'^/tmp/',		# ignore temp files
	'^/var/',		# ignore more temp/volatile files
	'^/usr/lib/locale/',	# ignore locale support
	'^/usr/share/lib/make/',	# ignore make bits
	'^/usr/share/lib/zoneinfo/',	# ignore timezone info
	'/SUNWspro/',		# ignore compiler bits
	'/sunstudio12.1/',	# ignore more compiler bits
	'^/ws/',		# nothing in /ws can be interesting
	'^\.[/\.]{0,1}$'	# ignore ., .., and ./
);

sub match
{
	local($string, @expressions) = @_;

	foreach (@expressions) {
		($string =~ m{$_}) && return (1);
	}
	return (0);
}

sub process_dtrace_results
{
	local ($filename) = @_;
	my (%tools, %files, $fh) = ();

	open($fh, "<$filename") || die "open($filename): $!\n";
	while (<$fh>) {
		if (/^TOOL:\s+(\S+) = (\S+)$/) {
			$tools{$2} = $1;
		} elsif ((/^FILE:\s+(\S+)\s*$/) && (match($1, @ignore) == 0) &&
			 (-e $1)) {
			$files{$1} = $1;
		}
	}
	close($fh);

	return (\%tools, \%files);
}

sub generate_package_requirements
{
	local (*tools, *files) = @_;
	my ($count, %pkgs, @search_strings, $search_string) = (0);

	# create a set of search strings to query the package DB
	foreach (sort (keys %tools, keys %files)) {
		if ($count++ % 100 == 0) {
			defined($search_string) && \
				push(@search_strings, $search_string);
			$search_string = $_;
		} else {
			$search_string .= " OR $_";
		}
	}
	push(@search_strings, $search_string);

	# walk through the search strings and query the package DB
	foreach (@search_strings) {
		my $IFH;

		open($IFH, "pkg search -l -H -o path,pkg.name '$_'|");
		while (<$IFH>) {
           		(/^(\S+)\s+(\S+)$/) && ($pkgs{$1} = $2);
		}
		close($IFH);
	}

	return (\%pkgs);
}

#
# Main execution begins here
#
GetOptions("c|command=s" => \$cmd, "i|input-file=s" => \@file,
	   "p|pkg" => \$pkg_flag, "v|verbose" => \$verbose);

if (defined($cmd)) {
	$file = (tempfile(UNLINK => 1))[1];

	if (!defined($ENV{'WS_TOP'})) {
		print("WS_TOP must be set in the calling environment\n");
		exit(1);
	}
	($verbose == 1) && print("*** Executing '$cmd' under dtrace...\n");
	system($ENV{'WS_TOP'}."/tools/build-watch.d", "-o", $file, "-c", $cmd);
}

($verbose == 1) && printf("*** Processing results...\n");
my ($tools, $files) = process_dtrace_results($file);

if (defined($pkg_flag)) {
	($verbose == 1) && printf("*** Generating package requirements...\n");
	my ($pkgs) = generate_package_requirements($tools, $files);
}

if (defined($tools)) {
	print "\n";
	print "REQUIRED_TOOL +=\t$_\n" for (sort keys %$tools);
}

if (defined($files)) {
	print "\n";
	print "REQUIRED_FILE +=\t$_\n" for (sort keys %$files);
}

if (defined($pkgs)) {
	@unique{values %$pkgs} = ();
	print "\n";
	print "REQUIRED_PKG +=\t$_\n" for (sort keys %unique);
}

exit(0);
