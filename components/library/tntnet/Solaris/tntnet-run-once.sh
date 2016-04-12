#!/bin/sh

# One-time (per script instance) runner for a packaged service postinstall
# Can be re-run if an updated package delivers a different copy of this file
# Copyright (C) 2016 by Jim Klimov
# Inspired by https://docs.oracle.com/cd/E26502_01/html/E21383/smfdelivery.html
. /lib/svc/share/smf_include.sh || exit $?

[ -n "${SMF_FMRI}" ] || exit $SMF_EXIT_ERR_NOSMF

if [ "$1" = "--refresh" ]; then
    echo "`LANG=C TZ=UTC date -u`: INFO: Self-enabling to check if the $0 script is updated"
    svcadm enable "${SMF_FMRI}"
    svcadm clear "${SMF_FMRI}" 2>/dev/null
fi

script_cksum=$(/usr/bin/svcprop -p config/script_cksum "${SMF_FMRI}")
CKSUM="`cksum "$0" | awk '{print $1}'`"
if [ "$script_cksum" == "$CKSUM" ] ; then
    echo "`LANG=C TZ=UTC date -u`: INFO: Self-disabling, until the $0 script is updated and "${SMF_FMRI}" is refreshed"
    svcadm disable "${SMF_FMRI}"
    exit $SMF_EXIT_OK
fi

MKDIR() {
    OWNER="$1"
    MODE="$2"
    DIR="$3"

    [ -n "${OWNER}" ] && [ -n "${MODE}" ] && [ -n "${DIR}" ] || { \
        echo "`LANG=C TZ=UTC date -u`: ERROR: Not all needed parameters are present: got MKDIR() $*" >&2;
        exit $SMF_EXIT_ERR_FATAL; }

    mkdir -p "${DIR}" && \
    chown "${OWNER}" "${DIR}" && \
    chmod "${MODE}" "${DIR}" || \
    exit $SMF_EXIT_ERR_FATAL

    echo "`LANG=C TZ=UTC date -u`: INFO: ensured presence of directory '${DIR}' owned by '${OWNER}' with mode bits '${MODE}'"

    return 0
}

MKDIR webservd:webservd 755 /var/www
MKDIR webservd:webservd 755 /var/log/tntnet

svccfg -s "${SMF_FMRI}" setprop config/script_cksum = "$CKSUM" && \
svccfg -s "${SMF_FMRI}" refresh && \
echo "`LANG=C TZ=UTC date -u`: INFO: Left a notice for my future self to quickly not-run, unless the $0 script is updated" && \
svcadm restart "${SMF_FMRI}"
