# Using oi-userland with Vagrant

oi-userland includes Vagrantfile, which allows contributing from non-OpenIndiana
platforms such as Mac OS X, Linux or Windows. Currently, only the VirtualBox
provider is supported. Vagrant is suitable for cases when you don't have access to OpenIndiana host and want to develop/contribute to oi-userland.

## Quickstart

* Download Vagrant from the official [download site](https://www.vagrantup.com/downloads.html). Select a version for your platform. We recommend to use the latest version.
* Download VirtualBox from the official [download site](https://www.virtualbox.org/wiki/Downloads). We recommend to  always use the latest VirtualBox.
* Run the following commands:

  ```
  git clone https://github.com/OpenIndiana/oi-userland.git && \
  cd oi-userland && \
  vagrant up
  ```

## Getting started

* Download Vagrant from the official [download site](https://www.vagrantup.com/downloads.html). Select a version for your platform. We recommend to use the latest version.
* Download VirtualBox from the official [download site](https://www.virtualbox.org/wiki/Downloads). We recommend to use always the latest VirtualBox.
* Fork the [oi-userland repository](https://github.com/OpenIndiana/oi-userland.git) on Github.
* Clone your oi-userland repository somewhere:

  ```
  git clone https://github.com/<username>/oi-userland.git oi-userland
  ```

* Configure remote repository, so you can fetch updates easily:

  ```
  git remote add upstream https://github.com/OpenIndiana/oi-userland.git
  ```

  Updates are fetched with the following commands:

  ```
  git pull --rebase upstream oi/hipster
  ```

* Start the VM by running:

  ```
  vagrant up
  ```

  This might take a while as build utilities will be download and oi-userland configured.

* Once the VM is online, enter it:

  ```
  vagrant ssh
  ```

* When finished, exit the machine and halt down the machine:

  ```
  vagrant halt
  ```

* To destroy the machine, run:

  ```
  vagrant destroy
  ```

## Vagrant box updates

Vagrant box is configured to check for updates and if a new update is available,
Vagrant will display the notice.

## Getting help

If not sure, ask.
