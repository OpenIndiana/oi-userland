#!/usr/bin/python

import ConfigParser
import grp
import os
import pwd
import shutil
import sys
import time
import warnings

import netifaces

from M2Crypto import RSA
from optparse import OptionParser
from solaris_install import with_spinner
from subprocess import CalledProcessError, Popen, PIPE, check_call


def get_external_ip():
    '''Process all IPv4 network interfaces returning address of first
    non-localhost(127.0.0.1) address or None of not found.
    '''
    for iface in netifaces.interfaces():
        for addr in netifaces.ifaddresses(iface)[netifaces.AF_INET]:
            if addr['addr'] != "127.0.0.1":
                return addr['addr']
    return None


def keystone(sqlite):
    print "configuring keystone"
    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/keystone/keystone.conf"))
    config.set("DEFAULT", "admin_token", "ADMIN")
    if not sqlite:
        config.set("database", "connection",
                   "mysql://keystone:keystone@localhost/keystone")
    with open("/etc/keystone/keystone.conf", "wb") as fh:
        config.write(fh)

    print "enabling keystone"
    check_call(["/usr/sbin/svcadm", "enable", "-rs", "keystone"])

    # sleep for a few seconds to let SMF catch up
    time.sleep(2)

    print "loading sample data"
    check_call(["/usr/bin/bash", "sample_data.sh"],
               cwd="/usr/demo/openstack/keystone")

    # Create ironic keystone info as not in sample_data.sh
    check_call(["/usr/bin/bash", "ironic-keystone-setup.sh"],
               cwd="/usr/demo/openstack/keystone")

    print "testing keystone"
    print "keystone user-list:"
    check_call(["keystone", "user-list"],
               env={"SERVICE_ENDPOINT": "http://localhost:35357/v2.0",
                    "SERVICE_TOKEN": "ADMIN"})


