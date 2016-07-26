= README file for OI-Userland delivery of ClamAV

== Overview

ClamAV is a multi-tiered system to scan static contents (emails, files,
web-proxy download pages, etc.) for viruses and other fingerprinted
malware. It is not a run-time antivirus that can catch exploits already
running in your RAM; however there are protocol clients that can integrate
with your local (ZFS) or networked (Samba) filesystem provider to prevent
malware files from getting written in the first place.

In a few words: ClamAV includes a scanning engine that uses up-to-date
virus definition databases (that you should download regularly) and is
accessible both with a local command-line tool `clamscan` for singular
invokations, and for streamlined usage - with a server process `clamd`
that absorbs the impact of loading and tracking the definitions database.
There are multiple clients that can connect to the `clamd` server, such
as the `clamdscan` for command-line usage; `clamav-milter` for email
scanning with Sendmail, Postfix and Sun Messaging Server among others;
or the `C-ICAP` project for many other clients including Squid, ZFS
and Samba, a SpamAssassin plugin, etc.

It is expected that ultimate deployments might not want to run all of
the components in the same operating environment. In particular, the
maintenance of a local copy of the virus definitions database adds a
considerable storage and internet-traffic overhead which would be not
needed on systems that do not run `clamd` or other implementations of
the scanning engine directly.

This expectation is partially met by packaging that allows the sysadmin
to "cherry pick" those components needed in a particular zone, and
partially by not delivering any configuration (nor quickly obsoleted
databases) out of the box.

== Configuring your deployment of ClamAV

Sample configuration files are delivered into `/usr/share/clamav/`.
These include "vanilla" examples from the distribution, as well as
`*.sol` files tuned for a typical deployment of this package on OI.

There is also a script `clamav-enable.sh` that can inspect which of
the components you have installed, so it would copy sample configs
into `/etc/clamav/` (of course, if there are no such files already
set up there) and starts the services. For a `clamd` deployment it
would also start `freshclam.sh` (wrapper for `freshclam` delivered
by this package) to download the initial virus definition databases
before starting the server for the first time.

Hope this helps,
Jim Klimov
