#! /bin/sh

# Import SMF routines
. /lib/svc/share/smf_include.sh

# SMF_FMRI is the name of the target service. This allows multiple instances
# to use the same script.

getproparg() {
        val=`svcprop -p $1 $SMF_FMRI`
        [ -n "$val" ] && echo $val
}

SBSBINDIR=`getproparg lmsd/bindir`
CACHEDIR=`getproparg lmsd/cachedir`
PREFSDIR=`getproparg lmsd/prefsdir`
LOGDIR=`getproparg lmsd/logdir`
TRANSCODING=`getproparg lmsd/transcoding`
SB1SLIMP3SYNC=`getproparg lmsd/sb1slimp3sync`
MYSQUEEZEBOX=`getproparg lmsd/mysqueezebox`
INFOLOG=`getproparg lmsd/infolog`
DEBUGLOG=`getproparg lmsd/debuglog`
WEBGUI=`getproparg lmsd/webgui`
PERFMON=`getproparg lmsd/perfmon`
DIAG=`getproparg lmsd/diag`
HTTPPORT=`getproparg lmsd/httpport`
HTTPADDR=`getproparg lmsd/httpaddr`
CLIPORT=`getproparg lmsd/cliport`
CLIADDR=`getproparg lmsd/cliaddr`
IMAGE=`getproparg lmsd/image`
VIDEO=`getproparg lmsd/video`
DBTYPE=`getproparg lmsd/dbtype`
PERLBIN=`getproparg lmsd/perlbin`

PIDFILE=${CACHEDIR}/lmsd.pid

ARGS="--daemon"

if [ -z $SMF_FMRI ]; then
        echo "SMF framework variables are not initialized."
        exit $SMF_EXIT_ERR
fi

if [ -z ${SBSBINDIR} ]; then
        echo "squeezed/bindir property not set"
        exit $SMF_EXIT_ERR_CONFIG
fi

if [ "${TRANSCODING}" == "false" ]; then
        ARGS="${ARGS} --notranscoding"
fi

if [ "${SB1SLIMP3SYNC}" == "false" ]; then
        ARGS="${ARGS} --nosb1slimp3sync"
fi

if [ "${MYSQUEEZEBOX}" == "false" ]; then
        ARGS="${ARGS} --nomysqueezebox"
fi

if [ "${INFOLOG}" == "false" ]; then
        ARGS="${ARGS} --noinfolog"
fi

if [ "${DEBUGLOG}" == "false" ]; then
        ARGS="${ARGS} --nodebuglog"
fi

if [ "${WEBGUI}" == "false" ]; then
        ARGS="${ARGS} --nowebgui"
fi

if [ "${PERFMON}" == "true" ]; then
        ARGS="${ARGS} --perfmon"
fi

if [ "${DIAG}" == "true" ]; then
        ARGS="${ARGS} --diag"
fi

if [ "${IMAGE}" == "false" ]; then
        ARGS="${ARGS} --noimage"
fi

if [ "${VIDEO}" == "false" ]; then
        ARGS="${ARGS} --noimage"
fi

if ! [ "${HTTPADDR}" == "0.0.0.0" ]; then
        ARGS="${ARGS} --httpaddr=$HTTPADDR"
fi

if ! [ "${HTTPPORT}" == "9000" ]; then
        ARGS="${ARGS} --httpport=$HTTPPORT"
fi

if ! [ "${CLIADDR}" == "0.0.0.0" ]; then
        ARGS="${ARGS} --cliaddr=$CLIADDR"
        ARGS="${ARGS} --cliaddr=$CLIADDR"
fi

if ! [ "${CLIPORT}" == "9090" ]; then
        ARGS="${ARGS} --cliport=$CLIPORT"
fi

ARGS="${ARGS} --cachedir=${CACHEDIR} --prefsdir=${PREFSDIR} --logdir=${LOGDIR} --pidfile=${PIDFILE} --dbtype=${DBTYPE}"

# Define start, stop, restart and refresh event
case "$1" in
'start')
        echo "Starting ${SBSBINDIR}/slimserver.pl ${ARGS}"
        ${PERLBIN} ${SBSBINDIR}/slimserver.pl ${ARGS}
        ;;

'stop')
        if test '!' -f $PIDFILE ; then
                echo "$PIDFILE doesn't exist, perhaps LMS isn't running"
        else
                # exec the kill to get the correct return code
                exec kill -TERM `cat $PIDFILE`
        fi
        ;;

'restart')
        stop
        wait 15
        start
        ;;

'refresh')
        stop
        wait 15
        start
        ;;

*)
        echo $"Usage: $0 {start|stop|restart}"
        exit 1
        ;;
esac
exit ${SMF_EXIT_OK}

