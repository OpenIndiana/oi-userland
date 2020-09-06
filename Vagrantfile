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
# Copyright 2017 Michal Nowak
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
    # workaround. The problem with vagrant is that it creates folder as root:root,
    # but rsync connects as vagrant and thus fails to write.
    config.vm.synced_folder ".", "/vagrant", type: "rsync",
      rsync__args: ["--verbose", "--archive", "-zz", "--copy-links"],
      rsync__rsync_path: "pfexec rsync", owner: "vagrant", group: "vagrant"

    # Autoconfigure resources for development VM. The snippet is taken from
    # https://stefanwrobel.com/how-to-make-vagrant-performance-not-suck.
    # We allocate 1/4 of available system memory and CPU core count of the host
    # to the VM, so performance does not suck.
    host = RbConfig::CONFIG['host_os']

    # Get memory size and CPU cores amount
    if host =~ /darwin/
        # sysctl returns Bytes
        mem = `sysctl -n hw.memsize`.to_i
        cpus = `sysctl -n hw.ncpu`.to_i
    elsif host =~ /linux/
        # meminfo shows size in kB; convert to Bytes
        mem = `awk '/MemTotal/ {print $2}' /proc/meminfo`.to_i * 1024
        cpus = `getconf _NPROCESSORS_ONLN`.to_i
    elsif host =~ /mswin|mingw|cygwin/
        # Windows code via https://github.com/rdsubhas/vagrant-faster
        mem = `wmic computersystem Get TotalPhysicalMemory`.split[1].to_i
        cpus = `echo %NUMBER_OF_PROCESSORS%`.to_i
    end

    # Give VM 1/4 system memory as well as CPU core count
    mem /= 1024 ** 2 * 4
    cpus /= 4

    config.vm.provider "virtualbox" do |v|
        v.customize ["modifyvm", :id, "--memory", mem]
        v.customize ["modifyvm", :id, "--cpus", cpus]
        v.customize ["storagectl", :id, "--name", "SATA Controller", "--hostiocache", "on"]
        # Enable following line, if oi-userland directory is on non-rotational
        # drive (e.g. SSD). (This could be automated, but with all those storage
        # technologies (LVM, partitions, ...) on all three operationg systems,
        # it's actually error prone to detect it automatically.) macOS has it
        # enabled by default as recent Macs have SSD anyway.
        if host =~ /darwin/
            v.customize ["storageattach", :id, "--storagectl", "SATA Controller", "--port", 0, "--nonrotational", "on"]
        else
            #v.customize ["storageattach", :id, "--storagectl", "SATA Controller", "--port", 0, "--nonrotational", "on"]
        end
        # Should we ever support `--discard` option, we need to switch to VDI
        # virtual disk format first.
        #v.customize ["storageattach", :id, "--storagectl", "SATA Controller", "--port", 0, "--discard", "on"]
	config.vm.synced_folder ".", "/vagrant_mounted"
    end

    config.vm.provider :libvirt do |libvirt|
        libvirt.memory = mem
        libvirt.cpus = cpus
    end

    # Once vagrant is able to chown files on OpenIndiana, chown line should be
    # removed from this part.
    config.vm.provision "shell", inline: <<-SHELL
        pfexec chown -R vagrant:vagrant /vagrant
        pfexec pkg install build-essential

        cd /vagrant && gmake setup
        pfexec pkg set-publisher --non-sticky -g file:///vagrant/i386/repo userland
        pfexec pkg set-publisher --non-sticky openindiana.org
        echo "VM is ready, happy contributing!"
    SHELL
end
