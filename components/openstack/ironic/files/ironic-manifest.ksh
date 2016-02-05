#!/bin/ksh93

# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License"); you may
#    not use this file except in compliance with the License. You may obtain
#    a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
#    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
#    License for the specific language governing permissions and limitations
#    under the License.

# The default AI manifest is a Derived Manifest (DM) script. The
# script creates a temp file from xml within the script, loads that
# file in as the manifest then replaces the source to be a specific
# archive specified for this client. 

SCRIPT_SUCCESS=0
SOLPKG="entire"
DEFAULT_SERVER_PKG="pkg:/group/system/solaris-large-server"
TMPFILE=`/usr/bin/mktemp /tmp/default.xml.XXXXXX`

#
# create_xml_file
# Create xml tmp file from here document. The contents of the
# here document are inserted during installadm create-service.
#
function create_xml_file
{
  # Create xml tmp file using this AI Clients default.xml as a base
  /usr/bin/cat /usr/share/auto_install/default.xml > $TMPFILE
}

#
# error_handler
# Error handling function
#
function error_handler
{
  exit $?
}

#
# load_xml
# Load the default manifest from previously created tmp file
#
function load_xml
{
  # load the default manifest
  trap error_handler ERR
  /usr/bin/aimanifest load $TMPFILE
  trap - ERR
}

#
# validate_entire
# Update the manifest entry of the Solaris consolidation package
# so that the build of Solaris being installed is the same as
# that running on the client.
# Remove all packages other than the Solaris consolidation package.
#
function validate_entire
{
  # Override SI_SYSPKG using exact version from the client
  SI_SYSPKG=$(/usr/bin/pkg info ${SOLPKG} | /usr/bin/nawk '/FMRI:/{print $2}')
  if [ -z ${SI_SYSPKG} ]; then
    echo "'${SOLPKG}' package not found on system"
    echo "Unable to constrain Solaris version being installed."
    SI_SYSPKG="pkg:/$SOLPKG"
  fi

  # Get IPS software_data path
  software_data=$(/usr/bin/aimanifest get -r \
    /auto_install/ai_instance/software[@type="IPS"]/software_data[@action="install"] \
    2> /dev/null)
  software_data_path=($(echo ${software_data} | /usr/bin/nawk '{print $2}'))

  # Clear out packages adding back just $SOLPKG
  echo "Removing all packages"
  /usr/bin/aimanifest delete ${software_data_path}/name
  echo "Adding Solaris consolidation package ${SI_SYSPKG}"
  /usr/bin/aimanifest add ${software_data_path}/name ${SI_SYSPKG}
}

