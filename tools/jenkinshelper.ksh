#!/bin/ksh
# 2021-04-07 Olaf Bohlen <olbohlen@eenfach.de>
# instead of putting all this into the Jenkinsfile I decided to put the actual code in this script

# global config
HTTPCONF="/etc/apache2/2.4/conf.d/pkgdepotd.conf"

# just run prepare once to initially set up the environment
# this must be run as root
prepare() {
    echo "jenkinshelper: preparing..."
    pkg install web/server/apache-24
    mkdir -p /etc/apache2/2.4/conf.d && chown root:sys /etc/apache2/2.4/conf.d
    grep "#ProxyPassMatch /default/(.*)\$ http://127.0.0.1:10000/\$1 nocanon max=200" "${HTTPCONF}" >/dev/null 2>&1
    if [ $? -gt 0 ]; then
	echo "jenkinshelper: Initializing a new apache config at ${HTTPCONF}"
	echo "#ProxyPassMatch /default/(.*)\$ http://127.0.0.1:10000/\$1 nocanon max=200" >"${HTTPCONF}"
    else
	echo "jenkinshelper: Preserving an existing ${HTTPCONF}"
    fi

    cat >/etc/apache2/2.4/conf.d/00-proxy.conf <<EOF
LoadModule proxy_module libexec/mod_proxy.so
LoadModule proxy_connect_module libexec/mod_proxy_connect.so
LoadModule proxy_ftp_module libexec/mod_proxy_ftp.so
LoadModule proxy_http_module libexec/mod_proxy_http.so
LoadModule proxy_ajp_module libexec/mod_proxy_ajp.so

ProxyRequests Off
ProxyVia Off
ProxyPreserveHost on
RequestHeader unset Origin
AllowEncodedSlashes NoDecode
EOF
    
    chown root:builders "${HTTPCONF}"
    chmod 664 "${HTTPCONF}"
    svcadm enable svc:/network/http:apache24
}

# setup oi-userland
stage_setup() {
    if [ ! -f /etc/apache2/2.4/conf.d/00-proxy.conf ]; then
	echo "jenkinshelper: aborting, please run \"jenkinshelper -p\" initially as root on this jenkins instance once"
	exit 1
    fi
    echo "jenkinshelper: running gmake setup"
    gmake setup
}

# scan the git log for changed components
# we try to be smart and assume that all updates will always touch
# the components Makefile also (to update COMPONENT_REVISION, etc)
stage_build_changed() { 
    for f in $(git diff --name-only HEAD..origin/oi/hipster | grep Makefile); do
	echo "jenkinshelper: building for ${f%/*}..."
	curpwd=$(pwd)
	cd "${f%/*}" && gmake publish
        rc=$?
	cd "${curpwd}"
	echo "jenkinshelper: done with ${f%/*} return code ${rc}"
    done
}

# prepare the pkg.depotd server instance, if an instance already
# exists for this branch, we will use that - otherwise create a
# fresh one
stage_prepare_pkgdepotd()
{
    # we need the platform for the path to the repo
    platform=$(uname -p)

    # check if we already have this branch set up as a pkg.depotd:
    if ! "svcs pkg/server:${BRANCH_NAME}" >/dev/null 2>&1; then

	# get highest port from ${HTTPCONF} to figure out the next free one
	nextport=$(( $(nawk -F '[/:]' '{ print $7 }' < "${HTTPCONF}" | sort -n | tail -1) + 1 ))
	
	# set-up a new pkg/server instance
	svccfg -s pkg/server <<EOF
add ${BRANCH_NAME}
select ${BRANCH_NAME}
addpg pkg application
setprop pkg/port=${nextport}
setprop pkg/readonly=true
setprop pkg/pkg_root=/
setprop pkg/inst_root=${WORKSPACE}/${platform}/repo
setprop pkg/proxy_base=${JENKINS_URL%:[0-9]*/}/${BRANCH_NAME}/
end
EOF

	# enable the new pkg/server instance
	svcadm enable pkg/server:${BRANCH_NAME}
	
	# add the new proxy rule to our apache config
	echo "ProxyPassMatch /${BRANCH_NAME}/(.*)\$ http://127.0.0.1:${nextport}/\$1 nocanon max=200" >> "${HTTPCONF}"

	fi

    # we need to refresh the repo:
    pkgrepo refresh -s ${WORKSPACE}/${platform}/repo

    # also restarting pkg.depotd does not hurt
    svcadm restart pkg/server:${BRANCH_NAME}
    
    # graceful restart apache to reload config
    svcadm refresh svc:/network/http:apache24
}

usage() {
    cat <<EOF
Usage:
jenkinshelper.ksh [ -h | -p | -s <stage> ]
		  -h    show this help
		  -p    run only ONCE to initialize your environment
		  -s    followed by the stage to run, currently:
		        setup, build_changed, prepare_pkgdepotd
EOF
exit 0
}

## MAIN ##
# call this script with the stage as an argument to -s

while getopts s:hp argv
do
    case ${argv} in
	s)         stage="stage_${OPTARG}";;
	p)         stage="prepare";;
        h)         usage;;
    esac
done
shift `expr ${OPTIND} - 1`

# run requested stage
rt=0
${stage} || rt=$?

# we are done
exit ${rt}
