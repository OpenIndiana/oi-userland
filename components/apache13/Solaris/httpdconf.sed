#ident	"@(#)httpdconf.sed	1.11	10/01/14 SMI"
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
# Copyright 2010 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.

/^# the directives/a\
#\
# Solaris Quick Configuration Information\
#\
# 1. Set ServerName if necessary (default is 127.0.0.1)\
# 2. Set ServerAdmin to a valid email address\
# 3. If configuring Jserv or Tomcat, read comments at\
#    the bottom of this file.\
#
s/\/usr\/apache\/conf/\/etc\/apache/g
/^ServerAdmin/c\
ServerAdmin you@yourhost.com
/^#ServerName/c\
ServerName 127.0.0.1
/^ServerName/c\
ServerName 127.0.0.1
/^Group/c\
Group nobody
/^LoadModule auth_module/a\
LoadModule auth_gss_module	libexec/mod_auth_gss.so
/^AddModule mod_auth.c/a\
AddModule mod_auth_gss.c
/^<IfModule mod_alias.c>/a\
\
Alias /manual/ "/usr/apache/htdocs/manual/"\
<Directory "/usr/apache/htdocs/manual" >\
    Options Indexes FollowSymLinks MultiViews\
    AllowOverride None\
</Directory>
/^SSLCipherSuite/c\
# AES with keylengths > 128 bit is not supported by default on Solaris\
# to operate with AES256 you must install the SUNWcry and SUNWcryr\
# packages from the Solaris 10 Data Encryption Kit.\
SSLCipherSuite ALL:!ADH:!EXPORT56:-AES256-SHA:-DHE-RSA-AES256-SHA:-DHE-DSS-AES256-SHA:RC4+RSA:+HIGH:+MEDIUM:+LOW:+SSLv2:+EXP:+eNULL\

$a\
\
#<IfModule mod_perl.c>\
#\
#<Location /perl-status>\
#     SetHandler perl-script\
#     PerlHandler Apache::Status\
#     order deny,allow\
#     deny from all\
#     allow from yourhost\
#</Location>\
#</IfModule>\
\
# Apache Tomcat support\
#include /etc/apache/jk.conf
