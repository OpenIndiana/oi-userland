# vim: tabstop=4 shiftwidth=4 softtabstop=4
# Copyright (c) 2012 OpenStack LLC.
# All Rights Reserved.
#
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
"""
Drivers for Solaris ZFS operations in local and iSCSI modes
"""

import abc
import fcntl
import os
import subprocess
import time

from oslo_concurrency import processutils
from oslo_config import cfg
from oslo_log import log as logging
import paramiko

from cinder import exception
from cinder.i18n import _, _LE, _LI
from cinder.image import image_utils
from cinder.volume import driver
from cinder.volume.drivers.san.san import SanDriver

from eventlet.green import socket
from eventlet.green.OpenSSL import SSL

import rad.client as radc
import rad.connect as radcon
import rad.bindings.com.oracle.solaris.rad.zfsmgr_1 as zfsmgr
import rad.auth as rada

from solaris_install.target.size import Size

FLAGS = cfg.CONF
LOG = logging.getLogger(__name__)

solaris_zfs_opts = [
    cfg.StrOpt('zfs_volume_base',
               default='rpool/cinder',
               help='The base dataset for ZFS volumes.'),
    cfg.StrOpt('zfs_target_group',
               default='tgt-grp',
               help='iSCSI target group name.'), ]

FLAGS.register_opts(solaris_zfs_opts)


def connect_tls(host, port=12302, locale=None, ca_certs=None):
    """Connect to a RAD instance over TLS.

    Arguments:
    host     string, target host
    port     int, target port (RAD_PORT_TLS = 12302)
    locale   string, locale
    ca_certs string, path to file containing CA certificates

    Returns:
    RadConnection: a connection to RAD
    """
    # We don't want SSL 2.0, SSL 3.0 nor TLS 1.0 in RAD
    context = SSL.Context(SSL.SSLv23_METHOD)
    context.set_options(SSL.OP_NO_SSLv2)
    context.set_options(SSL.OP_NO_SSLv3)
    context.set_options(SSL.OP_NO_TLSv1)

    if ca_certs is not None:
        context.set_verify(SSL.VERIFY_PEER, _tls_verify_cb)
        context.load_verify_locations(ca_certs)

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock = SSL.Connection(context, sock)
    sock.connect((host, port))
    sock.do_handshake()

    return radcon.RadConnection(sock, locale=locale)


