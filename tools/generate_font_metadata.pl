#! /usr/perl5/bin/perl -w

#
# Copyright (c) 2010, 2018, Oracle and/or its affiliates. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#

require 5.005;				# minimal Perl version required
use strict;				#
use diagnostics;			#
use integer;				#
use File::Spec;				# pathname manipulation routines
use English qw( -nomatchvars );
use Getopt::Long;

# Required arguments:
# -p <proto_area>
# -m <manifest>

my $proto_dir;
my $manifest;

my $result = GetOptions('p|protodir=s' => \$proto_dir,
                        'm|manifest=s' => \$manifest);

if (!defined($proto_dir)) {
  print STDERR "Missing required protodir argument\n";
  exit(1);
}

if (!defined($manifest)) {
  print STDERR "Missing required manifest argument\n";
  exit(1);
}

# Directories containing font files
my %fontdirs = ();

open my $MANIFEST, '<', $manifest
  or die "Cannot open manifest $manifest: $!\n";

while (my $man = <$MANIFEST>) {
  if ($man =~ m{path=(\S+)/fonts.dir}) {
    $fontdirs{$1} = $1;
  }
}
close $MANIFEST;

foreach my $fd (keys %fontdirs) {
  my $protofontpath = join('/', $proto_dir, $fd);
  my $protometafile = join('/', $proto_dir, $fd, 'fonts.dir');
  my %xlfds = ();

  if (! -f $protometafile) {
      # mkfontscale -b -s -l is equivalent to mkfontdir
      run_cmd("/usr/bin/mkfontscale", "-b", "-s", "-l",
	      $protofontpath);
  }

  open my $XFILE, '<', $protometafile
    or die "Cannot open $protometafile: $!\n";

  while (my $x = <$XFILE>) {
    chomp($x);
    if ($x =~ m{\s+}) {
      my ($fontfile, $fontxlfd) = split(/\s+/, $x, 2);
      $xlfds{$fontxlfd} = $fontfile;
      printf
	qq(<transform file path="$fd/%s" -> add info.file.font.xlfd "%s">\n),
	$fontfile, $fontxlfd;
    }
  }
  close $XFILE;

  $protometafile = join('/', $proto_dir, $fd, 'fonts.alias');

  if (-f $protometafile) {

    open my $XFILE, '<', $protometafile
      or die "Cannot open $protometafile: $!\n";

    while (my $x = <$XFILE>) {
      chomp($x);
      if ($x =~ m{\s+}) {
	my ($fontalias, $fontxlfd) = split(/\s+/, $x, 2);
	$fontxlfd =~ s{^"(.*)"$}{$1};
	if (exists $xlfds{$fontxlfd}) {
	  my $fontfile = $xlfds{$fontxlfd};
	  printf
	    qq(<transform file path="$fd/%s" -> add info.file.font.xlfd "%s">\n),
	      $fontfile, $fontalias;
	} else {
#	  print STDERR qq(No match found for "$fontxlfd" in $protometafile\n);
	}
      }
    }
    close $XFILE;
  }

}

my $fc_scan = "/usr/bin/fc-scan";

# See FcPatternFormat(3) for the full definition of the format syntax
#  %{file} => print the named value for this font
#  %{fullname|cescape} => print the named value with C-style string escapes
#			  (adds \ in front of \ or " characters)
#  %{?fullname{..A..}{..B..}} => if fullname is defined, then print A, else B
#  []fullname,fullnamelang{..A..} => for each pair of fullname & fullnamelang,
#					print A with those values substituted
my $fc_scan_format = q(--format=%{?fullname{%{[]fullname,fullnamelang{<transform file path="%{file}" -> add info.file.font.name:%{fullnamelang} "%{fullname|cescape}">\n}}}{%{[]family,style{<transform file path="%{file}" -> add info.file.font.name "%{family|cescape} %{style|cescape} %{pixelsize}">\n}}}});


chdir($proto_dir);
run_cmd($fc_scan, $fc_scan_format, keys %fontdirs);
exit(0);

sub run_cmd {
    my $cmd = $_[0];
    system(@_);
    if ($? == -1) {
	print STDERR "failed to execute $cmd: $!\n";
    }
    elsif ($? & 127) {
	printf STDERR "$cmd died with signal %d, %s coredump\n",
	($? & 127),  ($? & 128) ? 'with' : 'without';
    }
    elsif ($? != 0) {
	my $exit_code = $? >> 8;
	if ($exit_code != 1) {
	    printf STDERR "$cmd exited with value %d\n", $exit_code;
	    exit($exit_code);
	}
    }
}
