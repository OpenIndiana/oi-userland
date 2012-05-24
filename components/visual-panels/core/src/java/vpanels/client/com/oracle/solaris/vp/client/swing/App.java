/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.client.swing;

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.logging.*;
import com.oracle.solaris.afunix.*;
import com.oracle.solaris.vp.client.common.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.util.cli.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * The {@code App} class is a thread that listens for AF_UNIX
 * connections from other processes.  Multiple addresses of panels to
 * display, one per newline-terminated lines, may be sent through these
 * connections.
 */
public class App extends Thread implements AppConstants {
    //
    // Inner classes
    //

    public static class CommandLineOptionsBean {
	//
	// Instance data
	//

	private String host = RadLoginManager.LOCAL_HOST;
	private String user = RadLoginManager.LOCAL_USER;
	private String role;
	private String zone;
	private String zoneUser;
	private String zoneRole;
	private String address = null;
	private boolean noRemote;
	private HelpFormatter help;
	private Properties properties = new Properties();
	private boolean inParam = false;

	//
	// Constructors
	//

	public CommandLineOptionsBean(HelpFormatter help) {
	    this.help = help;
	}

	//
	// CommandLineOptionsBean methods
	//

	public String getAddress() {
	    return address;
	}

	public String getHost() {
	    return host;
	}

	public boolean getNoremote() {
	    return noRemote;
	}

	public Properties getProperties() {
	    return properties;
	}

	public String getRole() {
	    return role;
	}

	public String getUser() {
	    return user;
	}

	public String getZone() {
	    return zone;
	}

	public String getZonerole() {
	    return zoneRole;
	}

	public String getZoneuser() {
	    return zoneUser;
	}

	public void setAddress(String address) {
	    boolean absolute = address.startsWith("/");
	    if (this.address == null) {
		if (!absolute) {
		    // Assume non-relative path is a standalone shortcut
		    address = String.format("/%s/%s",
			Control.encode(AppRootControl.ID, null), address);
		}
		this.address = address;
	    } else {
		/*
		 * If the address has already been set, we accumulate
		 * additional operands as query parameters or subsequent
		 * path elements.
		 */
		if (absolute) {
		    this.address = this.address + address;
		    inParam = false;
		} else {
		    try {
			/*
			 * Ideally we'd use Control.encode, but mapping
			 * from our input to what it requires would be
			 * much less straightforward than what follows.
			 */
			String[] parts = address.split("=", 2);
			StringBuilder b = new StringBuilder(this.address);
			b.append(inParam ? "&" : "?");
			b.append(URLEncoder.encode(parts[0], Control.ENCODING));
			b.append('=');
			if (parts.length > 1)
			    b.append(URLEncoder.encode(parts[1],
				Control.ENCODING));
			this.address = b.toString();
			inParam = true;
		    } catch (UnsupportedEncodingException ex) {
		    }
		}
	    }
	}

	public void setHelp() {
	    System.out.println(help.getHelp());
	    System.exit(0);
	}

	public void setHost(String host) {
	    this.host = host;
	}

	public void setNoremote() {
	    noRemote = true;
	}

	public void setProperty(String property) {
	    String value;
	    int index = property.indexOf("=");
	    if (index == -1) {
		value = "";
	    } else {
		value = property.substring(index + 1);
		property = property.substring(0, index - 1);
	    }

	    properties.setProperty(property, value);
	}

	public void setRole(String role) {
	    this.role = role;
	}

	public void setUser(String user) {
	    this.user = user;
	}

	public void setVersion() {
	    showVersion();
	    System.exit(0);
	}

	public void setZone(String zone) {
	    this.zone = zone;
	}

	public void setZonerole(String zoneRole) {
	    this.zoneRole = zoneRole;
	}

	public void setZoneuser(String zoneUser) {
	    this.zoneUser = zoneUser;
	}
    }

    private static class InstanceInfo implements Serializable {
	//
	// Instance data
	//

