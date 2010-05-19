#
# spec file for package lcms
#
%include Solaris.inc
%define	src_name lcms
%define src_url http://download.sourceforge.net/project/lcms/lcms/

# The system doesn't support package names such as:
# text/less

Name:                lcms
Summary:             An open source color management engine
License:             GPL
Group:               Utilities
Distribution:        OpenSolaris
Version:             2-2.0a
Source:              %{src_url}/2.0/%{src_name}%{version}.tar.gz
SUNW_BaseDir:        %{_basedir}
SUNW_Copyright:      %{name}.copyright
BuildRoot:           %{_tmppath}/%{name}-%{version}-build
%include default-depend.inc

# OpenSolaris IPS Manifest Fields
Meta(info.upstream):            Marti Maria
Meta(info.maintainer):          Marti Maria
Meta(info.repository_url):      http://www.littlecms.com/
Meta(pkg.summary):              open source color management engine

%description
Little CMS intends to be a small-footprint color management engine, 
with special focus on accuracy and performance.

# Examples only:
Requires:            SUNWglib2
BuildRequires:       SUNWglib2-devel

%prep
%setup -q -n %{src_name}-2.0

%build
CPUS=`/usr/sbin/psrinfo | grep on-line | wc -l | tr -d ' '`
if test "x$CPUS" = "x" -o $CPUS = 0; then
  CPUS=1
fi
./configure --prefix=%{_prefix} \
            --libdir=%{_libdir} \
            --bindir=%{_bindir} \
            --datadir=%{_datadir}
make -j $CPUS

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
#rm -rf $RPM_BUILD_ROOT

%files
%{_bindir}/*
%{_libdir}/*
%{_datadir}/*
%{_includedir}/*

%changelog
Wed 19 May 2010 erwann.chenede@sun.com
- Initial spec
