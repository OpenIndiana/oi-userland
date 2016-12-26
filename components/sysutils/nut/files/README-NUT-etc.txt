This is the directory for Network UPS Tools configuration files,
as distributed by OpenIndiana Hipster.

Some example files are provided as `/usr/share/nut/etc-samples/*.sample`.
Actual configuration files are loaded by programs from `/etc/nut`.
General workflow is to modify provided sample configuration files
`/etc/nut/*.conf` as fits your situation.

NOTE: Take care about proper ownership and access bits of configuration
files, especially for those with credentials.

On a NUT server machine that directly tracks UPS states, you must
configure:
* `ups.conf` with a block for each driver configuration (required)
* `upsd.users` with a block for each set of credentials and allowed
  actions so different clients can do different things (required for
  monitoring, `upsrw` CGI and other clients)
* `upsd.conf` can customize `upsd` server settings (optional)

On a NUT client with `upsmon` for graceful shutdown (may be or not be
the same as teh NUT server machine), you must configure:
* `upsmon.conf` with a `MONITOR` line for each monitored UPS, including
  how many power-supplies of this server it feeds, and a `MINSUPPLIES`
  line to define the critical threshold (how many power-supplies should
  have stable external power conditions for the system to not start its
  graceful shutdown when UPS battery goes critical). Note that an admin
  workstation can monitor lots of devices with none (0) feeding it, just
  to aggregate notifications about state changes, etc. in one place.
  There are also other settings to configure for communication frequency,
  shutdown and notifications.

On a NUT client with `upssched` you can configure complex reactions to
change in UPS state, including a way to ignore occasional short-lived
state flip-flops. The daemon tracks the beginning of some state and sets
a user-defined delayed timer to react to the state later - unless the
state is cleared before the timeout. To use this facility, you must
configure:
* `upssched.conf` with settings for events and reactions
* `upssched-cmd` is a sample script with a `case` structure to handle events

For CGI clients you should set up the web-server of your choice accordingly
to run the binaries provided in /usr/lib/nut/cgi-bin, and configure:
* `upsset.conf` contains a flag that you must set to assert that you
  have indeed configured and enabled CGI clients knowingly, and have set
  up proper web-server security (required)
* `hosts.conf` contains a list of `MONITOR`ed devices that the CGI clients
  would display and/or send commands to (required)
* `upsstats.html` and `upsstats-single.html` are templates for rendering
  the CGI web-interface regarding all known, or a specific chosen, devices.

Beside directly NUT configuration examples, this distribution may include:
`/usr/share/nut/etc-samples/avahi-nut.service.sample` with settings for
mDNS announcement of NUT service on the Avahi zero-conf subnet.
This sample may be imported into your Avahi installation.

Hope this helps,
//Jim Klimov