	public String address;
	public Properties properties;
	public String host;
	public String user;
	public String role;
	public String zone;
	public String zoneUser;
	public String zoneRole;

	//
	// Constructors
	//

        public InstanceInfo(String address, Properties properties, String host,
            String user, String role, String zone, String zoneUser,
	    String zoneRole) {

	    this.address = address;
	    this.properties = properties;
	    this.host = host;
	    this.user = user;
	    this.role = role;
	    this.zone = zone;
	    this.zoneUser = zoneUser;
	    this.zoneRole = zoneRole;
	}

	//
	// Object methods
	//

	@Override
	public String toString() {
	    return "address = " + quote(address) +
		", host = " + quote(host) +
		", user = " + quote(user) +
		", role = " + quote(role) +
		", zone = " + quote(zone) +
		", zoneUser = " + quote(zoneUser) +
		", zoneRole = " + quote(zoneRole);
	}

	//
	// Static methods
	//

	private static String quote(String str) {
	    if (str == null) {
		return "(null)";
	    }
	    return "\"" + str + "\"";
	}
    }

    //
    // Static data
    //

    private static final String ARG_NONOPT_ADDRESS = "address";
    private static final String ARG_SHORT_HOST = "h";
    private static final String ARG_LONG_HOST = "host";
    private static final String ARG_SHORT_NOREMOTE = "n";
    private static final String ARG_LONG_NOREMOTE = "no-remote";
    private static final String ARG_SHORT_ROLE = "r";
    private static final String ARG_LONG_ROLE = "role";
    private static final String ARG_SHORT_USER = "u";
    private static final String ARG_LONG_USER = "user";
    private static final String ARG_SHORT_VERSION = "v";
    private static final String ARG_LONG_VERSION = "version";
    private static final String ARG_SHORT_ZONE = "z";
    private static final String ARG_LONG_ZONE = "zone";
    private static final String ARG_SHORT_ZONEUSER = "U";
    private static final String ARG_LONG_ZONEUSER = "zoneuser";
    private static final String ARG_SHORT_ZONEROLE = "R";
    private static final String ARG_LONG_ZONEROLE = "zonerole";
    private static final String ARG_SHORT_HELP = "?";
    private static final String ARG_LONG_HELP = "help";
    private static final String ARG_SHORT_PROPERTY = "D";
    private static final String ARG_LONG_PROPERTY = "property";

    private static final String COMMAND_NAME = "vp";
    private static final String COMMAND_DESC =
	Finder.getString("cli.description");

    private static OptionChoiceGroup options;
    static {
	OptionElement addressOption = new NoOptOptionElement(
	    true, ARG_NONOPT_ADDRESS, Finder.getString("cli.arg.address"), -1);

	OptionElement propOption = new OptionElement(ARG_SHORT_PROPERTY,
	    ARG_LONG_PROPERTY, false, "property", "");
	propOption.setDocumented(false);
	propOption.setUseLimit(-1);

	OptionElement hostOption = new OptionElement(ARG_SHORT_HOST,
	    ARG_LONG_HOST, false, "host", Finder.getString("cli.arg.host"));

	OptionElement noRemoteOption = new OptionElement(ARG_SHORT_NOREMOTE,
	    ARG_LONG_NOREMOTE, false, Finder.getString("cli.arg.noremote"));

	OptionElement userOption = new OptionElement(ARG_SHORT_USER,
	    ARG_LONG_USER, false, "user", Finder.getString("cli.arg.user"));

	OptionElement roleOption = new OptionElement(ARG_SHORT_ROLE,
	    ARG_LONG_ROLE, false, "role", Finder.getString("cli.arg.role"));

	OptionElement zoneOption = new OptionElement(ARG_SHORT_ZONE,
	    ARG_LONG_ZONE, false, "zone", Finder.getString("cli.arg.zone"));

	OptionElement zoneUserOption = new OptionElement(ARG_SHORT_ZONEUSER,
	    ARG_LONG_ZONEUSER, false, "zoneuser",
	    Finder.getString("cli.arg.zoneuser"));

	OptionElement zoneRoleOption = new OptionElement(ARG_SHORT_ZONEROLE,
	    ARG_LONG_ZONEROLE, false, "zonerole",
	    Finder.getString("cli.arg.zonerole"));

	OptionElement versionOption = new OptionElement(ARG_SHORT_VERSION,
	    ARG_LONG_VERSION, false, Finder.getString("cli.arg.version"));

	OptionElement helpOption = new OptionElement(ARG_SHORT_HELP,
	    ARG_LONG_HELP, false, Finder.getString("cli.arg.help"));

	OptionListGroup mainGroup = new OptionListGroup(false,
	    propOption, hostOption, userOption, roleOption, zoneOption,
	    zoneUserOption, zoneRoleOption, noRemoteOption, addressOption);

	options = new OptionChoiceGroup(true, mainGroup, versionOption,
	    helpOption);
    }