#
# Validate one of solaris-small-server or solaris-larger-server
# packages are present in the manifest, adding default solaris-large-server
# if neither are present.
function validate_server_pkgs
{
  # Get list of pkgs to install from the manifest
  pkgs=$(/usr/bin/aimanifest get -r \
    /auto_install/ai_instance/software[@type="IPS"]/software_data[@action="install"]/name \
    2> /dev/null)
  # array will be formatted as:  <pkg>  <aimanifest path>...
  array=($(echo ${pkgs} | /usr/bin/nawk 'BEGIN{FS="\n"} {print $NF}'))

  idx=0
  pkg_found=0
  while [ $idx -lt ${#array[@]} ]; do
    pkgname=${array[$idx]}
    path=${array[$idx+1]}

    # check if pkgname is large|small server
    echo $pkgname | /usr/bin/egrep -s "solaris-(large|small)-server"
    if [ $? -eq 0 ]; then
      pkg_found=1
      break
    fi
    # look at next pkg
    (( idx=idx+2 ))
  done

  if [ $pkg_found -eq 0 ]; then
    # Add solaris-large-server
    # Get IPS software_data path
    software_data=$(/usr/bin/aimanifest get -r \
      /auto_install/ai_instance/software[@type="IPS"]/software_data[@action="install"] \
      2> /dev/null)
    software_data_path=($(echo ${software_data} | /usr/bin/nawk '{print $2}'))

    echo "Adding default server package ${DEFAULT_SERVER_PKG}"
    /usr/bin/aimanifest add ${software_data_path}/name ${DEFAULT_SERVER_PKG}
  fi
}

#
# add_publishers
# Add publishers to the software source section
#
function add_publishers
{
  publishers=$1

  # publishers is plus(+) delimited list, split it into an array
  OLDIFS=$IFS
  IFS="+"
  set -A pub_list ${publishers}
  IFS=$OLDIFS

  # Get IPS software paths
  software=$(/usr/bin/aimanifest get -r \
    /auto_install/ai_instance/software[@type="IPS"] \
    2> /dev/null)
  software_path=($(echo ${software} | /usr/bin/nawk '{print $2}'))

  software_source=$(/usr/bin/aimanifest get -r \
    ${software_path}/source 2> /dev/null)
  software_source_path=($(echo ${software_source} | /usr/bin/nawk '{print $2}'))

  software_publishers=$(/usr/bin/aimanifest get -r \
    ${software_source_path}/publisher 2> /dev/null)

  # Save list existing publisher names and associated origins
  pub_array=($(echo ${software_publishers} | /usr/bin/nawk \
    'BEGIN{FS="\n"} {print $NF}'))
  pub_idx=0
  idx1=0
  while [ $idx1 -lt ${#pub_array[@]} ]; do
    pub=${pub_array[$idx1+1]}
    pub_name=$(/usr/bin/aimanifest get ${pub}@name 2> /dev/null)
    origins=$(/usr/bin/aimanifest get -r ${pub}/origin 2> /dev/null)

    publisher=${pub_name}

    idx2=0
    origin_array=($(echo ${origins} | /usr/bin/nawk \
      'BEGIN{FS="\n"} {print $NF}'))
    while [ $idx2 -lt ${#origin_array[@]} ]; do
      origin=${origin_array[$idx2+1]}
      origin_name=$(/usr/bin/aimanifest get ${origin}@name 2> /dev/null)
      publisher="${publisher}+${origin_name}"
      (( idx2=idx2+2 ))
    done

    saved_pubs[$pub_idx]=${publisher}
    (( pub_idx=pub_idx+1 ))
    (( idx1=idx1+2 ))
  done

  if [[ -n ${software_source_path} ]]; then
    # Delete source and start a fresh
    /usr/bin/aimanifest delete ${software_source_path}
  fi

  # Cycle through each custom publisher, adding in custom ordering
  # If already existed add custome origin before original
  idx1=0
  software_source_path=
  while [ $idx1 -lt ${#pub_list[@]} ]; do
    echo ${pub_list[$idx1]} | IFS='@' read publisher_name publisher_origin

    # Add specified publisher
    echo "Adding custom publisher ${publisher_name} @ ${publisher_origin}"
    if [ -z ${software_source_path} ]; then
      publisher_path=$(/usr/bin/aimanifest add -r \
        ${software_path}/source/publisher@name ${publisher_name} 2> /dev/null)
      /usr/bin/aimanifest add ${publisher_path}/origin@name ${publisher_origin}

      software_source=$(/usr/bin/aimanifest get -r \
        ${software_path}/source 2> /dev/null)
      software_source_path=($(echo ${software_source} | /usr/bin/nawk \
        '{print $2}'))
    else
      publisher_path=$(/usr/bin/aimanifest add -r \
        ${software_source_path}/publisher@name ${publisher_name} 2> /dev/null)
      /usr/bin/aimanifest add ${publisher_path}/origin@name ${publisher_origin}
    fi

    # Check if this publisher already in manifest and add back original origins
    idx2=0
    while [ $idx2 -lt ${#saved_pubs[@]} ]; do
      saved_publisher=${saved_pubs[$idx2]}

      # saved_publisher is plus(+) delimited list, first item is publisher name 
      # and remaining items are origins, split it into an array
      OLDIFS=$IFS
      IFS="+"
      set -A saved_pub_details ${saved_publisher}
      IFS=$OLDIFS

      pub_name=${saved_pub_details[0]}

      if [ ${pub_name} == ${publisher_name} ]; then
        # Add all saved origins for this publisher
        idx3=1
        while [ $idx3 -lt ${#saved_pub_details[@]} ]; do
          saved_origin=${saved_pub_details[idx3]}
          echo "Adding extra saved origin ${saved_origin}"
          /usr/bin/aimanifest add ${publisher_path}/origin@name ${saved_origin}
          (( idx3=idx3+1 ))
        done
        saved_pubs[idx2]="PROCESSED"
        break
      else
        # look at next publisher
        (( idx2=idx2+1 ))
        continue
      fi
    done

    (( idx1=idx1+1 ))
  done

  # Cycle through saved publishers adding back unprocessed ones
  idx1=0
  while [ $idx1 -lt ${#saved_pubs[@]} ]; do
    saved_publisher=${saved_pubs[$idx1]}

    OLDIFS=$IFS
    IFS="+"
    set -A saved_pub_details ${saved_publisher}
    IFS=$OLDIFS

    if [ ${saved_pub_details[0]} != "PROCESSED" ]; then
      # Add specified publisher
      echo "Adding saved publisher ${saved_pub_details[0]}"
      publisher_path=$(/usr/bin/aimanifest add -r \
        ${software_source_path}/publisher@name ${saved_pub_details[0]} \
        2> /dev/null)

      # Add all saved origins for this publisher
      idx2=1
      while [ $idx2 -lt ${#saved_pub_details[@]} ]; do
          saved_origin=${saved_pub_details[idx2]}
          echo "Adding saved origin ${saved_origin}"
          /usr/bin/aimanifest add ${publisher_path}/origin@name ${saved_origin}
          (( idx2=idx2+1 ))
      done
    fi
    (( idx1=idx1+1 ))
  done
}

#
# add_fmri
# Add specific fmri to be installed to software_data section
#
function add_fmri
{
  fmri=$1

  # fmri is plus(+) delimited list, split into an array
  OLDIFS=$IFS
  IFS="+"
  set -A pkg_list ${fmri}
  IFS=$OLDIFS

  # Get IPS software_data path
  software_data=$(/usr/bin/aimanifest get -r \
    /auto_install/ai_instance/software[@type="IPS"]/software_data[@action="install"] \
    2> /dev/null)

  # Get software_data path
  software_data_path=($(echo ${software_data} | /usr/bin/nawk '{print $2}'))

  # Get list of pkgs to install from the manifest
  # array will be formatted as:  <pkg>  <aimanifest path>...
  pkgs=($(/usr/bin/aimanifest get -r ${software_data_path}/name 2> /dev/null | /usr/bin/tr '\n' ' '))
  set -A array ${pkgs}

  # Cycle through each fmri package and add if not in manifest
  idx1=0
  while [ $idx1 -lt ${#pkg_list[@]} ]; do
    new_pkg=${pkg_list[$idx1]}

    found=0
    idx2=0
    while [ $idx2 -lt ${#array[@]} ]; do
      pkgname=${array[$idx2]}
      path=${array[$idx2+1]}
      echo ${new_pkg} | /usr/bin/egrep -s ${pkgname}
      if [ $? -ne 0 ]; then
        # Not found try comparing next package
        (( idx2=idx2+2 ))
        continue
      else
        # Package already in manifest can break out of this loop
        echo "Package ${new_pkg} already present in manifest."
        found=1
        break
      fi
    done

    # Package not found, so add to manifest
    if [ ${found} -eq 0 ]; then
      echo "Adding package ${new_pkg} to manifest."
      /usr/bin/aimanifest add ${software_data_path}/name ${new_pkg}
    fi

    (( idx1=idx1+1 ))
  done
}

########################################
# main
########################################
# Create xml tmp file, then use aimanifest(1M) to load the
# file and update the Solaris version to install.
if [ -z "$TMPFILE" ]; then
  echo "Error: Unable to create temporary manifest file"
  exit 1
fi
create_xml_file
load_xml
#
# Process bootargs
#
if [[ ${SI_ARCH} = sparc ]]; then
  ARCHIVE_URI=$(/usr/sbin/prtconf -vp | /usr/bin/nawk \
    '/bootargs.*archive_uri=/{n=split($0,a,"archive_uri=");split(a[2],b);split(b[1],c,"'\''");print c[1]}')
  AUTH_TOKEN=$(/usr/sbin/prtconf -vp | /usr/bin/nawk \
    '/bootargs.*auth_token=/{n=split($0,a,"auth_token=");split(a[2],b);split(b[1],c,"'\''");print c[1]}')
  PUBLISHERS=$(/usr/sbin/prtconf -vp | /usr/bin/nawk \
    '/bootargs.*publishers=/{n=split($0,a,"publishers=");split(a[2],b);split(b[1],c,"'\''");print c[1]}')
  FMRI=$(/usr/sbin/prtconf -vp | /usr/bin/nawk \
    '/bootargs.*fmri=/{n=split($0,a,"fmri=");split(a[2],b);split(b[1],c,"'\''");print c[1]}')
else
  ARCHIVE_URI=$(/usr/sbin/devprop -s archive_uri)
  AUTH_TOKEN=$(/usr/sbin/devprop -s auth_token)
  PUBLISHERS=$(/usr/sbin/devprop -s publishers)
  FMRI=$(/usr/sbin/devprop -s fmri)
fi

if [[ -n "$ARCHIVE_URI" ]]; then
  # Save list of default facets to re-insertion if required
  if [[ -n "$PUBLISHERS" || -n "$FMRI" ]]; then
    # Get IPS software paths
    software=$(/usr/bin/aimanifest get -r \
      /auto_install/ai_instance/software[@type="IPS"] \
      2> /dev/null)
    software_path=($(echo ${software} | /usr/bin/nawk '{print $2}'))

    facets=$(/usr/bin/aimanifest get -r \
      ${software_path}/destination/image/facet 2> /dev/null)
    facet_array=($(echo ${facets} | /usr/bin/nawk \
      'BEGIN{FS="\n"} {print $NF}'))

    facet_idx=0
    idx1=0
    while [ $idx1 -lt ${#facet_array[@]} ]; do
      facet=${facet_array[$idx1]}
      facet_path=${facet_array[$idx1+1]}
      facet_set=$(/usr/bin/aimanifest get ${facet_path}@set 2> /dev/null)
      saved_facets[$facet_idx]="${facet_set}+${facet}"
      (( facet_idx=facet_idx+1 ))
      (( idx1=idx1+2 ))
    done
  fi

  # Replace package software section with archive
  /usr/bin/aimanifest delete software
  swpath=$(/usr/bin/aimanifest add -r /auto_install/ai_instance/software@type ARCHIVE)
  file=$(/usr/bin/aimanifest add -r $swpath/source/file@uri $ARCHIVE_URI)
  if [[ -n "$AUTH_TOKEN" ]]; then
    /usr/bin/aimanifest add $file/credentials/http_auth_token $AUTH_TOKEN
  fi
  inspath=$(/usr/bin/aimanifest add -r $swpath/software_data@action install)
  /usr/bin/aimanifest add $inspath/name "*"
fi

if [[ -n "$PUBLISHERS" || -n "$FMRI" ]]; then
  if [[ -n "$ARCHIVE_URI" ]]; then
    # All software was removed, so add back stub IPS software
    swpath=$(/usr/bin/aimanifest add -r /auto_install/ai_instance/software@type IPS)
    swdatapath=$(/usr/bin/aimanifest add -r $swpath/software_data@action install)

    # Add back list of default facets
    echo "Adding back facets"
    idx1=0
    while [ $idx1 -lt ${#saved_facets[@]} ]; do
      saved_facet=${saved_facets[$idx1]}

      # saved_facet is plus(+) delimited two value string,
      # first item is set value and 2nd is actual facet
      OLDIFS=$IFS
      IFS="+"
      set -A saved_facet_details ${saved_facet}
      IFS=$OLDIFS

      facet_set=${saved_facet_details[0]}
      facet=${saved_facet_details[1]}

      facet_path=$(/usr/bin/aimanifest add -r ${swpath}/destination/image/facet ${facet})
      /usr/bin/aimanifest set ${facet_path}@set ${facet_set}
      (( idx1=idx1+1 ))
    done
  else
    # Ensure version if $SOLPKG is correct, remove all packages
    # other than $SOLPKG
    validate_entire
  fi

  if [[ -n "$PUBLISHERS" ]]; then
    # Add specific publishers to software source
    add_publishers $PUBLISHERS
  fi

  if [[ -n "$FMRI" ]]; then
    # Add specific FMRI to package set to install
    add_fmri $FMRI
  fi

  # Minumum package set is entire and one of solaris-small-server or
  # solaris-large-server
  # Ensure one of server packages are present in manifest
  if [[ -z "$ARCHIVE_URI" ]]; then
    validate_server_pkgs
  fi
fi

# Ensure manifest indicates to auto_reboot
/usr/bin/aimanifest set -r /auto_install/ai_instance@auto_reboot true

exit $SCRIPT_SUCCESS
