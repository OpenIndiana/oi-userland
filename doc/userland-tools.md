
# userland-tools

oi-userland comes with some tools used all over the build system and
these tools reside in the [tools/](https://github.com/OpenIndiana/oi-userland/tree/oi/hipster/tools) directory.

## userland-fetch
_userland-fetch_ is a tool to download and verify remote archives and files.
The build system uses it to download all archive packages. It takes care of download security testing,
gpg verification, checksum verification, partial downloads/continuation, and storing hash files.


### Notes

* Use `--hash <algorithm>:<checksum>` to skip `HASH_DIR` checking for a download.
* Use `--hash none` to skip all hash checking for a download.
* Use `--sigurl <URL>` to set the exact GPG signature to check.
This signature will be saved locally for future use.
* Use `--sigurl none` to skip all signature checking for a download.
* Use `--keep` to stop _userland-fetch_ from deleting any files.
* Use `-nN` to force checking of both signature and hash.
* Use `--search` to add a URL to the list to query for files, signatures and hashes.
  Can be used more than once.

##### protocols
_userland-fetch_ decides whether a download protocol is secure by checking the `SECURE_PROTOCOLS` envvar.
This can be set to a space-delimited list of schemes. (URLs are in the form `<scheme>://<resource>`)
**Override with caution!**

##### verification
_userland-fetch_ uses the following rules to determine the validity of a download:
* confirm the file has a good signature, using each extension in `SIGNATURE_EXTENSIONS`, OR
* confirm the file has a correct hash entry in a file in `HASH_DIR`, OR
* check if `URL` scheme is in `SECURE_PROTOCOLS` and `ALLOW_UNVERIFIED_DOWNLOADS=yes`.

Downloaded hash files are also checked for signatures and protocol security.

##### signature extensions
_userland-fetch_ searches for signature files with the extensions listed in the `SIGNATURE_EXTENSIONS` envvar.
If you find a strange extension for a remote signature, you can add it to `SIGNATURE_EXTENSIONS`, but keep
in mind that the file must be a detached GPG signature.

##### hashfiles and hash directory
_userland-fetch_ checks the envvar `HASH_DIR` to find the path to search for and store hashfiles. It will search
each file in `HASH_DIR` for a hash entry containing the basename of `--file <path>`, or the basename of `--url <URL>`, stopping on the first match. Subsequent matches are ignored. Files are checked in `sorted()` order.

_userland-fetch_ will strip directory information from the hashfiles when scanning them. The hashfiles themselves
are not altered. (I.E. `<hash>  a/b/file.txt` becomes `<hash>  file.txt` internally, so it will match)

In the event of an erroneous match, you can add a hashfile to the hashes directory manually, or
have it download with the build in a Makefile target:
```
$(HASH_DIR)/<filename>:
	$(FETCH) -N --url <URL> --file $@
download:: $(HASH_DIR)/<filename>
```

### Defaults
```
ALLOW_UNVERIFIED_DOWNLOADS=no
SECURE_PROTOCOLS=https
HASH_DIR=<file_arg directory>/hashes; 	(if --file <filename>)
HASH_DIR=<current directory>/hashes ; 	(if no --file argument)
SIGNATURE_EXTENSIONS=sig asc		;	(space delimited, no '.' prefix)
DEFAULT_HASH_FILES=SHA256SUMS sha256sums.txt sha256sum.txt	(space delimited)
DEFAULT_HASH_ALGO=sha256	(this is sent directly to python's hashlib.new() - only set one algorithm)
```

### Use cases

`userland-fetch --url <URL>`
* Download the file at URL, placing it in the current directory.
* Skip downloading if the output file already exists.
* Verify the download or file using the method stated above.

`userland-fetch --url <URL> --file <path>`
* Same as above, but output the download to `path`.

`userland-fetch -gn --url <URL>`
* Download the file at `URL`, placing it in the current directory.
* Look for these hash files in `URL`'s remote directory:
* * Filenames in the `DEFAULT_HASH_FILES` envvar
* * A few styles of `<filename>.DEFAULT_HASH_ALGO`
* If a local copy of a hashfile exists, use it instead of downloading the remote one
* Search hashfiles for an entry matching the filename; stop on first match.
* Verify the download, ensuring that a correct hash is present.

`userland-fetch -c --url <URL>`
* Do -g, but replace any files in HASH_DIR with their remote versions.

`userland-fetch -GN --url <URL>`
* Download the file at URL, placing it in the current directory.
* Look for these signature files in `URL`'s remote directory:
* * `<filename>.ext` for each extension in `SIGNATURE_EXTENSIONS`
* If a local copy of a signature exists, __overwrite it__
* Verify the file, ensuring that it has a good signature.

`userland-fetch --file <path>`
* Verify the file using the method stated above; protocol checking is skipped.

`userland-fetch -n --file <path>`
* Ensure a correct hash exists for `path` in HASH_DIR.

`userland-fetch -c --file <path>`
* Same as `userland-fetch -n --file <path>`. 

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