    public static final String VP_USER_DIR =
	System.getProperty("user.home") + File.separator + ".vp";

    static {
	// Set up client logging
	String fileName = VP_USER_DIR + File.separator + "log";

	// Root Logger
	Logger log = Logger.getLogger("");

	try {
	    File parent = new File(fileName).getParentFile();
	    if (!parent.exists()) {
		if (!parent.mkdirs()) {
		    throw new IOException(
			"could not create directory: " +
			parent.getAbsolutePath());
		}
	    }

	    Handler fHandler = new FileHandler(fileName);
	    fHandler.setFormatter(new SimpleFormatter());
	    log.addHandler(fHandler);

	    // Don't output to the console by default
	    for (Handler cHandler : log.getHandlers()) {
		if (cHandler instanceof ConsoleHandler) {
		    log.removeHandler(cHandler);
		}
	    }
	} catch (IOException e) {
	    Logger.getLogger(App.class.getName()).log(Level.WARNING,
		"unable to create log file: " + fileName);
	}
    }

    public static final File TRUSTSTORE_FILE =
	new File(VP_USER_DIR, "truststore");

    public static final File VP_UNIX;
    static {
	String hostName = NetUtil.getHostName();
	if (hostName == null) {
	    hostName = "localhost";
	}

	// May be null or malformed if not an X client
	String display = System.getenv("DISPLAY");

	if (display != null && !display.matches(".*:\\d+(\\.\\d)?$")) {
	    String error = "invalid DISPLAY environment variable: " + display;
	    Logger.getLogger(App.class.getName()).log(Level.WARNING, error);
	    display = null;
	}

	if (display == null) {
	    display = ":0.0";
	} else {
	    if (display.matches(".*:\\d+$")) {
		display += ".0";
	    }

	    if (display.startsWith(hostName)) {
		display = display.substring(hostName.length());
	    }
	}

	String name = String.format(".unix-%s-%s", hostName, display);

	VP_UNIX = new File(VP_USER_DIR, name);
    }

    public static final String VP_USER_PREFS =
	VP_USER_DIR + File.separator + "vp.init";

    private static final Preferences prefs = new Preferences(VP_USER_PREFS);

    //
    // Instance data
    //

    private UnixSocketServer server;
    private boolean closing;
    private final List<AppInstance> instances = new ArrayList<AppInstance>();
    private ConnectionManager connManager = new ConnectionManager();
    private LoginHistoryManager loginHistoryManager =
	new LoginHistoryManager(connManager, new File(VP_USER_DIR, "history"));

    //
    // Constructors
    //

    public App() {
	addVersionToThreadName(this);
    }

    //
    // Runnable methods
    //

