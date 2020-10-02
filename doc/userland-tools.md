# userland-tools

oi-userland comes with some tools used all over the build system and 
these tools reside in the [tools/](https://github.com/OpenIndiana/oi-userland/tree/oi/hipster/tools) directory.

## userland-zone

_userland-zone_ is a tool to manage a lifecycle of build zones in oi-userland. 
The intended and main use case is the use in our continuous integration system and provides a clean build environment.
It works in a way that it creates a template zone and all build zones are cloned from it.
To make it easier for new joiners, _userland-zone_ assumes certain things and set some defaults:

* /zones is a ZFS dataset

Recommended way how to create _zones_ dataset:

```shell script
zfs create -o mountpoint=/zones rpool/zones 
```

* **/ws/archives** is present in the global zone and hosts downloaded userland source archives
* **/ws/code** is present in the global zone and has a working copy of oi-userland repository
* template zone is called _prbuilder-template_ and is never running
* build zones are called _prbuilder-ID_ where ID is an identifier passed as an argument
  
When working with _userland-zone_, use the following workflow:

* **userland-zone create-template** - this creates a template zone, which is used as a golden image for other build zones. 

* **userland-zone spawn-zone --id 123** - this creates a build zone, _prbuilder-123_. Once the zone has been built,
**/ws/archives** and **/ws/code** from the global zone will be mounted under the same location inside the build zone.

* The build zone provides no networking, so source tarball will have to be downloaded in the global zone 
in via **gmake download**.

* Once, the source tarball has been downloaded, the build inside the zone can happen via **zlogin prbuilder-123**. 
Inside the zone, execute **cd /ws/code/components/CATEGORY/COMPONENT** and run **gmake publish**. 
The build will proceed in the clean environment of the build zone as expected and the built package will be 
published to the local repository.

*  When the build finished or the build zone is not needed, it can be safely destroyed 
via **userland-zone destroy-zone --id 123**.

* Before every build, it is recommend to update the template zone via **userland-zone update-template**. 
This is especially important in cases when compilers or libraries get updated and developers should always use the latest
bits to build oi-userland components.

* If you want to get rid of the template zone, delete it via **userland-zone delete-template**.