class ZFSVolumeDriver(SanDriver):
    """OpenStack Cinder ZFS volume driver for generic ZFS volumes.

    Version history:
        1.0.0 - Initial driver with basic functionalities in Havana
        1.1.0 - Support SAN for the remote storage nodes access in Juno
        1.1.1 - Add support for the volume backup
        1.1.2 - Add support for the volume migration
        1.2.0 - Add support for the volume management in Kilo
        1.2.1 - Enable the connect_tls by importing eventlet.green.socket
        1.2.2 - Introduce the ZFS RAD for volume migration enhancement
        1.2.3 - Replace volume-specific targets with one shared target in
                the ZFSISCSIDriver

    """

    version = "1.2.3"
    protocol = 'local'

    def __init__(self, *args, **kwargs):
        super(ZFSVolumeDriver, self).__init__(execute=self.solaris_execute,
                                              *args, **kwargs)
        self.configuration.append_config_values(solaris_zfs_opts)
        self.run_local = self.configuration.san_is_local
        self.hostname = socket.gethostname()

    def solaris_execute(self, *cmd, **kwargs):
        """Execute the command locally or remotely."""
        if self.run_local:
            return processutils.execute(*cmd, **kwargs)
        else:
            return super(ZFSVolumeDriver, self)._run_ssh(cmd,
                                                         check_exit_code=True)

    def check_for_setup_error(self):
        """Check the setup error."""
        pass

    def create_volume(self, volume):
        """Create a volume."""
        size = '%sG' % volume['size']
        zfs_volume = self._get_zfs_volume_name(volume['name'])

        # Create a ZFS volume
        cmd = ['/usr/sbin/zfs', 'create', '-V', size, zfs_volume]
        self._execute(*cmd)
        LOG.debug(_("Created ZFS volume '%s'") % volume['name'])

    def create_volume_from_snapshot(self, volume, snapshot):
        """Create a cloned volume from a snapshot."""
        if volume['size'] != snapshot['volume_size']:
            exception_message = (_("Could not create volume '%s' because "
                                   "its volume size of '%s' is different "
                                   "from that of the snapshot, '%s'.")
                                 % (volume['name'], volume['size'],
                                    snapshot['volume_size']))
            raise exception.InvalidInput(reason=exception_message)

        # Create a ZFS clone
        zfs_snapshot = self._get_zfs_snap_name(snapshot)
        zfs_volume = self._get_zfs_volume_name(volume['name'])
        cmd = ['/usr/sbin/zfs', 'clone', zfs_snapshot, zfs_volume]
        self._execute(*cmd)

        LOG.debug(_("Created cloned volume '%s'") % volume['name'])

    def create_cloned_volume(self, volume, src_vref):
        """Create a clone of the specified volume."""
        if volume['size'] != src_vref['size']:
            exception_message = (_("Could not clone volume '%s' because "
                                   "its volume size of '%s' is different "
                                   "from that of the source volume, '%s'.")
                                 % (volume['name'], volume['size'],
                                    src_vref['size']))
            raise exception.VolumeBackendAPIException(data=exception_message)

        self._zfs_send_recv(src_vref,
                            self._get_zfs_volume_name(volume['name']))

        LOG.debug(_("Created cloned volume '%s' from source volume '%s'")
                  % (volume['name'], src_vref['name']))

    def delete_volume(self, volume):
        """Delete a volume.

        Firstly, the volume should be checked if it is a cloned one. If yes,
        its parent snapshot with prefix 'tmp-snapshot-' should be deleted as
        well after it is removed.
        """
        zvol = self._get_zvol_path(volume)
        try:
            (out, _err) = self._execute('/usr/bin/ls', zvol)
        except processutils.ProcessExecutionError:
            LOG.debug(_("The volume path '%s' doesn't exist") % zvol)
            return

        zfs_volume = self._get_zfs_volume_name(volume['name'])
        origin_snapshot = self._get_zfs_property('origin', zfs_volume)
        tmp_cloned_vol = False

        # Check if it is the temporary snapshot created for the cloned volume
        if origin_snapshot.startswith(self.configuration.zfs_volume_base):
            prop_type = self._get_zfs_property('type', origin_snapshot)
            tmp_snap_prefix = 'tmp-snapshot-%s' % volume['id']
            if prop_type == 'snapshot' and tmp_snap_prefix in origin_snapshot:
                tmp_cloned_vol = True

        cmd = ['/usr/sbin/zfs', 'destroy', zfs_volume]
        self._execute(*cmd)
        LOG.debug(_("Deleted volume '%s'") % volume['name'])

        if tmp_cloned_vol:
            self._execute('/usr/sbin/zfs', 'destroy', origin_snapshot)
            LOG.debug(_("Deleted parent snapshot '%s' of volume '%s'")
                      % (origin_snapshot, volume['name']))

    def create_snapshot(self, snapshot):
        """Create a snapshot."""
        cmd = ['/usr/sbin/zfs', 'snapshot', self._get_zfs_snap_name(snapshot)]
        self._execute(*cmd)

        LOG.debug(_("Created snapshot '%s'") % snapshot['name'])

    def delete_snapshot(self, snapshot):
        """Delete a snapshot."""
        cmd = ['/usr/sbin/zfs', 'destroy', self._get_zfs_snap_name(snapshot)]
        self._execute(*cmd)

        LOG.debug(_("Deleted snapshot '%s'") % snapshot['name'])

    def ensure_export(self, context, volume):
        """Synchronously recreate an export for a logical volume."""
        pass

    def create_export(self, context, volume):
        """Export the volume."""
        pass

    def remove_export(self, context, volume):
        """Remove an export for a volume."""
        pass

    def initialize_connection(self, volume, connector):
        """Initialize the connection and returns connection info."""
        volume_path = '%s/volume-%s' % (self.configuration.zfs_volume_base,
                                        volume['id'])
        properties = {}
        properties['device_path'] = self._get_zvol_path(volume)

        return {
            'driver_volume_type': 'local',
            'volume_path': volume_path,
            'data': properties
        }

    def terminate_connection(self, volume, connector, **kwargs):
        """Disconnection from the connector."""
        pass

    def attach_volume(self, context, volume, instance_uuid, host_name,
                      mountpoint):
        """Callback for volume attached to instance or host."""
        pass

    def detach_volume(self, context, volume, attachment):
        """ Callback for volume detached."""
        pass

    def get_volume_stats(self, refresh=False):
        """Get volume status."""

        if refresh:
            self._update_volume_stats()

        return self._stats

    def _get_zfs_property(self, prop, dataset):
        """Get the value of property for the dataset."""
        try:
            (out, _err) = self._execute('/usr/sbin/zfs', 'get', '-H', '-o',
                                        'value', prop, dataset)
            return out.rstrip()
        except processutils.ProcessExecutionError:
            LOG.info(_LI("Failed to get the property '%s' of the dataset '%s'")
                     % (prop, dataset))
            return None

    def _get_zfs_snap_name(self, snapshot):
        """Get the snapshot path."""
        return "%s/%s@%s" % (self.configuration.zfs_volume_base,
                             snapshot['volume_name'], snapshot['name'])

    def _get_zfs_volume_name(self, volume_name):
        """Add the pool name to get the ZFS volume."""
        return "%s/%s" % (self.configuration.zfs_volume_base,
                          volume_name)

    def _remote_piped_execute(self, cmd1, cmd2, ip, username, password):
        """Piped execute on a remote host."""
        LOG.debug(_("Piping cmd1='%s' into cmd='%s' on host '%s'") %
                  (' '.join(cmd1), ' '.join(cmd2), ip))

        client = paramiko.SSHClient()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        client.connect(ip, username=username, password=password)

        cmd = ' '.join(cmd1) + '|' + ' '.join(cmd2)
        stdin, stdout, stderr = client.exec_command(cmd)
        channel = stdout.channel
        exit_status = channel.recv_exit_status()

        if exit_status != 0:
            LOG.error(_("_remote_piped_execute: failed to host '%s' with "
                        "stdout '%s' and stderr '%s'")
                      % (ip, stdout.read(), stderr.read()))
            msg = (_("Remote piped execution failed to host '%s'.") % ip)
            raise exception.VolumeBackendAPIException(data=msg)

    def _piped_execute(self, cmd1, cmd2):
        """Pipe output of cmd1 into cmd2."""
        LOG.debug(_("Piping cmd1='%s' into cmd2='%s'") %
                  (' '.join(cmd1), ' '.join(cmd2)))

        try:
            p1 = subprocess.Popen(cmd1, stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE)
        except:
            LOG.error(_LE("_piped_execute '%s' failed.") % (cmd1))
            raise

        # Set the pipe to be blocking because evenlet.green.subprocess uses
        # the non-blocking pipe.
        flags = fcntl.fcntl(p1.stdout, fcntl.F_GETFL) & (~os.O_NONBLOCK)
        fcntl.fcntl(p1.stdout, fcntl.F_SETFL, flags)

        p2 = subprocess.Popen(cmd2, stdin=p1.stdout,
                              stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE)
        p1.stdout.close()
        stdout, stderr = p2.communicate()
        if p2.returncode:
            msg = (_("_piped_execute failed with the info '%s' and '%s'.") %
                   (stdout, stderr))
            raise exception.VolumeBackendAPIException(data=msg)

    def _zfs_send_recv(self, src, dst):
        """Replicate the ZFS dataset by calling zfs send/recv cmd"""
        src_snapshot = {'volume_name': src['name'],
                        'name': 'tmp-snapshot-%s' % src['id']}
        src_snapshot_name = self._get_zfs_snap_name(src_snapshot)
        prop_type = self._get_zfs_property('type', src_snapshot_name)
        # Delete the temporary snapshot if it already exists
        if prop_type == 'snapshot':
            self.delete_snapshot(src_snapshot)
        # Create a temporary snapshot of volume
        self.create_snapshot(src_snapshot)
        src_snapshot_name = self._get_zfs_snap_name(src_snapshot)

        cmd1 = ['/usr/sbin/zfs', 'send', src_snapshot_name]
        cmd2 = ['/usr/sbin/zfs', 'receive', dst]
        # Due to pipe injection protection in the ssh utils method,
        # cinder.utils.check_ssh_injection(), the piped commands must be passed
        # through via paramiko. These commands take no user defined input
        # other than the names of the zfs datasets which are already protected
        # against the special characters of concern.
        if not self.run_local:
            ip = self.configuration.san_ip
            username = self.configuration.san_login
            password = self.configuration.san_password
            self._remote_piped_execute(cmd1, cmd2, ip, username, password)
        else:
            self._piped_execute(cmd1, cmd2)

        # Delete the temporary src snapshot and dst snapshot
        self.delete_snapshot(src_snapshot)
        dst_snapshot_name = "%s@tmp-snapshot-%s" % (dst, src['id'])
        cmd = ['/usr/sbin/zfs', 'destroy', dst_snapshot_name]
        self._execute(*cmd)

    def _get_rc_connect(self, san_info=None):
        """Connect the RAD server."""
        if san_info is not None:
            san_ip = san_info.split(';')[0]
            san_login = san_info.split(';')[1]
            san_password = san_info.split(';')[2]
        else:
            san_ip = self.configuration.san_ip
            san_login = self.configuration.san_login
            san_password = self.configuration.san_password

        rc = connect_tls(san_ip)
        auth = rada.RadAuth(rc)
        auth.pam_login(san_login, san_password)

        return rc

    def _rad_zfs_send_recv(self, src, dst, dst_san_info=None):
        """Replicate the ZFS dataset stream."""
        src_snapshot = {'volume_name': src['name'],
                        'name': 'tmp-send-snapshot-%s' % src['id']}
        src_snapshot_name = self._get_zfs_snap_name(src_snapshot)
        prop_type = self._get_zfs_property('type', src_snapshot_name)
        # Delete the temporary snapshot if it already exists
        if prop_type == 'snapshot':
            self.delete_snapshot(src_snapshot)
        # Create the temporary snapshot of src volume
        self.create_snapshot(src_snapshot)

        src_rc = self._get_rc_connect()
        dst_rc = self._get_rc_connect(dst_san_info)

        src_pat = self._get_zfs_volume_name(src['name'])
        src_vol_obj = src_rc.get_object(zfsmgr.ZfsDataset(),
                                        radc.ADRGlobPattern({"name": src_pat}))
        dst_pat = dst.rsplit('/', 1)[0]
        dst_vol_obj = dst_rc.get_object(zfsmgr.ZfsDataset(),
                                        radc.ADRGlobPattern({"name": dst_pat}))

        send_sock_info = src_vol_obj.get_send_socket(
            name=src_snapshot_name, socket_type=zfsmgr.SocketType.AF_INET)
        send_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        send_sock.connect((self.hostname, int(send_sock_info.socket)))

        dst_san_ip = dst_san_info.split(';')[0]
        remote_host, alias, addresslist = socket.gethostbyaddr(dst_san_ip)

        recv_sock_info = dst_vol_obj.get_receive_socket(
            name=dst, socket_type=zfsmgr.SocketType.AF_INET,
            name_options=zfsmgr.ZfsRecvNameOptions.use_provided_name)
        recv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        recv_sock.connect((remote_host, int(recv_sock_info.socket)))

        # Set 4mb buffer size
        buf_size = 4194304
        while True:
            # Read the data from the send stream
            buf = send_sock.recv(buf_size)
            if not buf:
                break
            # Write the data to the receive steam
            recv_sock.send(buf)

        recv_sock.close()
        send_sock.close()
        time.sleep(1)

        # Delete the temporary dst snapshot
        pat = radc.ADRGlobPattern({"name": dst})
        dst_zvol_obj = dst_rc.get_object(zfsmgr.ZfsDataset(), pat)
        snapshot_list = dst_zvol_obj.get_snapshots()
        for snap in snapshot_list:
            if 'tmp-send-snapshot'in snap:
                dst_zvol_obj.destroy_snapshot(snap)
                break

        # Delete the temporary src snapshot
        self.delete_snapshot(src_snapshot)
        LOG.debug(("Transfered src stream'%s' to dst'%s' on the host'%s'") %
                  (src_snapshot_name, dst, self.hostname))

        src_rc.close()
        dst_rc.close()

    def _get_zvol_path(self, volume):
        """Get the ZFS volume path."""
        return "/dev/zvol/rdsk/%s" % self._get_zfs_volume_name(volume['name'])

    def _update_volume_stats(self):
        """Retrieve volume status info."""

        LOG.debug(_("Updating volume status"))
        stats = {}
        backend_name = self.configuration.safe_get('volume_backend_name')
        stats["volume_backend_name"] = backend_name or self.__class__.__name__
        stats["storage_protocol"] = self.protocol
        stats["driver_version"] = self.version
        stats["vendor_name"] = 'Oracle'
        stats['QoS_support'] = False

        dataset = self.configuration.zfs_volume_base
        used_size = self._get_zfs_property('used', dataset)
        avail_size = self._get_zfs_property('avail', dataset)
        stats['total_capacity_gb'] = \
            (Size(used_size) + Size(avail_size)).get(Size.gb_units)
        stats['free_capacity_gb'] = Size(avail_size).get(Size.gb_units)
        stats['reserved_percentage'] = self.configuration.reserved_percentage

        stats['location_info'] =\
            ('ZFSVolumeDriver:%(hostname)s:%(zfs_volume_base)s:local' %
             {'hostname': self.hostname,
              'zfs_volume_base': self.configuration.zfs_volume_base})

        self._stats = stats

    def extend_volume(self, volume, new_size):
        """Extend an existing volume's size."""
        volsize_str = 'volsize=%sg' % new_size
        zfs_volume = self._get_zfs_volume_name(volume['name'])
        try:
            self._execute('/usr/sbin/zfs', 'set', volsize_str, zfs_volume)
        except Exception:
            msg = (_("Failed to extend volume size to %(new_size)s GB.")
                   % {'new_size': new_size})
            raise exception.VolumeBackendAPIException(data=msg)

    def rename_volume(self, src, dst):
        """Rename the volume from src to dst in the same zpool."""
        cmd = ['/usr/sbin/zfs', 'rename', src, dst]
        self._execute(*cmd)

        LOG.debug(_("Rename the volume '%s' to '%s'") % (src, dst))

    def _get_existing_volume_ref_name(self, existing_ref):
        """Returns the volume name of an existing reference.
        And Check if an existing volume reference has a source-name
        """
        if 'source-name' in existing_ref:
            vol_name = existing_ref['source-name']
            return vol_name
        else:
            reason = _("Reference must contain source-name.")
            raise exception.ManageExistingInvalidReference(
                existing_ref=existing_ref,
                reason=reason)

    def manage_existing_get_size(self, volume, existing_ref):
        """Return size of volume to be managed by manage_existing.
        existing_ref is a dictionary of the form:
        {'source-name': <name of the volume>}
        """
        target_vol_name = self._get_existing_volume_ref_name(existing_ref)
        volsize = self._get_zfs_property('volsize', target_vol_name)

        return Size(volsize).get(Size.gb_units)

    def manage_existing(self, volume, existing_ref):
        """Brings an existing zfs volume object under Cinder management.

        :param volume:       Cinder volume to manage
        :param existing_ref: Driver-specific information used to identify a
        volume
        """
        # Check the existence of the ZFS volume
        target_vol_name = self._get_existing_volume_ref_name(existing_ref)
        prop_type = self._get_zfs_property('type', target_vol_name)
        if prop_type != 'volume':
            msg = (_("Failed to identify the volume '%s'.")
                   % target_vol_name)
            raise exception.InvalidInput(reason=msg)

        if volume['name']:
            volume_name = volume['name']
        else:
            volume_name = 'new_zvol'

        # rename the volume
        dst_volume = "%s/%s" % (self.configuration.zfs_volume_base,
                                volume_name)
        self.rename_volume(target_vol_name, dst_volume)

    def unmanage(self, volume):
        """Removes the specified volume from Cinder management."""
        # Rename the volume's name to cinder-unm-* format.
        volume_name = self._get_zfs_volume_name(volume['name'])
        tmp_volume_name = "cinder-unm-%s" % volume['name']
        new_volume_name = "%s/%s" % (self.configuration.zfs_volume_base,
                                     tmp_volume_name)
        self.rename_volume(volume_name, new_volume_name)

    def migrate_volume(self, context, volume, host):
        """Migrate the volume from one backend to another one.
        The backends should be in the same volume type.

        :param context: context
        :param volume: a dictionary describing the volume to migrate
        :param host: a dictionary describing the host to migrate to
        """
        false_ret = (False, None)
        if volume['status'] != 'available':
            LOG.debug(_("Status of volume '%s' is '%s', not 'available'.") %
                      (volume['name'], volume['status']))
            return false_ret

        if 'capabilities' not in host:
            LOG.debug(("No 'capabilities' is reported in the host'%s'") %
                      host['host'])
            return false_ret

        if 'location_info' not in host['capabilities']:
            LOG.debug(("No 'location_info' is reported in the host'%s'") %
                      host['host'])
            return false_ret

        info = host['capabilities']['location_info']
        dst_volume = "%s/%s" % (info.split(':')[2], volume['name'])
        src_volume = self._get_zfs_volume_name(volume['name'])

        # check if the src and dst volume are under the same zpool
        dst_san_info = info.split(':')[3]
        if dst_san_info == 'local':
            self._zfs_send_recv(volume, dst_volume)
        else:
            self._rad_zfs_send_recv(volume, dst_volume, dst_san_info)
        # delete the source volume
        self.delete_volume(volume)

        provider_location = {}
        return (True, provider_location)


