#!/bin/sh

if [ -f $HOME/.config/user-dirs.dirs ] ; then
    . $HOME/.config/user-dirs.dirs
    DESKTOP_DIR="$XDG_DESKTOP_DIR"
fi

DESKTOP_DIR=${DESKTOP_DIR:-"$HOME/Desktop"}
MARKER_DIR="$DESKTOP_DIR"
MARKER=".os-icons-installed"
APPDIR=/usr/share/applications
DESKTOP_FILES="addmoresoftware.desktop os-next-steps.desktop"
ADDMORESOFTWARE="addmoresoftware.desktop"

/bin/mkdir -p "$MARKER_DIR"

if [ ! -f "$MARKER_DIR/$MARKER" ]; then
    /bin/mkdir -p "$DESKTOP_DIR"
    for dtfile in $DESKTOP_FILES; do
        if [ -f "$APPDIR/$dtfile" ] ; then
            /bin/cp "$APPDIR/$dtfile" "$DESKTOP_DIR"
        fi
        /bin/chmod u+w "$DESKTOP_DIR/$dtfile"
        /bin/chmod a+x "$DESKTOP_DIR/$dtfile"
    done
    /bin/mkdir -p "$MARKER_DIR"
    /bin/touch "$MARKER_DIR/$MARKER"
else
    apptime=`stat --format=%Y $APPDIR/$ADDMORESOFTWARE`
    desktoptime=`stat --format=%Y $DESKTOP_DIR/$ADDMORESOFTWARE`
    if [ $apptime -gt $desktoptime ] ; then
        /bin/cp "$APPDIR/$ADDMORESOFTWARE" "$DESKTOP_DIR"
        /bin/chmod u+w "$DESKTOP_DIR/$ADDMORESOFTWARE"
        /bin/chmod a+x "$DESKTOP_DIR/$ADDMORESOFTWARE"
    fi
fi