    @Override
    public void run() {
        Logger log = Logger.getLogger(getClass().getName());

	// Start singleton application instance...
	try {
	    server = UnixDomainSocket.bind(VP_UNIX, 0600);

	    while (true) {
		final UnixSocket socket = server.accept();
		String peerUser = socket.getPeerUser();

		if (!RadLoginManager.LOCAL_USER.equals(peerUser)) {
		    String error = String.format(
			"user %s attempted to connect as %s", peerUser,
			RadLoginManager.LOCAL_USER);
		    log.log(Level.WARNING, error);
		} else {
		    // Spawn on a separate thread so as not to block other
		    // incoming to conections -- not so much because we
		    // anticipate a lot of traffic, but because we can't
		    // guarantee that some poorly-behaved client won't keep its
		    // connection open indefinitely.
		    new Thread() {
			@Override
			public void run() {
			    readFully(socket);
			}
		    }.start();
		}
	    }
	} catch (AFUNIXNotSupportedException e) {
	    // Bummer
	    return;
	} catch (IOException e) {
	    if (!closing) {
		// Major bummer
		log.log(Level.SEVERE,
		    "error communicating via incoming AF_UNIX connection", e);
	    }
	    return;
	}
    }

    //
    // App methods
    //

    public void abortableExit() throws ActionAbortedException {
	synchronized (instances) {
	    for (int i = instances.size() - 1; i >= 0; i--) {
		// Throws ActionAbortedException
		instances.get(i).closeInstance(false);
	    }
	}
	exit();
    }

    public void exit(int exitCode) {
	try {
	    if (server != null) {
		closing = true;
		server.close();
	    }
	} catch (IOException ignore) {
	}

	try {
	    prefs.store();
	} catch (IOException e) {
	    Logger.getLogger(getClass().getName()).log(Level.WARNING,
		"could not write preferences", e);
	}

	System.exit(exitCode);
    }

    public void exit() {
	exit(0);
    }

    private void exitIfNoIntances(int exitCode) {
	if (instances.isEmpty()) {
	    exit(exitCode);
	}
    }

    public ConnectionManager getConnectionManager() {
	return connManager;
    }

    public LoginHistoryManager getLoginHistoryManager() {
	return loginHistoryManager;
    }

    protected Preferences getPreferences() {
	return prefs;
    }

    protected void instanceClosed(AppInstance instance) {
	synchronized (instances) {
	    if (instances.remove(instance)) {
		exitIfNoIntances(0);
	    }
	}
    }

    protected void instanceCreated(AppInstance instance) {
	synchronized (instances) {
	    instances.add(instance);
	}
    }

    public void newInstance(InstanceInfo info) {
	AppInstance instance = null;
	boolean success = false;

	try {
	    LoginProperty<String> host =
		new LoginProperty<String>(info.host, false);
	    host.setEditableOnError(true);

	    LoginProperty<String> user =
		new LoginProperty<String>(info.user, false);
	    user.setEditableOnError(true);

	    LoginProperty<String> role =
		new LoginProperty<String>(info.role, false);
	    role.setEditableOnError(true);

	    LoginProperty<String> zone =
		new LoginProperty<String>(info.zone, false);
	    zone.setEditableOnError(true);

	    LoginProperty<String> zoneUser =
		new LoginProperty<String>(info.zoneUser, false);
	    zoneUser.setEditableOnError(true);

	    LoginProperty<String> zoneRole =
		new LoginProperty<String>(info.zoneRole, false);
	    zoneRole.setEditableOnError(true);

            boolean zonePromptVal = zone.getValue() != null ||
		zoneUser.getValue() != null || zoneRole.getValue() != null;
	    LoginProperty<Boolean> zonePrompt =
		new LoginProperty<Boolean>(zonePromptVal, false);

            LoginRequest request = new LoginRequest(host, user, role,
		zonePrompt, zone, zoneUser, zoneRole);

	    instance = new AppInstance(this, info.properties, request);

	    SimpleNavigable[] path = Navigator.toArray(info.address);
	    instance.getNavigator().goToAsyncAndWait(true, null, path);
	    success = true;

	// User is aware of this because he explicitly caused it
	} catch (ActionAbortedException e) {

	// User has been advised of this by RadLoginManager
	} catch (ActionFailedException e) {

	// User has been advised of this by SwingNavigator
	} catch (NavigationException e) {

	// Unexpected error - write to log
	} catch (RuntimeException e) {
	    Logger log = Logger.getLogger(getClass().getName());
	    log.log(Level.SEVERE, "could not launch: " + info, e);

	// Unexpected error - write to log
	} catch (Error e) {
	    Logger log = Logger.getLogger(getClass().getName());
	    log.log(Level.SEVERE, "could not launch: " + info, e);

	} finally {
	    if (!success && instance != null &&
		// Partial navigation failures aren't deal-breakers
		!NavigationUtil.isPanelStarted(instance.getNavigator())) {

		instance.close();
	    }
	}
    }

