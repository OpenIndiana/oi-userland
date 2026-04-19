#!/usr/bin/perl

#
# because Squeak has many plugins,
# there are also many dependencies 
# in order to have a small "kernel" package
# this script is used
#
# the script "classifies" plugins into currently 3 categories:
#  - squeak-nodisplay (only libc,libm math,libpthread, ksh)
#  - squeak-display-X11 (only x11,xext,xrender)
#  - squeak (ssl,ffi,pulseaudio freetype2,gnome, everything else)
#
# Usage: check the samplemanifest,
# ./subversion.pl < ../manifests/sample-manifest.p5m > sample2.p5m
# then classify the files as follows:
# ./classify.pl < sample2.p5m
# then alias the amd64 files (install in component directory)
# ./amd64.pl < squeak.p5m > ../squeak.p5m
# or run ./amd64-p5m.sh
#

# name can be changed to cog-spur or stack-spur for squeak opensmalltalk packages
$name="squeak";

open(NODISPLAY,">>","${name}-nodisplay.p5m") || die "Can't open ${name}-nodisplay.p5m";

open(X11,">>","${name}-display-X11.p5m") || die "Can't open ${name}-display-X11.p5m";

open(VEP,">>","${name}-vep.p5m") || die "Can't open ${name}-vep.p5m";

open(SSL,">>","${name}-ssl.p5m") || die "Can't open ${name}-ssl.p5m";

open(REST,">>","${name}.p5m") || die "Can't open ${name}.p5m";

# TODO: PTY support in squeak 4.21.5
# open(PTY,">>","${name}-pty.p5m") || die "Can't open ${name}-pty.p5m";

while (<>) {
	if (/^#/) {
		# ignore lines that start with comment
	} elsif (/^$/) {
		# ignore empty lines
	} elsif (/license /) {
		# ignore license lines
	} elsif (/set name=/) {
		# ignore those lines
	} elsif (/dir  path=/) {
		# ignore those lines
	} elsif (/file path=usr\/squeak/) {
		# ignore those lines
	} elsif (/file path=/) {
		if (/Sun/) {
			# ignore the Sun sound plugin - we use pulseaudio
		} elsif (/vm-sound-OSS/) {
			# ignore the OSS sound plugin - we use pulseaudio
		} elsif (/usr\/bin/) {
			# don't deal with driver scripts here
		} elsif (/usr\/doc/) {
			# don't deal with docs here
		} elsif (/man1/) {
			# don't deal with the manpages here
		} elsif (/squeak$/) {
			# don't deal with the actual binary here
		} elsif (/squeakvm/) {
			# don't deal with the actual binary here
		} elsif (/ckformat$/) {
			# don't deal with the ckformat binary here
		} elsif (/AioPlugin/) {
			print NODISPLAY $_;
		} elsif (/ClipboardExtendedPlugin/) {
			print X11 $_;
		} elsif (/FileCopyPlugin/) {
			print NODISPLAY $_;
		} elsif (/HostWindowPlugin/) {
			print X11 $_;
		} elsif (/ImmX11Plugin/) {
			print X11 $_;
		} elsif (/Squeak3D/) {
			print X11 $_;
		} elsif (/SqueakSSL/) {
			print SSL $_;
		} elsif (/B3DAcceleratorPlugin/) {
			print X11 $_;
		} elsif (/UnixOSProcessPlugin/) {
			print NODISPLAY $_;
		} elsif (/PseudoTTYPlugin/) {
# TODO: PTY support in squeak 4.21.5
#			print PTY $_;
		} elsif (/MD5Plugin/) {
			print NODISPLAY $_;
		} elsif (/SHA2Plugin/) {
			print NODISPLAY $_;
		} elsif (/DESPlugin/) {
			print NODISPLAY $_;
		} elsif (/XDisplayControlPlugin/) {
			print X11 $_;
		} elsif (/VectorEnginePlugin/) {
			print VEP $_;
		} elsif (/vm-sound-null/) {
			print NODISPLAY $_;
		} elsif (/vm-display-null/) {
			print NODISPLAY $_;
		} elsif (/vm-display-X11/) {
			print X11 $_;
		} elsif (/vm-display-X11/) {
			print X11 $_;
		} elsif (/usr\/lib\/squeak/) {
			print REST $_;
		} elsif (/usr\/lib\/\$\(MACH64\)\/squeak/) {
			print REST $_;
		} else {
			# unclassified files
			print $_;
		}
	} elsif (/inisqueak.1/) {
		# ignore manpage hardlink
	} elsif (/hardlink path=/) {
		# unclassified files
		print $_;
	} elsif (/link path=/) {
		# unclassified files
		print $_;
	} else {
		# unclassified files
		print $_;
	}
}

