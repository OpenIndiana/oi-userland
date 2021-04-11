#!/usr/bin/perl

#
# currently (and perhaps forever) the Makefile of squeak places binaries
# in subversion-revision_suffix where suffix can be 64bit
#
# the pkglint check for 64binaries in 32bit path will complain on this;
# the usage enforced by pkglint is 
# /usr/lib/amd64/squeak/xyz/plugin  instead of /usr/lib/squeak/xyz_64bit/plugin
# ./amd64.pl < in > out
# example:  ./amd64.pl < ../manifests/sample-manifest.p5m > sample-manifest.p5m
#

while (<>) {
	if (/ckformat/) {
	   # don't process cause _64bit is already processed
	   print $_;
	} elsif (/squeakvm/) {
	   # don't process cause _64bit is already processed
	   print $_;
	} elsif (/transform/) {
	   # don't process cause _64bit is already processed
	   print $_;
	} elsif (/_64bit/) {
		s/file path=//;
		chomp;
		$file = $_;
		$path = $_;
		$path =~ s/usr\/lib/usr\/lib\/amd64/;
		$path =~ s/_64bit//;
		print "file ",$file," path=",$path,"\n";
	} else {
		print $_;
	}
}

