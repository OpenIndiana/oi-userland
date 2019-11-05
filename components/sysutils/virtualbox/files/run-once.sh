#!/usr/bin/sh
# Copyright (C) 2013-2014 Prominic - Thomas Gouverneur <thomas@espix.net>
# This program is free software: you can redistribute it and/or modify it under the 
# terms of the GNU General Public License as published by the Free Software Foundation, 
# either version 3 of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program. 
# If not, see http://www.gnu.org/licenses/.

. /lib/svc/share/smf_include.sh
lver=$(/usr/bin/svcprop -p config/version $SMF_FMRI)
if [ -f /opt/VirtualBox/VERSION ]; then
  cver=$(cat /opt/VirtualBox/VERSION)
else
  cver=""
fi
infoprint()
{
    echo 1>&2 "$1"
}
errorprint()
{
    echo 1>&2 "## $1"
}
if [ "$lver" != "$cver" ]; then
  svccfg -s $SMF_FMRI setprop config/assembled = false
  svccfg -s $SMF_FMRI setprop config/version = astring: $cver
  svccfg -s $SMF_FMRI refresh
  echo "--UPDATE virtualbox/run-once"
  BIN_PKG=`which pkg 2> /dev/null`
  # Check if the Zone Access service is holding open vboxdrv, if so stop & remove it
  servicefound=`svcs -H "svc:/application/virtualbox/zoneaccess" 2> /dev/null | grep '^online'`
  if test ! -z "$servicefound"; then
      infoprint "VirtualBox's zone access service appears to still be running."
      infoprint "Halting & removing zone access service..."
      /usr/sbin/svcadm disable -s svc:/application/virtualbox/zoneaccess
      # Don't delete the service, handled by manifest class action
      # /usr/sbin/svccfg delete svc:/application/virtualbox/zoneaccess
  fi
  
  # Check if the Web service is running, if so stop & remove it
  servicefound=`svcs -H "svc:/application/virtualbox/webservice" 2> /dev/null | grep '^online'`
  if test ! -z "$servicefound"; then
      infoprint "VirtualBox web service appears to still be running."
      infoprint "Halting & removing webservice..."
      /usr/sbin/svcadm disable -s svc:/application/virtualbox/webservice
      # Don't delete the service, handled by manifest class action
      # /usr/sbin/svccfg delete svc:/application/virtualbox/webservice
  fi
  
  # Check if the autostart service is running, if so stop & remove it
  servicefound=`svcs -H "svc:/application/virtualbox/autostart" 2> /dev/null | grep '^online'`
  if test ! -z "$servicefound"; then
      infoprint "VirtualBox autostart service appears to still be running."
      infoprint "Halting & removing autostart service..."
      /usr/sbin/svcadm disable -s svc:/application/virtualbox/autostart
  fi
  
  # Check if VBoxSVC is currently running
  VBOXSVC_PID=`ps -eo pid,fname | grep VBoxSVC | grep -v grep | awk '{ print $1 }'`
  if test ! -z "$VBOXSVC_PID" && test "$VBOXSVC_PID" -ge 0; then
      errorprint "VirtualBox's VBoxSVC (pid $VBOXSVC_PID) still appears to be running."
      abort_error
  fi
  # Check if VBoxNetDHCP is currently running
  VBOXNETDHCP_PID=`ps -eo pid,fname | grep VBoxNetDHCP | grep -v grep | awk '{ print $1 }'`
  if test ! -z "$VBOXNETDHCP_PID" && test "$VBOXNETDHCP_PID" -ge 0; then
      errorprint "VirtualBox's VBoxNetDHCP (pid $VBOXNETDHCP_PID) still appears to be running."
      abort_error
  fi
  
  # Check if VBoxNetNAT is currently running
  VBOXNETNAT_PID=`ps -eo pid,fname | grep VBoxNetNAT | grep -v grep | awk '{ print $1 }'`
  if test ! -z "$VBOXNETNAT_PID" && test "$VBOXNETNAT_PID" -ge 0; then
      errorprint "VirtualBox's VBoxNetNAT (pid $VBOXNETNAT_PID) still appears to be running."
      abort_error
  fi
  # Check if vboxnet is still plumbed, if so try unplumb it
  BIN_IFCONFIG=`which ifconfig 2> /dev/null`
  if test -x "$BIN_IFCONFIG"; then
      vboxnetup=`$BIN_IFCONFIG vboxnet0 >/dev/null 2>&1`
      if test "$?" -eq 0; then
          infoprint "VirtualBox NetAdapter is still plumbed"
          infoprint "Trying to remove old NetAdapter..."
          $BIN_IFCONFIG vboxnet0 unplumb
          if test "$?" -ne 0; then
              errorprint "VirtualBox NetAdapter 'vboxnet0' couldn't be unplumbed (probably in use)."
              abort_error
          fi
      fi
      vboxnetup=`$BIN_IFCONFIG vboxnet0 inet6 >/dev/null 2>&1`
      if test "$?" -eq 0; then
          infoprint "VirtualBox NetAdapter (Ipv6) is still plumbed"
          infoprint "Trying to remove old NetAdapter..."
          $BIN_IFCONFIG vboxnet0 inet6 unplumb
          if test "$?" -ne 0; then
              errorprint "VirtualBox NetAdapter 'vboxnet0' IPv6 couldn't be unplumbed (probably in use)."
              abort_error
          fi
      fi
  fi
 
fi
assembled=$(/usr/bin/svcprop -p config/assembled $SMF_FMRI)
if [ "$assembled" == "true" ] ; then
    exit $SMF_EXIT_OK
fi
# Run the pkginstall.sh --ips
echo "--PKGINSTALL virtualbox/run-once"
/opt/VirtualBox/pkginstall.sh --ips
svccfg -s $SMF_FMRI setprop config/assembled = true
svccfg -s $SMF_FMRI refresh
echo "--DONE virtualbox/run-once"
