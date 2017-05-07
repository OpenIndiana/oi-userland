README for X11R7.7

The X.Org Foundation

April 2012

X11R7.7 is an Open Source version of the X Window System that supports many
UNIX® and UNIX-like operating systems (such as Linux, FreeBSD, NetBSD, OpenBSD,
and Solaris) on a variety of platforms. This version is compatible with X11R7.6
and other X Window System implementations which support the X11 standard.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Table of Contents

What is X11R7.7?
Licensing
Pointers to additional information
The Public Mailing Lists
Contributing to the X.Org Foundation's X efforts.
How to get the release

    X11R7.7
    The current development tree

Reporting Bugs

What is X11R7.7?

X11R7.7 is the eighth release in the X11R7 series.

Specific release enhancements can be viewed in the Release Notes.

Most modern PC video hardware is supported in this release, and most PC video
hardware that isn't supported explicitly can be used with the "vesa" driver.
The Release Notes has a table showing the drivers provided with X11R7.7, and
links to related documentation.

The X.Org Foundation X releases are produced by the X.Org Foundation. The X.Org
Foundation has been formed as a Delaware corporation organized to operate as a
scientific charity under IRS code 501(c)(3) chartered to develop and execute
effective strategies which provide world-wide stewardship of the X Window
System technology and standards. Membership in the X.Org Foundation is free to
all participants. Applications for Membership are now being accepted, and
active participants in the further development of the X Window Technology are
invited to complete a membership application. The X11R7.7 release has been
produced by the many contributors to the X.Org community and members of the
X.Org Foundation and includes code from the X Consortium, the Open Group and
the XFree86® Project. This release is dedicated to the greater X community,
developers and users alike.

Licensing

X Window System source code is covered by many licenses. All of these licenses
have in common the fact that they do not impose significant conditions on the
modification or redistribution or either source code or binaries beyond
requiring one or more of the following:

 1. Copyright and/or license notices are left intact.

 2. Copyright and/or license notices are reproduced verbatim in documentation
    accompanying binary distributions.

 3. Attributions are included with documentation accompanying binaries.

Most of these licenses are based on the MIT, X Consortium, or BSD (original and
revised) licenses. All of them are consistent with the Open Source Definition,
and most are consistent with the Free Software Foundation's Free Software
Definition.

Copyright and Licensing information for X, including the reproduction of
copyright and/or license notices and attributions required by some of the
licenses for binary distributions, can be found in the License Document. If you
find any omissions in that document, please contact us with details at <
xorg@lists.x.org>. While the current licenses are all open source licenses, the
X.Org Foundation is attempting, with time, to bring as much as possible of the
code's licenses in the distribution into compliance with the Debian Free
Software Guidelines.

Pointers to additional information

The documentation for this release can be found online at the X.Org web site.

The X11 version numbering system (including historical information) can be
found in the Versions Document.

Additional information may be available at the X.Org Foundation Wiki.

The Public Mailing Lists

Current information about the X.Org Foundation public mailing lists is
available on the X.Org mailing list page and related desktop technology mailing
lists can be found on Freedesktop.org's mailing list page.

Contributing to the X.Org Foundation's X efforts.

If you have any new work or enhancements/bug fixes for existing work, please
send them as git format patches to <xorg-devel@lists.freedesktop.org> or to our
bug tracking system using the xorg component. This will help ensure that they
are included in future releases. More details on patch submission and review
process are available on the SubmittingPatches page of the X.Org wiki.

How to get the release

Information about X11R7.7 can be found from the X.Org Foundation wiki, and at
mirrors of this server.

X11R7.7

This is the eighth release of the new modular source code tree. The source code
has been split into nine logical modules: app, data, doc, driver, font, lib.
proto, util and xserver. Each of these modules contain one or more packages
that can be configured, built and installed separately. Please see an X11R7.7
release site for a complete list of the tarballs.

For information on how to build the modular tree packages see the Modular
Developer's Guide. This guide also contains information for developers who want
to help improve the modular build system and modular code base.

The current development tree

The X source code for this and all releases/snapshots as well as development
versions can also be accessed via the Freedesktop.org git repository. It's also
possible to browse the freedesktop git repository.

To check out the latest development version, don't specify any tag.

Reporting Bugs

Bugs should be reported to freedesktop.org's bug tracking system using the xorg
component. Before reporting bugs, please check the server log file, which can
be found at /var/log/Xorg.0.log on most platforms. If you can't resolve the
problem yourself, send the entire log file with your bug report but not the
operating system core dump. Do not edit the log file as our developers use it
to reproduce and debug your problem. Please attach it to your bug report.

