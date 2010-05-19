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
# Copyright 2010 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# include global definitions
include ../Makefile.component

PACKAGES=file
SRC=file-5.04
VERSION=5.0.4
SRC_LOC=ftp://ftp.fu-berlin.de/unix/tools/file
TARBALL=$(SRC).tar.gz
TARBALL_CHECKSUM=56ddf7135471aa656334ed8fefe1112bcccc2cc3
PATH=/usr/bin:/usr/gnu/bin
BUILD_PKG_DEPENDENCIES= make \
	                wget \
			gnu-coreutils \
			$(C_COMPILER) \
			gnu-grep \
			developer/object-file

build:  unpack
	$(MAKE) check_dependencies
	export DESTDIR=`pwd`/proto; cd $(SRC); \
	    export PATH=$(PATH); \
	    ./configure --prefix=/usr --exec-prefix=/usr; \
            make; make check; make install
	touch build

package: build
	# generate a manifest of what is in the proto area
	pkgsend generate proto > tmp.1
	# drop those things we're not going to ship
	pkgmogrify tmp.1 file.raw.drops > tmp.2
	# generate and resolve dependencies
	pkgdepend generate -m tmp.2 proto > tmp.3
	pkgdepend resolve -m tmp.3
	# cleanup dependencies, add headers, expand macros
	pkgmogrify $(PKGMOGRIFY_MACROS:%=-D %) \
            ../../transforms/remove_dependency_versions \
            ../../transforms/actuators tmp.3.res file.cleanup  > tmp.4
	# prepare comparison manifest
	pkgmogrify $(PKGMOGRIFY_MACROS:%=-D %) \
            ../../transforms/remove_dependency_versions \
            ../../transforms/actuators file.mf > file.cmp
	# prepare publication manifest
	pkgmogrify $(PKGMOGRIFY_MACROS:%=-D %) \
            ../../transforms/remove_dependency_versions \
            ../../transforms/actuators file.mf > file.publish
	# check for differences
	pkgdiff file.cmp tmp.4	
	# publish
	pkgsend -s $(REPO) publish --fmri-in-manifest -d proto file.publish

$(TARBALL):
	wget $(SRC_LOC)/$(SRC).tar.gz
	printf "%s  %s\n" $(TARBALL_CHECKSUM) $(TARBALL) | sha1sum -c 

unpack: $(TARBALL)
	gunzip < $(SRC).tar.gz | tar xf -
	touch unpack

clean:	
	rm -fr $(SRC) build file.new tmp.* file.publish file.cmp proto unpack

clobber: clean
	rm $(TARBALL)