    public void readFully(UnixSocket socket) {
	ObjectInputStream in = null;
        Logger log = Logger.getLogger(getClass().getName());

	try {
	    in = new ObjectInputStream(socket.getInputStream());
	    InstanceInfo info = (InstanceInfo)in.readObject();
	    newInstance(info);
	} catch (ClassNotFoundException e) {
            log.log(Level.SEVERE,
		"unexpected or invalid object read from AF_UNIX connection", e);

	} catch (IOException e) {
	    log.log(Level.SEVERE, "I/O error", e);

	} finally {
	    IOUtil.closeIgnore(in);
	}
    }

    //
    // Static methods
    //

    private static void addVersionToThreadName(Thread thread) {
	// Add useful information to a thread dump
	String name = String.format(
	    "%s (app version %s)", thread.getName(), VERSION);

	thread.setName(name);
    }

    public static void showVersion() {
	System.out.println(Finder.getString("cli.error.version", VERSION));
    }

    public static void main(String args[]) {
	addVersionToThreadName(Thread.currentThread());

	CommandLineParser parser = new PosixCommandLineParser();
	UsageFormatter usage = new UsageFormatter(
	    COMMAND_NAME, options, parser.getOptionFormatter());
	HelpFormatter help = new HelpFormatter(COMMAND_DESC, usage);
	CommandLineOptionsBean bean = new CommandLineOptionsBean(help);

	if (System.getProperty("vpanels.debug.version") != null) {
	    showVersion();
	}

	try {
	    // Populate bean
	    CommandLineProcessor.process(args, options, parser, bean);
	}

	catch (Exception e) {
	    CommandUtil.exit(e, usage);
	}

        InstanceInfo info = new InstanceInfo(bean.getAddress(),
            bean.getProperties(), bean.getHost(), bean.getUser(),
            bean.getRole(), bean.getZone(), bean.getZoneuser(),
            bean.getZonerole());

	if (!bean.getNoremote()) {
	    // Check for running instance
	    try {
		UnixSocket socket = UnixDomainSocket.connect(VP_UNIX);

		// Send arguments to running instance...
		ObjectOutputStream out = new ObjectOutputStream(
		    socket.getOutputStream());

		out.writeObject(info);
		out.close();
		System.exit(0);
	    } catch (AFUNIXNotSupportedException e) {
		// AF_UNIX sockets are not supported on this platform
	    } catch (IOException e) {
		// We are the only running instance
	    }
	}

	try {
	    URL policy = Finder.getResource("panel.policy");
	    if (policy == null) {
		throw new IOException("panel.policy not found");
	    }
	    PanelClassLoader.loadPermissions(policy);
	} catch (IOException e) {
	    Logger.getLogger(App.class.getName()).log(Level.SEVERE,
		"unable to read panel.policy", e);
	    String message = Finder.getString("init.error.security.io");
	    System.err.println(message);
	    System.exit(1);
	} catch (PermissionParseException e) {
	    Logger.getLogger(App.class.getName()).log(Level.SEVERE,
		"unable to parse panel.policy", e);
	    String message = Finder.getString("init.error.security.parse");
	    System.err.println(message);
	    System.exit(1);
	}

	System.setSecurityManager(new SecurityManager());

	App app = new App();
	app.newInstance(info);
	app.exitIfNoIntances(1);

	if (!bean.getNoremote()) {
	    // Start daemon thread listening for connections
	    app.start();
	}
    }
}
