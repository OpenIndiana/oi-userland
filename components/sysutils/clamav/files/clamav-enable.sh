#!/bin/sh

### Enable the ClamAV services including starter config files and freshclam
### Use once to enable and installed but inactive ClamAV virus toolkit in this
### local zone or host
### (C) 2016 by Jim Klimov
### $Id: clamav-enable.sh,v 1.1 2016/02/05 00:00:00 jim Exp $

CLAMD_CONFFILE=/etc/clamav/clamd.conf
CLAMMILT_CONFFILE=/etc/clamav/clamav-milter.conf
FRESHCLAM_CONFFILE=/etc/clamav/freshclam.conf
FRESHCLAM_RUNFILE="/usr/bin/freshclam.sh"

### After all, copying of configs and enablement of services should be separate:
### freshclam depends on both its config and clamd.conf, but clamd service needs
### the databases to start up...
for F in "$CLAMD_CONFFILE" "$FRESHCLAM_CONFFILE" "$CLAMMILT_CONFFILE" ; do
	S="/usr/share/clamav/`basename "$F"`.sol"
	if [ ! -s "$F" ] && [ -s "$S" ] ; then
		echo "INFO: Copying default config '$S' into active config '$F'" >&2
		cp -pf "$S" "$F"
		chown root:root "$F"
		chmod 644 "$F"
	else
		echo "INFO: Nothing to change about active config '$F'" >&2
	fi
done

for F in "$FRESHCLAM_CONFFILE" "$CLAMD_CONFFILE" "$CLAMMILT_CONFFILE" ; do
	case "$F" in
		"$FRESHCLAM_CONFFILE")
			if [ -s "$F" ]; then
				echo "INFO: Enabling service: FRESHCLAM" >&2
				[ -x "$FRESHCLAM_RUNFILE" ] && "$FRESHCLAM_RUNFILE"
				theSMF_FMRI="svc:/antivirus/freshclam:default"
				svcadm refresh "$theSMF_FMRI"
				sleep 5
				svcadm enable -s "$theSMF_FMRI" # Let initial download pass
				sleep 5
				svcadm restart "$theSMF_FMRI"
				sleep 5
				svcadm clear "$theSMF_FMRI" 2>/dev/null && sleep 5
				sleep 1
				svcs -p "$theSMF_FMRI"
			fi ;;
		"$CLAMD_CONFFILE")
			if [ -s "$F" -a -x "/usr/sbin/clamd" ]; then
				echo "INFO: Enabling service: CLAMD" >&2
				theSMF_FMRI="svc:/antivirus/clamav:default"
				svcadm refresh "$theSMF_FMRI"
				svcadm enable "$theSMF_FMRI"
				svcadm restart "$theSMF_FMRI"
				svcadm clear "$theSMF_FMRI" 2>/dev/null && sleep 5
				sleep 1
				svcs -p "$theSMF_FMRI"
			fi ;;
		"$CLAMMILT_CONFFILE")
			if [ -s "$F" -a -x "/usr/sbin/clamav-milter" ]; then
				echo "INFO: Enabling service: CLAMAV-MILTER" >&2
				theSMF_FMRI="svc:/antivirus/clamav-milter:default"
				svcadm refresh "$theSMF_FMRI"
				svcadm enable "$theSMF_FMRI"
				svcadm restart "$theSMF_FMRI"
				svcadm clear "$theSMF_FMRI" 2>/dev/null && sleep 5
				sleep 1
				svcs -p "$theSMF_FMRI"
			fi ;;
	esac
done