def glance(sqlite):
    print "configuring glance"

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/glance/glance-api.conf"))
    config.set("keystone_authtoken", "admin_tenant_name", "service")
    config.set("keystone_authtoken", "admin_user", "glance")
    config.set("keystone_authtoken", "admin_password", "glance")
    if not sqlite:
        config.set("database", "connection",
                   "mysql://glance:glance@localhost/glance")

    with open("/etc/glance/glance-api.conf", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/glance/glance-cache.conf"))
    config.set("DEFAULT", "auth_url", "http://127.0.0.1:5000/v2.0/")
    config.set("DEFAULT", "admin_tenant_name", "service")
    config.set("DEFAULT", "admin_user", "glance")
    config.set("DEFAULT", "admin_password", "glance")
    with open("/etc/glance/glance-cache.conf", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/glance/glance-registry.conf"))
    config.set("keystone_authtoken", "admin_tenant_name", "service")
    config.set("keystone_authtoken", "admin_user", "glance")
    config.set("keystone_authtoken", "admin_password", "glance")
    if not sqlite:
        config.set("database", "connection",
                   "mysql://glance:glance@localhost/glance")
    with open("/etc/glance/glance-registry.conf", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/glance/glance-api-paste.ini"))
    config.set("filter:authtoken", "auth_uri", "http://127.0.0.1:5000/v2.0/")
    config.set("filter:authtoken", "identity_uri", "http://127.0.0.1:35357")
    config.set("filter:authtoken", "admin_tenant_name", "service")
    config.set("filter:authtoken", "admin_user", "glance")
    config.set("filter:authtoken", "admin_password", "glance")
    with open("/etc/glance/glance-api-paste.ini", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/glance/glance-registry-paste.ini"))
    config.set("filter:authtoken", "auth_uri", "http://127.0.0.1:5000/v2.0/")
    config.set("filter:authtoken", "identity_uri", "http://127.0.0.1:35357")
    config.set("filter:authtoken", "admin_tenant_name", "service")
    config.set("filter:authtoken", "admin_user", "glance")
    config.set("filter:authtoken", "admin_password", "glance")
    with open("/etc/glance/glance-registry-paste.ini", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/glance/glance-scrubber.conf"))
    config.set("DEFAULT", "filesystem_store_datadir", "/var/lib/glance/images")
    config.set("DEFAULT", "swift_store_auth_address", "127.0.0.1:5000/v2.0/")
    config.set("DEFAULT", "swift_store_user", "johndoe:johndoe")
    config.set("DEFAULT", "swift_store_key",
               "a86850deb2742ec3cb41518e26aa2d89")
    config.set("DEFAULT", "s3_store_host", "127.0.0.1:8080/v1.0/")
    config.set("DEFAULT", "s3_store_access_key", '"<20-char AWS access key>"')
    config.set("DEFAULT", "s3_store_secret_key", '"<40-char AWS secret key>"')
    config.set("DEFAULT", "s3_store_bucket", '"<lowercased 20-char aws key>"')
    config.set("DEFAULT", "s3_store_create_bucket_on_put", "False")
    config.set("DEFAULT", "auth_url", "http://127.0.0.1:5000/v2.0/")
    config.set("DEFAULT", "admin_tenant_name", "service")
    config.set("DEFAULT", "admin_user", "glance")
    config.set("DEFAULT", "admin_password", "glance")
    with open("/etc/glance/glance-scrubber.conf", "wb") as fh:
        config.write(fh)

    print "enabling glance-api, glance-registry, and glance-scrubber"
    check_call(["/usr/sbin/svcadm", "enable", "-rs", "glance-api", "glance-db",
                "glance-registry", "glance-scrubber"])

    # sleep for a few seconds to let SMF catch up
    time.sleep(2)

    print "testing glance"
    print "glance image-list:"
    check_call(["glance", "image-list"],
               env={"OS_AUTH_URL": "http://localhost:5000/v2.0",
                    "OS_PASSWORD": "glance",
                    "OS_USERNAME": "glance",
                    "OS_TENANT_NAME": "service"})


def create_pubkey(user):
    # look for ssh keys for the user
    sshdir = os.path.join(user.pw_dir, ".ssh")
    if not os.path.exists(sshdir):
        os.mkdir(sshdir)

    print "setting .ssh/config"
    ssh_config = "Host *\n\tStrictHostKeyChecking no\n"
    with open(os.path.join(user.pw_dir, ".ssh", "config"), "w") as fh:
        fh.write(ssh_config)

    if not [f for f in os.listdir(sshdir) if f.endswith("rsa.pub")]:
        key = RSA.gen_key(2048, 65337)
        key.save_key(os.path.join(sshdir, "id_rsa"),
                     cipher=None)
        os.chmod(os.path.join(sshdir, "id_rsa"), 0600)
        p = Popen(["ssh-keygen", "-y", "-f",
                   os.path.join(sshdir, "id_rsa")], stdout=PIPE, stderr=PIPE)
        pubkey, err = p.communicate()
        owner = "%s:%s" % (user.pw_name, grp.getgrgid(user.pw_gid).gr_name)
        check_call(["chown", "-R", owner, sshdir])
    else:
        with open(os.path.join(sshdir, "id_rsa.pub"), "r+") as fh:
            pubkey = fh.read()
    return pubkey


def neutron_prep():
    # look for an 'evsuser'
    try:
        evsuser = pwd.getpwnam("evsuser")
    except KeyError:
        # no 'evsuser' on system.  Go create one
        print "creating 'evsuser' account"
        check_call(["useradd", "-d", "/var/lib/evsuser", "-m", "evsuser"])
        evsuser = pwd.getpwnam("evsuser")
    neutronuser = pwd.getpwnam("neutron")
    root = pwd.getpwnam("root")

    print "creating ssh keys"
    evsuser_pubkey = create_pubkey(evsuser)
    neutron_pubkey = create_pubkey(neutronuser)
    root_pubkey = create_pubkey(root)

    print "setting .ssh/config"
    ssh_config = "Host *\n\tStrictHostKeyChecking no\n"
    for user in [evsuser, neutronuser, root]:
        with open(os.path.join(user.pw_dir, ".ssh", "config"), "w") as fh:
            fh.write(ssh_config)

    print "populating authorized_keys"
    path = os.path.join(evsuser.pw_dir, ".ssh", "authorized_keys")
    with open(path, "w") as fh:
        fh.write(evsuser_pubkey)
        fh.write(neutron_pubkey)
        fh.write(root_pubkey)

    owner = "%s:%s" % (evsuser.pw_name, grp.getgrgid(evsuser.pw_gid).gr_name)
    check_call(["chown", "-R", owner,
               os.path.join(evsuser.pw_dir, ".ssh", "authorized_keys")])


def neutron(sqlite):
    neutron_prep()

    print "configuring EVS"
    check_call(['evsadm', 'set-prop', '-p',
                'controller=ssh://evsuser@localhost'])

    try:
        check_call(["evsadm"])
    except CalledProcessError:
        raise RuntimeError("Unable to call evsadm.")

    try:
        check_call(["dladm", "show-etherstub", "l3stub0"], stdout=PIPE,
                   stderr=PIPE)
    except CalledProcessError:
        # l3stub0 not found, go create it
        try:
            check_call(["dladm", "create-etherstub", "l3stub0"])
        except CalledProcessError:
            raise RuntimeError("Unable to create etherstub")

    check_call(['evsadm', 'set-controlprop', '-p', 'l2-type=vlan'])
    check_call(['evsadm', 'set-controlprop', '-p', 'uplink-port=l3stub0'])
    check_call(['evsadm', 'set-controlprop', '-p', 'vlan-range=200-300'])
    check_call(['ipadm', 'set-prop', '-p', 'forwarding=on', 'ipv4'])

    print "configuring neutron"
    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/neutron/neutron.conf"))
    config.set("DEFAULT", "allow_overlapping_ips", "False")
    if not sqlite:
        config.set("database", "connection",
                   "mysql://neutron:neutron@localhost/neutron")
    else:
        config.set("database", "connection",
                   "sqlite:////var/lib/neutron/neutron.sqlite")

    if not config.has_section("keystone_authtoken"):
        config.add_section("keystone_authtoken")
    config.set("keystone_authtoken", "auth_host", "127.0.0.1")
    config.set("keystone_authtoken", "auth_port", "35357")
    config.set("keystone_authtoken", "auth_protocol", "http")
    config.set("keystone_authtoken", "admin_tenant_name", "service")
    config.set("keystone_authtoken", "admin_user", "neutron")
    config.set("keystone_authtoken", "admin_password", "neutron")
    config.set("keystone_authtoken", "signing_dir",
               "/var/lib/neutron/keystone-signing")
    with open("/etc/neutron/neutron.conf", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/neutron/api-paste.ini"))
    config.set("filter:authtoken", "admin_tenant_name", "service")
    config.set("filter:authtoken", "admin_user", "neutron")
    config.set("filter:authtoken", "admin_password", "neutron")
    config.set("filter:authtoken", "auth_uri", "http://127.0.0.1:5000/v2.0/")
    config.set("filter:authtoken", "identity_uri", "http://127.0.0.1:35357")
    with open("/etc/neutron/api-paste.ini", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/neutron/l3_agent.ini"))
    config.set("DEFAULT", "enable_metadata_proxy", "True")
    with open("/etc/neutron/l3_agent.ini", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/neutron/metadata_agent.ini"))
    config.set("DEFAULT", "admin_tenant_name", "service")
    config.set("DEFAULT", "admin_user", "neutron")
    config.set("DEFAULT", "admin_password", "neutron")
    config.set("DEFAULT", "auth_url", "http://127.0.0.1:5000/v2.0/")
    config.set("DEFAULT", "nova_metadata_ip", "127.0.0.1")
    config.set("DEFAULT", "nova_metadata_port", "8775")
    config.set("DEFAULT", "metadata_proxy_shared_secret", "seCr3t")
    with open("/etc/neutron/metadata_agent.ini", "wb") as fh:
        config.write(fh)

    print "enabling neutron services"
    check_call(["/usr/sbin/svcadm", "enable", "-rs", "ipfilter"])
    check_call(["/usr/sbin/svcadm", "enable", "-rs", "neutron-server",
                "neutron-dhcp-agent", "neutron-metadata-agent"])

    print "testing neutron"
    print "neutron networks:"
    check_call(["neutron", "net-list"],
               env={"OS_AUTH_URL": "http://localhost:5000/v2.0",
                    "OS_PASSWORD": "neutron",
                    "OS_USERNAME": "neutron",
                    "OS_TENANT_NAME": "service"})


def nova(sqlite):
    print "configuring nova"
    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/nova/nova.conf"))
    config.set("DEFAULT", "firewall_driver",
               "nova.virt.firewall.NoopFirewallDriver")
    config.set("DEFAULT", "neutron_url", "http://localhost:9696")
    config.set("DEFAULT", "neutron_admin_username", "neutron")
    config.set("DEFAULT", "neutron_admin_password", "neutron")
    config.set("DEFAULT", "neutron_admin_tenant_name", "service")
    config.set("DEFAULT", "neutron_admin_auth_url",
               "http://localhost:5000/v2.0")
    config.set("DEFAULT", "neutron_auth_strategy", "keystone")
    config.set("DEFAULT", "network_driver", "nova.network.solaris_net")

    # Set VNC console configuration
    proxy_port = "6080"
    ext_ip = get_external_ip() or "127.0.0.1"
    config.set("DEFAULT", "vnc_enabled", "true")
    config.set("DEFAULT", "vncserver_listen", "0.0.0.0")
    config.set("DEFAULT", "novncproxy_port", proxy_port)
    config.set("DEFAULT", "novncproxy_base_url",
               "http://" + ext_ip + ":" + proxy_port + "/vnc_auto.html")
    config.set("DEFAULT", "novncproxy_host", "0.0.0.0")

    if not sqlite:
        config.set("database", "connection",
                   "mysql://nova:nova@localhost/nova")

    # get the number of CPUs so we can throttle down the requests made against
    # rabbitmq
    p = Popen(["psrinfo", "-p"], stdout=PIPE, stderr=PIPE)
    out, err = p.communicate()
    workers = out.strip()
    config.set("DEFAULT", "metadata_workers", workers)
    config.set("DEFAULT", "osapi_compute_workers", workers)
    config.set("DEFAULT", "ec2_workers", workers)
    config.set("conductor", "workers", workers)

    if not config.has_section("neutron"):
        config.add_section("neutron")
    config.set("neutron", "service_metadata_proxy", "True")
    config.set("neutron", "metadata_proxy_shared_secret", "seCr3t")

    with open("/etc/nova/nova.conf", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/nova/api-paste.ini"))
    config.set("filter:authtoken", "admin_tenant_name", "service")
    config.set("filter:authtoken", "admin_user", "nova")
    config.set("filter:authtoken", "admin_password", "nova")
    config.set("filter:authtoken", "auth_uri", "http://127.0.0.1:5000/v2.0/")
    config.set("filter:authtoken", "identity_uri", "http://127.0.0.1:35357")
    with open("/etc/nova/api-paste.ini", "wb") as fh:
        config.write(fh)

    print "enabling nova services"
    check_call(["/usr/sbin/svcadm", "enable", "-rs", "nova-conductor"])
    # sleep for a few seconds to let SMF catch up
    time.sleep(2)

    check_call(["/usr/sbin/svcadm", "enable", "-rs", "nova-api-ec2",
                "nova-api-osapi-compute", "nova-scheduler",
                "nova-cert", "nova-compute", "nova-api-metadata",
                "nova-consoleauth", "nova-novncproxy"])

    # sleep for a few seconds to let SMF catch up
    time.sleep(2)

    print "testing nova"
    print "nova endpoints:"
    check_call(["nova", "endpoints"],
               env={"OS_AUTH_URL": "http://localhost:5000/v2.0",
                    "OS_PASSWORD": "nova",
                    "OS_USERNAME": "nova",
                    "OS_TENANT_NAME": "service"})

    print "nova list:"
    check_call(["nova", "list"],
               env={"OS_AUTH_URL": "http://localhost:5000/v2.0",
                    "OS_PASSWORD": "nova",
                    "OS_USERNAME": "nova",
                    "OS_TENANT_NAME": "service"})


def cinder(sqlite):
    print "configuring cinder"
    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/cinder/cinder.conf"))
    config.set("DEFAULT", "my_ip", "localhost")
    config.set("DEFAULT", "scheduler_driver",
               "cinder.scheduler.filter_scheduler.FilterScheduler")
    config.set("DEFAULT", "zfs_volume_base", "rpool/cinder")
    config.set("DEFAULT", "san_is_local", "true")
    if not sqlite:
        config.set("database", "connection",
                   "mysql://cinder:cinder@localhost/cinder")

    with open("/etc/cinder/cinder.conf", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/cinder/api-paste.ini"))
    config.set("filter:authtoken", "admin_tenant_name", "service")
    config.set("filter:authtoken", "admin_user", "cinder")
    config.set("filter:authtoken", "admin_password", "cinder")
    config.set("filter:authtoken", "signing_dir",
               "/var/lib/cinder/keystone-signing")
    with open("/etc/cinder/api-paste.ini", "wb") as fh:
        config.write(fh)

    print "enabling cinder services"
    check_call(["/usr/sbin/svcadm", "enable", "-rs", "cinder-api", "cinder-db",
        "cinder-backup", "cinder-scheduler", "cinder-volume:setup",
        "cinder-volume:default"])

    # sleep for a few seconds to let SMF catch up
    time.sleep(2)

    print "testing cinder"
    print "cinder list:"
    check_call(["cinder", "list"],
               env={"OS_AUTH_URL": "http://localhost:5000/v2.0",
                    "OS_PASSWORD": "cinder",
                    "OS_USERNAME": "cinder",
                    "OS_TENANT_NAME": "service"})


def horizon():
    print "configuring horizon"
    # who loves sed?
    cmd = ["gsed", '-i',
           "-e", "s@SECURE_PROXY_SSL_HEADER@#SECURE_PROXY_SSL_HEADER@",
           "-e", "s@CSRF_COOKIE_SECURE@#CSRF_COOKIE_SECURE@",
           "-e", "s@SESSION_COOKIE_SECURE@#SESSION_COOKIE_SECURE@",
           "/etc/openstack_dashboard/local_settings.py"]
    try:
        check_call(cmd)
    except OSError:
        print "text/gnu-sed not installed: skipping horizon configuration."
        return

    shutil.copy("/etc/apache2/2.4/samples-conf.d/openstack-dashboard-http.conf",
                "/etc/apache2/2.4/conf.d")

    cmd = ["svcs", "-H", "-o", "state", "apache24"]
    p = Popen(cmd, stdout=PIPE, stderr=PIPE)
    out, err = p.communicate()
    if out.strip() == "disabled":
        check_call(["/usr/sbin/svcadm", "enable", "apache24"])
    else:
        check_call(["/usr/sbin/svcadm", "restart", "apache24"])


def swift():
    print "configuring swift"
    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/swift/proxy-server.conf"))
    if not config.has_section("filter:authtoken"):
        config.add_section("filter:authtoken")
    config.set("filter:authtoken", "admin_tenant_name", "service")
    config.set("filter:authtoken", "admin_user", "swift")
    config.set("filter:authtoken", "admin_password", "swift")
    config.set("filter:authtoken", "signing_dir",
      "/var/lib/swift/keystone-signing")
    # We might be upgrading from an existing swift configuration that doesn't
    # have the defaults in the new packages ...
    if "keystoneauth" not in config.get("pipeline:main", "pipeline"):
        config.set("pipeline:main", "pipeline", "catch_errors healthcheck "
          "proxy-logging cache slo ratelimit tempauth container-quotas "
          "account-quotas authtoken keystoneauth proxy-logging proxy-server")
        config.set("app:proxy-server", "account_autocreate", "true")
        config.set("filter:authtoken", "paste.filter_factory",
          "keystoneclient.middleware.auth_token:filter_factory")
        config.set("filter:authtoken", "auth_host", "127.0.0.1")
        config.set("filter:authtoken", "auth_port", "35357")
        config.set("filter:authtoken", "auth_protocol", "http")
        config.set("filter:authtoken", "auth_uri", "http://127.0.0.1:5000/")
        config.set("filter:authtoken", "delay_auth_decision", "1")
        config.set("filter:authtoken", "cache", "swift.cache")
        config.set("filter:authtoken", "include_service_catalog", "False")
        if not config.has_section("filter:keystoneauth"):
            config.add_section("filter:keystoneauth")
        config.set("filter:keystoneauth", "use", "egg:swift#keystoneauth")
    with open("/etc/swift/proxy-server.conf", "wb") as fh:
        config.write(fh)

    print "building rings"

    def rb(type, action, *args):
        check_call(["/usr/bin/swift-ring-builder",
          "/etc/swift/%s.builder" % type, action] + list(args))

    port = {"object": 6000, "container": 6001, "account": 6002}
    ipv4addr = get_external_ip() or "127.0.0.1"
    if ipv4addr != "127.0.0.1":
        print "swift cluster using %s on net0" % ipv4addr
    else:
        ipv4addr = "127.0.0.1"
        print "swift cluster using %s on loopback" % ipv4addr
        print "You may want to change this with:"
        print "    # swift-ring-builder /etc/swift/<type>.builder set_info 127.0.0.1 <ip>"
        print "    # swift-ring-builder /etc/swift/<type>.builder write_ring"
        print "where <type> is set to 'object', 'container', and 'account' and"
        print "<ip> is set to the IP address you want the cluster to use."
    for t in port.keys():
        rb(t, "create", "10", "3", "1")
        rb(t, "add", "r1z1-%s:%s/disk0" % (ipv4addr, port[t]), "100")
        rb(t, "rebalance")

    print "creating ZFS datasets"
    try:
        check_call(["/usr/sbin/zfs", "list", "rpool/export/swift"],
                   stdout=PIPE, stderr=PIPE)
    except:
        # doesn't exist; create it
        check_call(["/usr/sbin/zfs", "create", "-o", "mountpoint=none",
          "rpool/export/swift"])

    try:
        check_call(["/usr/sbin/zfs", "list", "rpool/export/swift/srv"],
                   stdout=PIPE, stderr=PIPE)
    except:
        # doesn't exist; create it
        check_call(["/usr/sbin/zfs", "create", "-o", "mountpoint=/srv",
          "rpool/export/swift/srv"])

    try:
        check_call(["/usr/sbin/zfs", "list", "rpool/export/swift/srv/node"],
                   stdout=PIPE, stderr=PIPE)
    except:
        # doesn't exist; create it
        check_call(["/usr/sbin/zfs", "create", "rpool/export/swift/srv/node"])

    try:
        check_call(["/usr/sbin/zfs", "list",
                    "rpool/export/swift/srv/node/disk0"],
                    stdout=PIPE, stderr=PIPE)
    except:
        # doesn't exist; create it
        check_call(["/usr/sbin/zfs", "create",
                    "rpool/export/swift/srv/node/disk0"])

    check_call(["/usr/bin/chown", "-R", "swift:swift", "/srv"])
    check_call(["/usr/bin/chown", "-R", "swift:swift", "/etc/swift"])

    print "enabling swift services"
    check_call(["/usr/sbin/svcadm", "enable", "-rs",
      "swift-replicator-rsync", "swift-account-replicator",
      "swift-container-sync", "swift-container-server", "swift-account-auditor",
      "swift-container-updater", "swift-container-reconciler",
      "swift-container-replicator", "swift-container-auditor",
      "swift-account-reaper", "swift-account-server", "swift-object-expirer",
      "swift-object-auditor", "swift-object-server", "swift-object-replicator",
      "swift-object-updater", "swift-proxy-server"])

    # sleep for a few seconds to let SMF catch up
    time.sleep(2)

    print "testing swift"
    env = {
      "OS_AUTH_URL": "http://localhost:5000/v2.0",
      "OS_USERNAME": "admin",
      "OS_PASSWORD": "secrete",
      "OS_TENANT_NAME": "demo"
    }
    check_call(["swift", "upload", "junk", "/etc/motd"], env=env)
    check_call(["swift", "stat", "junk", "etc/motd"], env=env)
    try:
        os.unlink("/tmp/swifttest")
    except:
        pass
    check_call(["swift", "download", "-o", "/tmp/swifttest", "junk",
                "etc/motd"],
      env=env)

    check_call(["diff", "/tmp/swifttest", "/etc/motd"])
    try:
        os.unlink("/tmp/swifttest")
    except:
        pass


def heat(sqlite):
    print "configuring heat"
    check_call(["/usr/demo/openstack/keystone/heat-keystone-setup"],
               env={"OS_AUTH_URL": "http://localhost:5000/v2.0",
                    "OS_PASSWORD": "secrete",
                    "OS_USERNAME": "admin",
                    "OS_TENANT_NAME": "demo"})

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/heat/heat.conf"))

    if not sqlite:
        config.set("database", "connection",
                   "mysql://heat:heat@localhost/heat")

    config.set("keystone_authtoken", "admin_tenant_name", "service")
    config.set("keystone_authtoken", "admin_user", "heat")
    config.set("keystone_authtoken", "admin_password", "heat")
    with open("/etc/heat/heat.conf", "wb") as fh:
        config.write(fh)

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/heat/api-paste.ini"))
    config.set("filter:authtoken", "admin_user", "heat")
    config.set("filter:authtoken", "admin_password", "heat")
    config.set("filter:authtoken", "admin_tenant_name", "service")
    config.set("filter:authtoken", "auth_uri", "http://127.0.0.1:5000/v2.0/")
    config.set("filter:authtoken", "identity_uri", "http://127.0.0.1:35357")
    with open("/etc/heat/api-paste.ini", "wb") as fh:
        config.write(fh)

    print "enabling heat services"
    check_call(["/usr/sbin/svcadm", "enable", "-rs", "heat-api", "heat-db",
                "heat-engine", "heat-api-cfn", "heat-api-cloudwatch"])

    # sleep for a few seconds to let SMF catch up
    time.sleep(2)

    print "testing heat"
    print "heat stack-list:"
    check_call(["heat", "stack-list"],
               env={"OS_AUTH_URL": "http://localhost:5000/v2.0",
                    "OS_USERNAME": "admin",
                    "OS_PASSWORD": "secrete",
                    "OS_TENANT_NAME": "demo"})


def ironic_prep():
    """Prepare ironic user for SSH authentication"""
    ironic = pwd.getpwnam("ironic")

    print "creating ssh keys"
    ironic_pubkey = create_pubkey(ironic)

    print "setting .ssh/config"
    ssh_config = "Host *\n\tStrictHostKeyChecking no\n"
    with open(os.path.join(ironic.pw_dir, ".ssh", "config"), "w") as fh:
        fh.write(ssh_config)

    print "populating authorized_keys"
    path = os.path.join(ironic.pw_dir, ".ssh", "authorized_keys")
    with open(path, "w") as fh:
        fh.write(ironic_pubkey)

    owner = "%s:%s" % (ironic.pw_name, grp.getgrgid(ironic.pw_gid).gr_name)
    check_call(["chown", "-R", owner,
               os.path.join(ironic.pw_dir, ".ssh", "authorized_keys")])


def ironic(sqlite):
    """Configure Ironic for Single Node"""
    print "configuring ironic"

    ironic_prep()

    # Check if keystone installed, if not use noauth
    pr = Popen(['pkg', 'info', 'cloud/openstack/keystone'],
               stdout=PIPE, stderr=PIPE)
    _out, _err = pr.communicate()
    keystone = (pr.returncode == 0)

    print "configuring ironic"
    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/ironic/ironic.conf"))
    if not keystone:
        config.set("DEFAULT", "auth_strategy", "noauth")
    else:
        config.set("DEFAULT", "auth_strategy", "keystone")
    config.set("DEFAULT", "enabled_drivers", "solaris")
    config.set("ai", "server", "localhost")
    config.set("ai", "username", "ironic")
    config.set("ai", "port", "22")
    config.set("ai", "timeout", "10")
    config.set("ai", "deploy_interval", "30")
    config.set("ai", "ssh_key_file", "/var/lib/ironic/.ssh/id_rsa")
    config.set("conductor", "api_url", "http://localhost:6385/")
    config.set("conductor", "heartbeat_interval", "60")
    config.set("conductor", "heartbeat_timeout", "60")
    config.set("conductor", "check_provision_state_interval", "120")
    config.set("conductor", "sync_power_state_interval", "300")
    if not sqlite:
        config.set("database", "connection",
                   "mysql://ironic:ironic@localhost/ironic")
    else:
        config.set("database", "connection",
                   "sqlite:////var/lib/ironic/ironic.sqlite")
    config.set("neutron", "url", "http://localhost:9696")

    # Glance host needs to be external IP not 127.0.0.1
    # Otherwise AI Client won't be able to find real glance host
    ext_ip = get_external_ip() or "127.0.0.1"

    config.set("glance", "glance_host", ext_ip)
    config.set("glance", "glance_port", "9292")
    config.set("glance", "glance_protocol", "http")
    config.set("glance", "glance_api_servers", "%s:9292" % ext_ip)

    config.set("solaris_ipmi", "imagecache_dirname", "/var/lib/ironic/images")
    config.set("solaris_ipmi", "imagecache_lock_timeout", "60")

    if not keystone:
        config.set("glance", "auth_strategy", "noauth")
    else:
        config.set("glance", "auth_strategy", "keystone")
        config.set("keystone_authtoken", "auth_host", "127.0.0.1")
        config.set("keystone_authtoken", "auth_url",
                   "http://127.0.0.1:5000/v2.0")
        config.set("keystone_authtoken", "admin_user", "ironic")
        config.set("keystone_authtoken", "admin_password", "ironic")
        config.set("keystone_authtoken", "admin_tenant_name", "service")
        config.set("keystone_authtoken", "signing_dir",
                   "/var/lib/ironic/keystone-signing")
        config.set("keystone_authtoken", "identity_uri",
                   "http://127.0.0.1:35357")

    with open("/etc/ironic/ironic.conf", "wb") as fh:
        config.write(fh)

    print "enabling ironic services"
    check_call(["/usr/sbin/svcadm", "enable", "-rs", "ironic-db"])

    check_call(["/usr/sbin/svcadm", "enable", "-rs", "ironic-api",
                "ironic-conductor"])

    # sleep for a few seconds to let SMF catch up
    time.sleep(2)

    print "testing ironic"
    print "ironic driver-list:"
    if keystone:
        check_call(["ironic", "driver-list"],
                   env={"OS_AUTH_URL": "http://localhost:5000/v2.0",
                        "OS_USERNAME": "admin",
                        "OS_PASSWORD": "secrete",
                        "OS_TENANT_NAME": "demo"})
    else:
        check_call(["ironic", "driver-list"],
                   env={"OS_AUTH_URL": "http://localhost:5000/v2.0",
                        "OS_USERNAME": "admin",
                        "OS_PASSWORD": "secrete",
                        "OS_AUTH_TOKEN": "fake-token",
                        "OS_TENANT_NAME": "demo"})

    print "NOTE: Ironic expecting AI Server on localhost"


def parse_args(args=sys.argv[1:]):
    parser = OptionParser()
    parser.add_option('--sqlite', help='user sqlite instead of mysql',
                      action='store_true', dest='sqlite')
    options, args = parser.parse_args(args)

    return options, args


@with_spinner
def pkg_install(pkg):

    swrite = lambda x: sys.stdout.write('\r' + x + '   ')

    todo = []
    if isinstance(pkg, str):
        pkg = [pkg]

    for p in pkg:
        cmd = ['pkg', 'list', p]
        try:
            check_call(cmd, stdout=PIPE, stderr=PIPE)
        except CalledProcessError:
            todo.append(p)

    if not todo:
        return

    swrite('installing %s' % ", ".join(pkg))
    cmd = ['pkg', 'install', '--accept']
    cmd.extend(pkg)

    p = Popen(cmd, stdout=PIPE, stderr=PIPE)
    out, err = p.communicate()
    if p.returncode not in (0, 4):
        swrite('Error installing: %s' % pkg)
        swrite('---')
        swrite(out)
        swrite('---')
        swrite(err)


def main(args):
    options, args = parse_args()

    if not args:
        args = ["keystone", "glance", "nova", "cinder", "horizon", "swift",
                "heat", "neutron", "ironic"]

    cmd = ["svcadm", "restart", "rad:local"]
    check_call(cmd)

    # install rabbit if needed and start it
    pkg_install('rabbitmq')
    cmd = ["svcs", "-H", "-o", "state", "rabbitmq"]
    p = Popen(cmd, stdout=PIPE, stderr=PIPE)
    out, err = p.communicate()
    if out.strip() == "disabled":
        check_call(["/usr/sbin/svcadm", "enable", "-rs", "rabbitmq"])

    if not options.sqlite:
        # install mysql if needed and start it
        pkg_install(['mysql-55', 'mysql-55/client', 'python-mysql'])
        cmd = ["svcs", "-H", "-o", "state", "mysql"]
        p = Popen(cmd, stdout=PIPE, stderr=PIPE)
        out, err = p.communicate()
        if out.strip() == "disabled":
            check_call(["/usr/sbin/svcadm", "enable", "-rs", "mysql"])

        # sleep for 2 seconds to allow SMF to catch up
        time.sleep(2)

        # ignore the Deprecation warning from importing MySQLdb
        warnings.filterwarnings("ignore")
        import MySQLdb
        # create mysql databases
        for i in range(5):
            try:
                db = MySQLdb.connect('localhost', 'root')
                cursor = db.cursor()
                break
            except Exception as err:
                # mysql isn't ready.  sleep for 2 more seconds
                time.sleep(2)
        else:
            sys.exit('unable to connect to mysql: %s' % err)

        dbs = ["nova", "cinder", "glance", "keystone", "heat", "neutron",
               "ironic"]

        # Get list of already existinng databases:
        cursor.execute("SHOW DATABASES")
        databases = cursor.fetchall()
        existing_dbs = [database[0] for database in databases]

        for name in (db_name for db_name in dbs if db_name not in existing_dbs):
            # Check if dbs exists, create/grant of it does not
            print '\ncreating MySQL database %s' % (name)
            cursor.execute('CREATE DATABASE %s '
                           'DEFAULT CHARACTER SET utf8 '
                           'DEFAULT COLLATE utf8_general_ci;' % name)
            cursor.execute("GRANT ALL PRIVILEGES ON %s.* TO '%s'@'localhost' IDENTIFIED BY '%s';" % (name, name, name))
        cursor.execute("FLUSH PRIVILEGES;")
        db.commit()
        db.close()

    if "keystone" in args:
        keystone(options.sqlite)

    if "glance" in args:
        glance(options.sqlite)

    if "nova" in args:
        nova(options.sqlite)

    if "cinder" in args:
        cinder(options.sqlite)

    if "horizon" in args:
        horizon()

    if "neutron" in args:
        neutron(options.sqlite)

    if "swift" in args:
        swift()

    if "heat" in args:
        heat(options.sqlite)

    if "ironic" in args:
        ironic(options.sqlite)

if __name__ == "__main__":
    main(sys.argv[1:])
