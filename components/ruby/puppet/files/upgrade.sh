#!/usr/bin/bash -e
. /lib/svc/share/smf_include.sh

# Get Puppet 4 upgrade flag
PUP4_X=$(/usr/bin/svcprop -p upgrade/4.x $SMF_FMRI)

# Get list of puppet FMRIs
readarray -t PUPPET_FMRI <<< "$(svcs -H -o fmri application/puppet)"

# Properties to remove if set
PUPPET_RM_PROP=(
stringify_facts trusted_node_data allow_variables_with_dashes
async_storeconfigs binder catalog_format certdnsnames
certificate_expire_warning couchdb_url dbadapter dbconnections
dblocation dbmigrate dbname dbpassword dbport dbserver dbsocket
dbuser dynamicfacts http_compression httplog ignoreimport
immutable_node_data inventory_port inventory_server
inventory_terminus legacy_query_parameter_serialization listen
localconfig manifestdir masterlog parser preview_outputdir puppetport
queue_source queue_type rails_loglevel railslog report_serialization_format
reportfrom rrddir rrdinterval sendmail smtphelo smtpport smtpserver
stringify_facts tagmap templatedir thin_storeconfigs trusted_node_data zlib
disable_warnings classfile vardir libdir rundir confdir ssldir)

# If additional migrations are needed in the future use a new prop
# and variable for the steps
if [ "$PUP4_X" == "true" ] ; then
  exit $SMF_EXIT_OK
fi
if [ "$PUP4_X" == "false" ]; then
  echo "Updating settings for Puppet 4"
  echo "Removing Out of Date Configuration Options"
  for fmri in ${PUPPET_FMRI[@]}
  do
    for prop in ${PUPPET_RM_PROP[@]}
    do
      printf "%s: " ${fmri}/:properties/config/${prop}
      # Don't exit on error
      set +e
      tmp=$(svcprop ${fmri}/:properties/config/${prop} 2> /dev/null)
      if [ ! -z ${tmp} ]; then
        svccfg -s $fmri delprop config/${prop} > /dev/null 2>&1
        # Reset exit on error
        print "removed (${tmp})"
      else
        print "not present"
      fi
      set -e
    done
  done
fi
svccfg -s $SMF_FMRI setprop upgrade/4.x = true
svccfg -s $SMF_FMRI refresh
