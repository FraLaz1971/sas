#! /usr/bin/rpm
Version: 2.0.9
Release: 1
Name: 	 rlmm
Summary: C++ classes that wrap the readline library
Group:   Development/Libraries
License: LGPL
Source0: http://cern.ch/cholm/cgi-bin/download?File=misc/rlmm-%{version}.tar.gz
Prefix: %{_prefix}
Url:    http://cholm.home.cern.ch/cholm/misc/#rlmm
BuildRoot: %{_tmppath}/%{name}-%{version}-root

%description
This package implements a full GNU Readline interface in C++. The API is quite simple and makes heavy use of templated container, standard classes and so on. The idea is that a C++ developer should fell resonabily comfortable with the library API.

%prep
%setup

%build
%configure --enable-termcap --enable-curses
make

%install
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%pre
ldconfig

%post
ldconfig

%files
%defattr(-,root,root)
/usr

%changelog
* Wed Aug 23 2005 Christian Holm <cholm@nbi.dk> 1.2
 - Spec file generated by configure

* Thu Jan 20 2005 Karl Grindley <kgrindley@ll.mit.edu> 1.1
 - initial spec buildout
