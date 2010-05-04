#
# Default settings for GNOME packages on Solaris
#
# Copyright 2009 Sun Microsystems, Inc.
#
SUNW_ProdName:             GNOME
SUNW_ProdVers:             2.29.91

%define default_pkg_version 2.29.91
%define default_python_version 2.6

%{?sf_download:#}%define sf_download http://downloads.sourceforge.net

%{?jds_version:#}%define jds_version JDSosol
%define default_category   GNOME2,application,%{jds_version}
%{?support_level:#}%define support_level      unsupported

Vendor:			   Sun Microsystems, Inc.

%define                    pkg_prefix SUNW

%define                    restart_fmri $BASEDIR/share/desktop-cache/restart_fmri

# ChangeLog:
# 2009-10-08  Laszlo (Laca) Peter  <laca@sun.com>
# - define default_python_version
# 2009-04-03  Laszlo (Laca) Peter  <laca@sun.com>
# - define restart_fmri
# 2007-09-27  Laszlo (Laca) Peter  <laca@sun.com>
# - move tjds build option to options.inc
# 2007-03-15  Laszlo (Laca) Peter  <laca@sun.com>
# - create by moving product specific stuff out of Solaris.inc
