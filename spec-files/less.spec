#
# spec file for package less
#
# includes module(s): less
#
%include Solaris.inc

%define	src_name less
%define src_url http://src.opensolaris.org/source/raw/sfw/usr/src/cmd

# The system doesn't support package names such as:
# text/less

Name:                less
Summary:             less - opposite of more
License:             GPL
Group:               Editor
Distribution:        OpenSolaris
Version:             436
Source:              %{src_url}/%{src_name}/%{src_name}-%{version}.tar.gz
SUNW_BaseDir:        %{_basedir}
SUNW_Copyright:      %{name}.copyright
BuildRoot:           %{_tmppath}/%{name}-%{version}-build
%include default-depend.inc

# OpenSolaris IPS Manifest Fields
Meta(info.upstream):            Less Person
Meta(info.maintainer):          Less Maintainer 
Meta(info.repository_url):      svn://svn.example.org/less/trunk
Meta(pkg.summary):              The GNU pager (less)

%description
Less is a program similar to more (1), but which allows backward
movement in the file as well as forward movement.

# Examples only:
Requires:            SUNWglib2
BuildRequires:       SUNWglib2-devel

%prep
%setup -q -n %{src_name}-%version

%build
sh configure
make

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
rm -f $RPM_BUILD_ROOT%{_libdir}/lib*.*a

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr (-, root, bin)
%dir %attr (0755, root, bin) /usr/local
/usr/local/bin/*
%dir %attr (0755, root, sys) /usr/local/share
/usr/local/share/man/*

%changelog
* Thu 7 April 2010 - Michal.Pryc@Oracle.Com
- Initial spec
