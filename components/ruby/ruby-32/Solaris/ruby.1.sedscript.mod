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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#
1i\
'\\" t\
\.\\"\
\.\\" Modified for Solaris to add notes about Ruby installation locations.\
\.\\"\
$a\
\.\\" Begin Oracle update\
.SH FILES\
The following files specify the installation locations for Ruby: \
.PP\
.TP\
/usr/ruby/3.2/lib/ruby/gems/3.2 \
Contains the Rubygems repository. Configure the GEM_HOME environment variable \
to point to /usr/ruby/3.2/lib/ruby/gems/3.2 as the installation of Rubygems repository.\
.PP\
.TP\
~/.gem/ruby/3.2 \
Per user location for gems, when installing with the gem install option \
--user-install (gem install --user-install ... ).  This path is \
automatically added to GEM_PATH.\
.PP\
.TP\
~/.gem/ruby/3.2/bin\
Per user location for gem executables.\
.PP\
.TP\
/usr/ruby/3.2/bin \
Contains  the  Ruby  executable  as well as other utility programs, and \
Rubygems programs. These programs are linked from /usr/bin.\
For example: /usr/ruby/3.2/bin/ruby is linked from /usr/bin/ruby19, and \
may be linked from /usr/bin/ruby if the package mediator "ruby" is version \
"3.2" (see pkg(1)). \
Also contains executables for any installed gems that have them (i.e.: thin,\
rails, etc). \
\.\\" End Oracle update
