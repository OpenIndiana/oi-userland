#!/bin/sh

### Startup for COSclamav package
### (C) 2008-2016 by Jim Klimov, COS&HT
### $Id: freshclam.sh,v 1.6 2016/02/22 20:40:00 jim Exp $

### Use to update ClamAV virus signatures from cron:
### 0,15,30,45 * * * *       [ -x /usr/bin/freshclam.sh ] && /usr/bin/freshclam.sh

CLAMD_CONFFILE=/etc/clamav/clamd.conf
FRESHCLAM_CONFFILE=/etc/clamav/freshclam.conf
FRESHCLAM_BINFILE="/usr/bin/freshclam"

### Clumsy syntax due to portable shells:
FRESHCLAMSH_BINFILE_DIR="`dirname "$0"`" && \
FRESHCLAMSH_BINFILE_DIR="`cd "$FRESHCLAMSH_BINFILE_DIR" && pwd`" && \
FRESHCLAMSH_BINFILE="$FRESHCLAMSH_BINFILE_DIR/`basename "$0"`" && \
[ x"$FRESHCLAMSH_BINFILE" != x ] && [ -x "$FRESHCLAMSH_BINFILE" ] || \
FRESHCLAMSH_BINFILE="/usr/bin/freshclam.sh"

STATUS_LINES=100

PATH=/usr/bin:/bin:/usr/sbin:/bin:$PATH
export PATH

LD_LIBRARY_PATH=\
/usr/lib:/lib:/usr/ssl/lib:\
/usr/sfw/lib:/opt/sfw/lib:\
/usr/gnu/lib:/opt/gnu/lib:\
$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

if [ ! -s "$CLAMD_CONFFILE" -o ! -s "$FRESHCLAM_CONFFILE" ]; then
	# echo "ClamAV-FreshCLAM: No config file!" >&2
	exit 0
fi

adderror() {
	BUF_ERROR="$BUF_ERROR
$1"
	[ x"$RES" = x0 ] && RES="$2"
	[ "$RES_MAX" -lt "$2" ] && RES_MAX="$2"
}

do_delcron() {
	( which crontab >/dev/null 2>&1 ) || \
		{ echo "ERROR: crontab program not found" >&2; return 1; }
	RES=0

	# Below we depend on parsing some outputs
	LC_ALL=C
	LANG=C
	export LC_ALL LANG

	OUT="`crontab -l 2>&1`" || RES=$?
	[ $RES != 0 ] && \
	if	echo "$OUT" | grep "can't open" >/dev/null && \
		[ "`echo "$OUT" | wc -l`" -eq 1 ] \
	; then OUT="" ; RES=0; else return $RES; fi
	echo "$OUT" | egrep -v "bin/freshclam|$FRESHCLAMSH_BINFILE|^$" > "/tmp/saved-crontab.$$"
	if [ -s "/tmp/saved-crontab.$$" ]; then
		crontab "/tmp/saved-crontab.$$" || RES=$?
	else
		crontab -r || RES=$?
	fi
	rm -f "/tmp/saved-crontab.$$"
	[ $RES != 0 ] && echo "ERROR: could not delete freshclam from crontab" >&2
	return $RES
}

do_addcron() {
	[ x"$1" = x ] && return 1   # Whole cron-schedule spec
	do_delcron || return $?  # Also checks for valid crontab program in PATH

	# Below we depend on parsing some outputs
	LC_ALL=C
	LANG=C
	export LC_ALL LANG

	if [ "$1" = SMF ]; then
		[ -n "$SMF_FMRI" ] && \
		SCHED="`/usr/bin/svcprop -p freshclam/cron-schedule "$SMF_FMRI"`" \
			&& [ -n "$SCHED" ] || return $?
	else
		SCHED="$1"
	fi
	# SMF escapes our schedule... and shell too...
	SCHED="`echo "$SCHED" | sed 's,\\\\ , ,g'`"
	OUT="`crontab -l 2>/dev/null`" || OUT=""
	echo "$OUT
$SCHED	[ -x '$FRESHCLAMSH_BINFILE' ] && '$FRESHCLAMSH_BINFILE'" > "/tmp/saved-crontab.$$"
	RES=0
	crontab "/tmp/saved-crontab.$$" || RES=$?
	rm -f "/tmp/saved-crontab.$$"
	[ $RES != 0 ] && echo "ERROR: could not add freshclam to crontab" >&2
	return $RES
}

case "$1" in
	--smf-enable) # Initial refresh and a cronjob (with schedule in $2)
		[ -x "$FRESHCLAM_BINFILE" ] && "$FRESHCLAM_BINFILE"
		do_addcron "SMF"
		;;
	--add-cron) # For CLI user and SMF integration
		[ x"$2" = x -o $# != 2 ] && \
			echo "ERROR: Option $1 requires a cron-schedule 5-token argument like '0 * * * *'" >&2 && \
			exit 1
		do_addcron "$2"
		exit $?
		;;
	--del-cron) # For CLI user and SMF integration
		do_delcron
		exit $?
		;;
	status)	### Use "status nowarn" to not return errors for warnings only.
		### Use "status nowarnobs" to not return errors for warnings
		### and obsolete databases only.
		[ x"$2" != x ] && [ "$2" -gt 10 ] && STATUS_LINES="$2"
		LOGFILE="`egrep '^[^#]*UpdateLogFile ' $FRESHCLAM_CONFFILE | awk '{print $NF }'`"
		if [ x"$LOGFILE" = x -o ! -f "$LOGFILE" ]; then
			echo "ClamAV-FreshCLAM: No log file ($LOGFILE)!" >&2
			exit 1
		fi

		BUF_ERROR=""
		BUF_START=""
		RES=0
		RES_MAX=0
		tail -"$STATUS_LINES" "$LOGFILE" | ( while read LINE; do
			case "$LINE" in
			ClamAV\ update\ process\ started\ at*)
				BUF_ERROR=""
				RES=0
				RES_MAX=0
				BUF_START="$LINE"
				;;
			*connect\ timing\ out*|*Can?t\ connect\ to*)
				adderror "$LINE" 10 ;;
			*node\ name\ or\ service\ name\ not\ known*)
				adderror "$LINE" 11 ;;
			Update\ failed*)
				adderror "$LINE" 12 ;;
			*Your\ ClamAV\ installation\ is\ OUTDATED*)
				adderror "$LINE" 3 ;;
			WARNING*)
				adderror "$LINE" 2 ;;
			esac
		done
		if [ x"$RES" != x0 ]; then
			[ x"$BUF_START" != x ] && echo "$BUF_START" >&2
			echo "$BUF_ERROR" >&2
			if [ x"$2" = xnowarn -a "$RES_MAX" -le 2 ]; then
				echo "Status: WARN"
				RES=0
			else
				if [ x"$2" = xnowarnobs -a "$RES_MAX" -le 3 ]; then
				echo "Status: WARN"
					RES=0
				else
				echo "Status: FAIL"
				fi
			fi
		else
			echo "Status: OK"
		fi
		exit $RES )
		;;
	*) # Wrapper for the program
		[ -x "$FRESHCLAM_BINFILE" ] && "$FRESHCLAM_BINFILE" "$@"
		;;
esac