class STMFDriver(ZFSVolumeDriver):
    """Abstract base class for common COMSTAR operations."""
    __metaclass__ = abc.ABCMeta

    def __init__(self, *args, **kwargs):
        super(STMFDriver, self).__init__(*args, **kwargs)

    def _stmf_execute(self, *cmd):
        """Handle the possible race during the local execution."""
        tries = 0
        while True:
            try:
                self._execute(*cmd)
                return
            except processutils.ProcessExecutionError as ex:
                tries = tries + 1

                if tries >= self.configuration.num_shell_tries or \
                        'resource busy' not in ex.stderr:
                    raise

                time.sleep(tries ** 2)

    def _check_target(self, target, protocol):
        """Verify the target and check its status."""
        try:
            (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-target',
                                        '-v', target)
            tmp_protocol = None
            status = None
            for line in [l.strip() for l in out.splitlines()]:
                if line.startswith("Operational"):
                    status = line.split()[-1]
                if line.startswith("Protocol"):
                    tmp_protocol = line.split()[-1]
                    break
            if tmp_protocol == protocol:
                return status
            else:
                err_msg = (_("'%s' does not match the listed protocol '%s'"
                             " for target '%s'.")
                           % (protocol, tmp_protocol, target))
        except processutils.ProcessExecutionError as error:
            if 'not found' in error.stderr:
                LOG.debug(_("The target '%s' is not found.") % target)
                return None
            else:
                err_msg = (_("Failed to list the target '%s': '%s'")
                           % (target, error.stderr))
        raise exception.VolumeBackendAPIException(data=err_msg)

    def _check_tg(self, tg):
        """Check if the target group exists."""
        try:
            self._execute('/usr/sbin/stmfadm', 'list-tg', tg)
            return True
        except processutils.ProcessExecutionError as error:
            if 'not found' in error.stderr:
                LOG.debug(_("The target group '%s' is not found.") % tg)
                return False
            else:
                err_msg = (_("Failed to list the target group '%s': '%s'")
                           % (tg, error.stderr))
            raise exception.VolumeBackendAPIException(data=err_msg)

    def _get_luid(self, volume):
        """Get the LU corresponding to the volume."""
        zvol = self._get_zvol_path(volume)

        (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-lu', '-v')
        luid = None

        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("LU Name:"):
                luid = line.split()[-1]
            if line.startswith("Alias") and line.split()[-1] == zvol:
                break
        else:
            luid = None

        if luid is not None:
            LOG.debug(_("Got the LU '%s'") % luid)
        else:
            LOG.debug(_("Failed to get LU for volume '%s'")
                      % volume['name'])
        return luid

    def _get_view_and_lun(self, lu):
        """Check the view entry of the LU and then get the lun and view."""
        view_and_lun = {}
        view_and_lun['view'] = view_and_lun['lun'] = None
        try:
            (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-view',
                                        '-l', lu, '-v')
        except processutils.ProcessExecutionError as error:
            if 'no views found' in error.stderr:
                LOG.debug(_("No view is found for LU '%s'") % lu)
                return view_and_lun
            else:
                raise

        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("View Entry:"):
                view_and_lun['view'] = line.split()[-1]
            if line.startswith("LUN") and 'Auto' not in line.split()[-1]:
                view_and_lun['lun'] = int(line.split()[-1])
                break
            if line.startswith("Lun"):
                view_and_lun['lun'] = int(line.split()[2])

        if view_and_lun['view'] is None or view_and_lun['lun'] is None:
            err_msg = (_("Failed to get the view_entry or LUN of the LU '%s'.")
                       % lu)
            raise exception.VolumeBackendAPIException(data=err_msg)
        else:
            LOG.debug(_("The view_entry and LUN of LU '%s' are '%s' and '%d'.")
                      % (lu, view_and_lun['view'], view_and_lun['lun']))

        return view_and_lun


class ZFSISCSIDriver(STMFDriver, driver.ISCSIDriver):
    """ZFS volume operations in iSCSI mode."""
    protocol = 'iSCSI'

    def __init__(self, *args, **kwargs):
        super(ZFSISCSIDriver, self).__init__(*args, **kwargs)
        if not self.configuration.san_is_local:
            self.hostname, alias, addresslist = \
                socket.gethostbyaddr(self.configuration.san_ip)

    def get_volume_stats(self, refresh=False):
        """Get volume status."""
        status = super(ZFSISCSIDriver, self).get_volume_stats(refresh)
        status["storage_protocol"] = self.protocol
        backend_name = self.configuration.safe_get('volume_backend_name')
        status["volume_backend_name"] = backend_name or self.__class__.__name__

        if not self.configuration.san_is_local:
            san_info = "%s;%s;%s" % (self.configuration.san_ip,
                                     self.configuration.san_login,
                                     self.configuration.san_password)
            status['location_info'] = \
                ('ZFSISCSIDriver:%(hostname)s:%(zfs_volume_base)s:'
                 '%(san_info)s' %
                 {'hostname': self.hostname,
                  'zfs_volume_base': self.configuration.zfs_volume_base,
                  'san_info': san_info})

        return status

    def do_setup(self, context):
        """Setup the target and target group."""
        target_group = self.configuration.zfs_target_group
        target_name = '%s%s-%s-target' % \
                      (self.configuration.iscsi_target_prefix,
                       self.hostname,
                       target_group)

        if not self._check_tg(target_group):
            self._stmf_execute('/usr/sbin/stmfadm', 'create-tg', target_group)
        target_status = self._check_target(target_name, 'iSCSI')
        if target_status == 'Online':
            return

        if target_status is None:
            # Create and add the target into the target group
            self._stmf_execute('/usr/sbin/itadm', 'create-target', '-n',
                               target_name)
            self._stmf_execute('/usr/sbin/stmfadm', 'offline-target',
                               target_name)
            self._stmf_execute('/usr/sbin/stmfadm', 'add-tg-member', '-g',
                               target_group, target_name)

        # Online the target from the 'Offline' status
        self._stmf_execute('/usr/sbin/stmfadm', 'online-target',
                           target_name)
        assert self._check_target(target_name, 'iSCSI') == 'Online'

    def create_export(self, context, volume):
        """Export the volume."""
        # If the volume is already exported there is nothing to do, as we
        # simply export volumes and they are universally available.
        luid = self._get_luid(volume)
        if luid:
            view_lun = self._get_view_and_lun(luid)
            if view_lun['view'] is not None:
                return
            else:
                msg = (_("Failed to create logical unit for volume '%s' due "
                         "to an existing LU id but no view.") % volume['name'])
                raise exception.VolumeBackendAPIException(data=msg)

        zvol = self._get_zvol_path(volume)

        # Create a Logical Unit (LU)
        self._stmf_execute('/usr/sbin/stmfadm', 'create-lu', zvol)
        luid = self._get_luid(volume)
        if not luid:
            msg = (_("Failed to create LU for volume '%s'")
                   % volume['name'])
            raise exception.VolumeBackendAPIException(data=msg)

        # Add a view entry to the logical unit
        target_group = self.configuration.zfs_target_group
        self._stmf_execute('/usr/sbin/stmfadm', 'add-view',
                           '-t', target_group, luid)

    def remove_export(self, context, volume):
        """Remove an export for a volume.

        All of the related elements about the volume, including the
        target, target group, view entry and lu, are deleted.
        """
        luid = self._get_luid(volume)

        # Remove the LU
        if luid is not None:
            self._stmf_execute('/usr/sbin/stmfadm', 'delete-lu', luid)

        # Remove the target and its target group if they were created by
        # earlier versions of the volume driver
        target_group = 'tg-%s' % volume['name']
        target_name = '%s%s' % (self.configuration.iscsi_target_prefix,
                                volume['name'])

        if self._check_target(target_name, 'iSCSI') is not None:
            self._stmf_execute('/usr/sbin/itadm', 'delete-target', '-f',
                               target_name)

        if self._check_tg(target_group):
            self._stmf_execute('/usr/sbin/stmfadm', 'delete-tg', target_group)

    def _get_iscsi_properties(self, volume):
        """Get iSCSI configuration

        Now we use the discovery address as the default approach to add
        objects into the initiator. A discovery address is an IP address:port
        combination used in a SendTargets discovery session in the initiator.

        :target_discovered:    boolean indicating whether discovery was used
        :target_iqn:           the IQN of the iSCSI target
        :target_portal:        the portal of the iSCSI target
        :target_lun:           the lun of the iSCSI target
        :volume_id:            the id of the volume

        :auth_method:, :auth_username:, :auth_password:
            the authentication details. Right now, either auth_method is not
            present meaning no authentication, or auth_method == `CHAP`
            meaning use CHAP with the specified credentials.
        """
        luid = self._get_luid(volume)
        if not luid:
            msg = (_("Failed to get LU for volume '%s'") % volume['name'])
            raise exception.VolumeBackendAPIException(data=msg)

        target_name = '%s%s' % (self.configuration.iscsi_target_prefix,
                                volume['name'])
        if self._check_target(target_name, 'iSCSI') is None:
            target_name = '%s%s-%s-target' % \
                          (self.configuration.iscsi_target_prefix,
                           self.hostname,
                           self.configuration.zfs_target_group)

        properties = {}

        properties['target_discovered'] = True
        properties['target_iqn'] = target_name

        # Here the san_is_local means that the cinder-volume runs in the
        # iSCSI target with iscsi_ip_address.
        if self.configuration.san_is_local:
            target_ip = self.configuration.iscsi_ip_address
        else:
            target_ip = self.configuration.san_ip
        properties['target_portal'] = ('%s:%d' %
                                       (target_ip,
                                        self.configuration.iscsi_port))
        view_lun = self._get_view_and_lun(luid)
        if view_lun['lun'] is not None:
            properties['target_lun'] = view_lun['lun']
        properties['volume_id'] = volume['id']

        auth = volume['provider_auth']
        if auth:
            (auth_method, auth_username, auth_secret) = auth.split()
            properties['auth_method'] = auth_method
            properties['auth_username'] = auth_username
            properties['auth_password'] = auth_secret

        return properties

    def initialize_connection(self, volume, connector):
        """Initialize the connection and returns connection info.

        The iSCSI driver returns a driver_volume_type of 'iscsi'.
        The format of the driver data is defined in _get_iscsi_properties.
        Example return value::

        {
            'driver_volume_type': 'iscsi'
            'data': {
                'target_discovered': True,
                'target_iqn':
                'iqn.1986-03.com.sun:02:200720c6-9bca-cb8f-c061-d427d7ab978f',
                'target_portal': '127.0.0.1:3260',
                'volume_id': 1,
            }
        }

        """
        initiator_name = connector['initiator']
        volume_name = volume['name']
        LOG.debug(_('Connecting the initiator %(initiator_name)s '
                    'for volume %(volume_name)s')
                  % {'initiator_name': initiator_name,
                     'volume_name': volume_name})
        iscsi_properties = self._get_iscsi_properties(volume)

        return {
            'driver_volume_type': 'iscsi',
            'data': iscsi_properties
        }

    def terminate_connection(self, volume, connector, **kwargs):
        """Disconnection from the connector."""
        initiator_name = connector['initiator']
        volume_name = volume['name']

        LOG.debug(_('Disconnecting the initiator %(initiator_name)s '
                    'for volume %(volume_name)s')
                  % {'initiator_name': initiator_name,
                     'volume_name': volume_name})


class ZFSFCDriver(STMFDriver, driver.FibreChannelDriver):
    """ZFS volume operations in FC mode."""
    protocol = 'FC'

    def __init__(self, *args, **kwargs):
        super(ZFSFCDriver, self).__init__(*args, **kwargs)
        if not self.configuration.san_is_local:
            self.hostname, alias, addresslist = \
                socket.gethostbyaddr(self.configuration.san_ip)

    def get_volume_stats(self, refresh=False):
        """Get volume status."""
        status = super(ZFSFCDriver, self).get_volume_stats(refresh)
        status["storage_protocol"] = self.protocol
        backend_name = self.configuration.safe_get('volume_backend_name')
        status["volume_backend_name"] = backend_name or self.__class__.__name__

        if not self.configuration.san_is_local:
            san_info = "%s;%s;%s" % (self.configuration.san_ip,
                                     self.configuration.san_login,
                                     self.configuration.san_password)
            status['location_info'] = \
                ('ZFSFCDriver:%(hostname)s:%(zfs_volume_base)s:'
                 '%(san_info)s' %
                 {'hostname': self.hostname,
                  'zfs_volume_base': self.configuration.zfs_volume_base,
                  'san_info': san_info})

        return status

    def do_setup(self, context):
        """Check wwns and setup the target group."""
        self.wwns = self._get_wwns()
        if not self.wwns:
            msg = (_("Could not determine fibre channel world wide "
                     "node names."))
            raise exception.VolumeBackendAPIException(data=msg)

        self.tg = 'tg-wwn-%s' % self.wwns[0]
        if not self._check_tg(self.tg):
            self._setup_tg(self.tg)

    def _get_wwns(self):
        """Get the FC port WWNs of the host."""
        (out, _err) = self._execute('/usr/sbin/fcinfo', 'hba-port', '-t')

        wwns = []
        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("HBA Port WWN:"):
                wwn = line.split()[-1]
                LOG.debug(_("Got the FC port WWN '%s'") % wwn)
                wwns.append(wwn)

        return wwns

    def _get_target_wwns(self, tg):
        """Get the target members in the tg."""
        (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-tg',
                                    '-v', tg)

        wwns = []
        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("Member:"):
                wwn = line.split()[-1]
                target_wwn = wwn.split('.')[-1]
                wwns.append(target_wwn)
        return wwns

    def _setup_tg(self, tg):
        """Setup the target group."""
        self._stmf_execute('/usr/sbin/stmfadm', 'create-tg', tg)

        # Add free target wwns into the target group
        for wwn in self.wwns:
            if not self._target_in_tg(wwn, None):
                target_wwn = 'wwn.%s' % wwn
                try:
                    self._stmf_execute('/usr/sbin/stmfadm', 'offline-target',
                                       target_wwn)
                    self._stmf_execute('/usr/sbin/stmfadm', 'add-tg-member',
                                       '-g', tg, target_wwn)
                    self._stmf_execute('/usr/sbin/stmfadm', 'online-target',
                                       target_wwn)
                    assert self._check_target(wwn, 'Channel') == 'Online'

                except:
                    LOG.error(_LE("Failed to add and online the target '%s'.")
                              % (target_wwn))

        target_wwns = self._get_target_wwns(tg)
        if not target_wwns:
            msg = (_("No target members exist in the target group '%s'.")
                   % tg)
            raise exception.VolumeBackendAPIException(data=msg)

    def _only_lu(self, lu):
        """Check if the LU is the only one."""
        (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-lu', '-v')
        linecount = 0

        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("LU Name:"):
                luid = line.split()[-1]
                linecount += 1

        if linecount == 1 and luid == lu:
            LOG.debug(_("The LU '%s' is the only one.") % lu)
            return True
        else:
            return False

    def _target_in_tg(self, wwn, tg):
        """Check if the target has been added into a target group."""
        target = 'wwn.%s' % wwn.upper()

        if tg is not None:
            (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-tg',
                                        '-v', tg)
        else:
            (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-tg', '-v')
        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("Member:") and target in line:
                return True
        LOG.debug(_("The target '%s' is not in %s target group.") %
                  (target, tg if tg else 'any'))
        return False

    def _force_lip_wwn(self):
        """Force the link to reinitialize."""
        target_wwns = self._get_target_wwns(self.tg)
        for target_wwn in target_wwns:
            self._stmf_execute('/usr/sbin/fcadm', 'force-lip', target_wwn)

    def create_export(self, context, volume):
        """Export the volume."""
        # If the volume is already exported there is nothing to do, as we
        # simply export volumes and they are universally available.
        luid = self._get_luid(volume)
        if luid:
            view_lun = self._get_view_and_lun(luid)
            if view_lun['view'] is not None:
                return
            else:
                msg = (_("Failed to create logical unit for volume '%s' due "
                         "to an existing LU id but no view.") % volume['name'])
                raise exception.VolumeBackendAPIException(data=msg)

        zvol = self._get_zvol_path(volume)
        # Create a Logical Unit (LU)
        self._stmf_execute('/usr/sbin/stmfadm', 'create-lu', zvol)
        luid = self._get_luid(volume)
        if not luid:
            msg = (_("Failed to create logic unit for volume '%s'")
                   % volume['name'])
            raise exception.VolumeBackendAPIException(data=msg)

        # setup the target group if it doesn't exist.
        if not self._check_tg(self.tg):
            self._setup_tg(self.tg)
        # Add a logical unit view entry
        self._stmf_execute('/usr/sbin/stmfadm', 'add-view', '-t',
                           self.tg, luid)
        self._force_lip_wwn()

    def remove_export(self, context, volume):
        """Remove an export for a volume."""
        luid = self._get_luid(volume)

        if luid is not None:
            target_group = self.tg
            view_lun = self._get_view_and_lun(luid)
            if view_lun['view']:
                self._stmf_execute('/usr/sbin/stmfadm', 'remove-view', '-l',
                                   luid, view_lun['view'])

            # Remove the target group when the LU to be deleted is last one
            # exposed by the target group.
            if self._only_lu(luid):
                if self._check_tg(target_group):
                    self._stmf_execute('/usr/sbin/stmfadm', 'delete-tg',
                                       target_group)

            # Remove the LU
            self._stmf_execute('/usr/sbin/stmfadm', 'delete-lu', luid)

    def _get_fc_properties(self, volume):
        """Get Fibre Channel configuration.

        :target_discovered:    boolean indicating whether discovery was used
        :target_wwn:           the world wide name of the FC port target
        :target_lun:           the lun assigned to the LU for the view entry

        """
        luid = self._get_luid(volume)
        if not luid:
            msg = (_("Failed to get logic unit for volume '%s'")
                   % volume['name'])
            raise exception.VolumeBackendAPIException(data=msg)

        properties = {}

        properties['target_discovered'] = True
        properties['target_wwn'] = self._get_target_wwns(self.tg)
        view_lun = self._get_view_and_lun(luid)
        if view_lun['lun'] is not None:
            properties['target_lun'] = view_lun['lun']
        return properties

    def initialize_connection(self, volume, connector):
        """Initializes the connection and returns connection info.

        The  driver returns a driver_volume_type of 'fibre_channel'.
        The target_wwn can be a single entry or a list of wwns that
        correspond to the list of remote wwn(s) that will export the volume.
        Example return values:

            {
                'driver_volume_type': 'fibre_channel'
                'data': {
                    'target_discovered': True,
                    'target_lun': 1,
                    'target_wwn': '1234567890123',
                }
            }

            or

             {
                'driver_volume_type': 'fibre_channel'
                'data': {
                    'target_discovered': True,
                    'target_lun': 1,
                    'target_wwn': ['1234567890123', '0987654321321'],
                }
            }

        """
        fc_properties = self._get_fc_properties(volume)

        return {
            'driver_volume_type': 'fibre_channel',
            'data': fc_properties
        }
