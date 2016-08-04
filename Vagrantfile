# -*- mode: ruby -*-
# vi: set ft=ruby :
#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Adam Stevko. All rights reserved.
#

Vagrant.configure("2") do |config|
  # Every Vagrant development environment requires a box. You can search for
  # boxes at https://atlas.hashicorp.com/search.
  config.vm.box = "openindiana/hipster"

  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  config.vm.box_check_update = true

  # Unless OpenIndiana is better supported in vagrant, we have to use this
  # workaround. The problem is with vagrant creating folder as root:root,
  # but rsync connects as vagrant and fails to write.
  config.vm.synced_folder ".", "/vagrant", type: "rsync",
    rsync__args: ["--verbose", "--archive", "-z", "--copy-links"],
    rsync__rsync_path: "pfexec rsync", owner: "vagrant", group: "vagrant"

  # Autoconfigure resources for development VM. The snippet is taken from
  # https://stefanwrobel.com/how-to-make-vagrant-performance-not-suck.
  # We allocate 1/4 of available system memory and CPU core count of the host
  # to the VM, so performance does not suck.
  config.vm.provider "virtualbox" do |v|
    host = RbConfig::CONFIG['host_os']

    # Give VM 1/4 system memory and CPU core count
    if host =~ /darwin/
      # sysctl returns Bytes and we need to convert to MB
      mem = `sysctl -n hw.memsize`.to_i / 1024
      cpus = `sysctl -n hw.ncpu`.to_i / 4
    elsif host =~ /linux/
      # meminfo shows KB and we need to convert to MB
      mem = `grep 'MemTotal' /proc/meminfo | sed -e 's/MemTotal://' -e 's/ kB//'`.to_i / 1024
      cpus = `grep -c Processor /proc/cpuinfo`.to_i / 4
    elsif host =~ /mswin|mingw|cygwin/
      # Windows code via https://github.com/rdsubhas/vagrant-faster
      mem = `wmic computersystem Get TotalPhysicalMemory`.split[1].to_i / 1024
      cpus = 2
    end

    mem = mem / 1024 / 4

    v.customize ["modifyvm", :id, "--memory", mem]
    v.customize ["modifyvm", :id, "--cpus", cpus]
  end

  # Once vagrant is able to chown files on OpenIndiana, chown line should be
  # removed from this part.
  config.vm.provision "shell", inline: <<-SHELL
    pfexec chown -R vagrant:vagrant /vagrant
    pfexec pkg install build-essential

    cd /vagrant && gmake setup
    echo "VM ready, happy contributing!"
  SHELL
end
