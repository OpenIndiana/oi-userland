SUBDIRS = src data po help

desktopdir = $(datadir)/applications
desktop_in_files = imf-selector.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@


EXTRA_DIST = \
	autogen.sh \
	OPENSOLARIS.LICENSE \
	$(desktop_in_files)

DISTCLEANFILES = \
	$(desktop_DATA)

