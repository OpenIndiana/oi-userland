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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.client.common;

import java.io.*;
import java.net.*;
import java.security.*;
import java.security.cert.*;
import java.security.cert.Certificate;
import java.util.*;
import java.util.logging.*;
import javax.management.*;
import javax.management.remote.*;
import javax.swing.JOptionPane;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.rad.*;
import com.oracle.solaris.rad.jmx.*;
import com.oracle.solaris.rad.pam.*;
import com.oracle.solaris.rad.zonesbridge.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.api.panel.MBeanUtil;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public abstract class RadLoginManager {
    public static final String RAD_PATH_AFUNIX_AUTH =
	"/system/volatile/rad/radsocket";
    public static final String RAD_PATH_AFUNIX_UNAUTH =
	"/system/volatile/rad/radsocket-unauth";

    //
    // Inner classes
    //

    private static abstract class AuthPrompter {
	//
	// Instance data
	//

	private boolean acknowledged;

	//
	// AuthPrompter methods
	//

	/**
	 * _,__/|
	 *  `O.o'
	 * =(_x_)=
	 *    U
	 */
	protected void ack() {
	    acknowledged = true;
	}

	public boolean isAcknowledged() {
	    return acknowledged;
	}

	public abstract Block initiate(LoginRequest request,
	    AuthenticationMXBean auth) throws ActionAbortedException,
	    ObjectException;

	public abstract void prompt(LoginRequest request,
	    List<LoginProperty> properties, boolean isFirst)
	    throws ActionAbortedException, ActionRegressedException;
    }

    private class UserPrompter extends AuthPrompter {
	@Override
	public Block initiate(LoginRequest request,
	    AuthenticationMXBean auth) throws ActionAbortedException,
	    ObjectException {

	    setLoginStatus(request, Finder.getString("login.status.login",
		request.getUser().getValue()));

	    return auth.login(Locale.getDefault().getLanguage(),
		request.getUser().getValue());
	}

	@Override
	public void prompt(LoginRequest request, List<LoginProperty> properties,
	    boolean isFirst) throws ActionAbortedException,
	    ActionRegressedException {

	    try {
		promptForAuth(request, properties, false, true, isFirst);
	    } finally {
		ack();
		request.getHost().setErrored(false);
		request.getUser().setErrored(false);
	    }
	}
    }

    private class RolePrompter extends AuthPrompter {
	@Override
	public Block initiate(LoginRequest request,
	    AuthenticationMXBean auth) throws ActionAbortedException,
	    ObjectException {

	    setLoginStatus(request, Finder.getString("login.status.assume",
		request.getRole().getValue()));

	    return auth.assume(Locale.getDefault().getLanguage(),
		request.getRole().getValue());
	}

	@Override
	public void prompt(LoginRequest request, List<LoginProperty> properties,
	    boolean isFirst) throws ActionAbortedException,
	    ActionRegressedException {

	    try {
		promptForAuth(request, properties, false, false, isFirst);
	    } finally {
		ack();
		request.getRole().setErrored(false);
	    }
	}
    }

    private class ZoneUserPrompter extends AuthPrompter {
	@Override
	public Block initiate(LoginRequest request,
	    AuthenticationMXBean auth) throws ActionAbortedException,
	    ObjectException {

	    return auth.login(Locale.getDefault().getLanguage(),
		request.getZoneUser().getValue());
	}

	@Override
	public void prompt(LoginRequest request, List<LoginProperty> properties,
	    boolean isFirst) throws ActionAbortedException,
	    ActionRegressedException {

	    try {
		promptForAuth(request, properties, true, true, isFirst);
	    } finally {
		ack();
		request.getZone().setErrored(false);
		request.getZoneUser().setErrored(false);
	    }
	}
    }

    private class ZoneRolePrompter extends AuthPrompter {
	@Override
	public Block initiate(LoginRequest request,
	    AuthenticationMXBean auth) throws ActionAbortedException,
	    ObjectException {

	    return auth.assume(Locale.getDefault().getLanguage(),
		request.getZoneRole().getValue());
	}

	@Override
	public void prompt(LoginRequest request, List<LoginProperty> properties,
	    boolean isFirst) throws ActionAbortedException,
	    ActionRegressedException {

	    try {
		promptForAuth(request, properties, true, false, isFirst);
	    } finally {
		ack();
		request.getZoneRole().setErrored(false);
	    }
	}
    }

    private static class LoginData {
	//
	// Instance data
	//

	private LinkedList<ConnectionInfo> depChain =
	    new LinkedList<ConnectionInfo>();

	private LinkedList<Boolean> acks = new LinkedList<Boolean>();

	//
	// LoginData methods
	//

	public boolean isAcknowledged() {
	    return acks.peek();
	}

	public List<ConnectionInfo> getDepChain() {
	    return depChain;
	}

	public ConnectionInfo peek(int offset) {
	    return depChain.get(offset);
	}

	public void pop() {
	    depChain.pop();
	    acks.pop();
	}

	public void push(ConnectionInfo info, boolean acknowledged) {
	    depChain.push(info);
	    acks.push(acknowledged);
	}

	public void setDepChain(List<ConnectionInfo> depChain,
	    boolean acknowledged) {

	    assert compatible(depChain);

	    this.depChain.clear();
	    acks.clear();

	    for (int i = depChain.size() - 1; i >= 0; i--) {
		push(depChain.get(i), acknowledged);
	    }
	}

	//
	// Object methods
	//

	@Override
	public String toString() {
	    StringBuilder buffer = new StringBuilder();
	    for (int i = depChain.size() - 1; i >= 0; i--) {
		buffer.append(String.format("%d. %s (%s)\n", i,
		    depChain.get(i), acks.get(i) ? "acknowledged" :
		    "not acknowledged"));
	    }
	    return buffer.toString();
	}

	//
	// Private methods
	//

	private void clearConnectionsTo(int level) {
	    int size = depChain.size();
	    for (int i = size - 1; i >= level; i--) {
		depChain.remove(i);
	    }
	}

	private boolean compatible(List<ConnectionInfo> depChain) {
	    boolean compatible = false;
	    if (depChain.size() == this.depChain.size() + 1) {
		compatible = true;
		for (int i = 0, n = this.depChain.size(); i < n; i++) {
		    if (!this.depChain.get(i).equals(depChain.get(i + 1))) {
			compatible = false;
			break;
		    }
		}
	    }
	    return compatible;
	}
    }

    //
    // Static data
    //

    public static final String TRUSTSTORE_PASSWORD = "trustpass";
    public static final String LOCAL_USER = System.getProperty("user.name");
    public static final String LOCAL_HOST = "localhost";

    //
    // Instance data
    //

    private ConnectionManager connManager;

    //
    // Constructors
    //

    public RadLoginManager(ConnectionManager connManager) {
	this.connManager = connManager;
    }

    //
    // RadLoginManager methods
    //

    /**
     * Creates an empty truststore file.
     */
    protected void createTrustStore(File truststore) throws KeyStoreException,
	IOException, NoSuchAlgorithmException, CertificateException {

	File truststoreDir = truststore.getParentFile();

	if (!truststoreDir.exists()) {
	    if (!truststoreDir.mkdirs()) {
		throw new IOException(
		    "could not create truststore directory: " +
		    truststoreDir.getAbsolutePath());
	    }
	}

	KeyStore keyStore = KeyStore.getInstance(KeyStore.getDefaultType());
	char[] password = getTrustStorePassword().toCharArray();

	// Create empty keystore
	keyStore.load(null, password);

	FileOutputStream fos = new FileOutputStream(truststore);
	keyStore.store(fos, password);
	fos.close();
    }

    /**
     * Guides the user through the login process, then returns a dependency
     * chain of {@link ConnectionInfo}s.  The first element of the chain is the
     * {@code ConnectionInfo} that satisfies the given request.  Each additional
     * {@code ConnectionInfo} is a dependency of the previous {@code
     * ConnectionInfo}.
     * <p/>
     * For example, a role-based connection ("root@nerd (via talley)", say)
     * would have an dependency on the user-based connection ("talley@nerd")
     * used to create it.  The returned chain would contain the role-based
     * connection just before the user-based connection.
     * <p/>
     * This chain of {@code ConnectionInfo} dependencies can be {@link
     * ConnectionManager#add added} to the {@code ConnectionManager} for
     * automatic dependency-based management.
     *
     * @param	    request
     *		    the {@link LoginRequest} encapsulating the preset values and
     *		    editability of each core {@link LoginProperty}
     *
     * @param	    current
     *		    if non-{@code null}, ensures that the user is aware of any
     *		    change in login, preventing the use of cached connections
     *		    without the user's knowledge
     *
     * @exception   ActionAbortedException
     *		    if the user cancels the operation
     *
     * @exception   ActionFailedException
     *		    if the given request fails
     */
    @SuppressWarnings({"fallthrough"})
    public List<ConnectionInfo> getConnectionInfo(LoginRequest request,
	LoginInfo current) throws ActionAbortedException, ActionFailedException
    {
	LoginData data = new LoginData();
	Boolean doZone;
	for (int step = 0; ; ) {
	    try {
		switch (step) {
		case 0:
		    gatherHostAndUserData(request, data);
		    step++;

		case 1:
		    gatherRoleData(request, data);
		    step++;

		case 2:
		    doZone = request.getZonePrompt().getValue();
		    if (doZone != null && doZone) {
			gatherZoneHostAndUserData(request, data);
		    }
		    step++;

		case 3:
		    doZone = request.getZonePrompt().getValue();
		    if (doZone != null && doZone) {
			gatherZoneRoleData(request, data);
		    }
		    step++;
		}
		break;
	    } catch (ActionRegressedException e) {
		step--;
	    }
	}

	List<ConnectionInfo> depChain = data.getDepChain();

	// To prevent rogue connections, if the chosen connection differs from
	// the current one, ensure that the user has acknowledged it at some
	// point in the authentication process.  If not, prompt for
	// acknowledgement now.
	if (!data.isAcknowledged() && !depChain.get(0).matches(current)) {
	    promptForAck(request);
	}

	return depChain;
    }

    public ConnectionManager getConnectionManager() {
	return connManager;
    }

    /**
     * Gets the truststore file.
     */
    public abstract File getTrustStoreFile();

    /**
     * Gets the truststore password.  This default implementation returns
     * "{@code trustpass}".
     */
    public String getTrustStorePassword() {
	return TRUSTSTORE_PASSWORD;
    }

    protected boolean handleCertFailure(String host, File truststore,
	Certificate certificate) throws ActionAbortedException,
	KeyStoreException, IOException, NoSuchAlgorithmException,
	CertificateException {

	KeyStore keyStore = KeyStore.getInstance(KeyStore.getDefaultType());
	char[] password = getTrustStorePassword().toCharArray();

	// Load truststore
	FileInputStream fis = new FileInputStream(truststore);
	keyStore.load(fis, password);
	fis.close();

	// Does the truststore already contain the certificate?
	String alias = keyStore.getCertificateAlias(certificate);
	if (alias != null) {
	    return false;
	}

	boolean acceptNeeded = true;

	if (NetUtil.isLocalAddress(host)) {
	    FileInputStream certFileIn = null;
	    try {
		File certFile = new File("/etc/rad/cert.pem");
		certFileIn = new FileInputStream(certFile);
		Certificate localCert = CertificateFactory.
		    getInstance("X.509").generateCertificate(certFileIn);

		if (localCert.equals(certificate)) {
		    acceptNeeded = false;
		}
	    } catch (Throwable ignore) {
	    } finally {
		IOUtil.closeIgnore(certFileIn);
	    }
	}

	if (acceptNeeded) {
	    // Display the certificate, prompt user to accept
	    promptForCertificate(host, certificate);
	}

	// Add certificate
	alias = ((X509Certificate)certificate).getIssuerDN().toString();
	KeyStore.Entry entry =
	    new KeyStore.TrustedCertificateEntry(certificate);
	keyStore.setEntry(alias, entry, null);

	FileOutputStream fos = new FileOutputStream(truststore);
	keyStore.store(fos, password);
	fos.close();

	return true;
    }

    /**
     * Prompt the user to acknowledge or reject the imminent completion of the
     * given request.
     *
     * @param	    request
     *		    the {@link LoginRequest} encapsulating the preset values of
     *		    each core {@link LoginProperty}
     *
     * @exception   ActionAbortedException
     *		    if the user cancels the operation
     */
    protected abstract void promptForAck(LoginRequest request)
	throws ActionAbortedException;

    /**
     * Prompts the user to enter data for each of the given {@link
     * LoginProperty}s required for user or role authentication by the server.
     *
     * @param	    request
     *		    the {@link LoginRequest} encapsulating the preset values and
     *		    editability of each core {@link LoginProperty}
     *
     * @param	    properties
     *		    a {@code List} of {@link LoginProperty}s from the server
     *		    ({@code LoginProperty<String>} or {@code
     *		    PasswordLoginProperty} only)
     *
     * @exception   ActionAbortedException
     *		    if the user cancels the operation
     *
     * @exception   ActionRegressedException
     *		    if the chooses to re-edit the host or user fields
     *
     * @param	    isZone
     *		    {@code true} if prompting for a zone user or role
     *		    authentication
     *
     * @param	    isUserAuth
     *		    {@code true} if for user authentication, {@code false} if
     *		    for role authentication
     *
     * @param	    isFirst
     *		    {@code true} if this is the first prompt in the
     *		    authentication conversation
     */
    protected abstract void promptForAuth(LoginRequest request,
	List<LoginProperty> properties, boolean isZone, boolean isUserAuth,
	boolean isFirst) throws ActionAbortedException,
	ActionRegressedException;

    /**
     * Display the given {@code Certificate} details and prompt for user
     * confirmation to add it to the truststore.
     *
     * @param	    host
     *		    the owner of the {@code Certificate}
     *
     * @param	    certificate
     *		    the {@code Certificate} to verify
     *
     * @exception   ActionAbortedException
     *		    if the user cancels the operation
     */
    protected abstract void promptForCertificate(String host,
	Certificate certificate) throws ActionAbortedException;

    /**
     * Prompts the user to acknowledge failure of the given request.
     *
     * @param	    request
     *		    the {@link LoginRequest} encapsulating the values and
     *		    error status of each core {@link LoginProperty}
     */
    protected abstract void promptForFailedRequest(LoginRequest request);

    /**
     * Prompt the user to enter host/user data, subject to the editability and
     * preset values of the host and user {@link LoginProperty}s of the given
     * request.
     *
     * @param	    request
     *		    the {@link LoginRequest} encapsulating the preset values and
     *		    editability of each core {@link LoginProperty}
     *
     * @exception   ActionAbortedException
     *		    if the user cancels the operation
     */
    protected abstract void promptForHostAndUser(LoginRequest request)
	throws ActionAbortedException;

    /**
     * Prompt the user to select a role, subject to the editability and preset
     * value of the role {@link LoginProperty} of the given request.
     *
     * @param	    request
     *		    the {@link LoginRequest} encapsulating the preset values and
     *		    editability of each core {@link LoginProperty}
     *
     * @param	    roles
     *		    a list of valid roles for the selected user
     *
     * @param	    isZone
     *		    {@code true} if prompting for a zone role
     *
     * @exception   ActionAbortedException
     *		    if the user cancels the operation
     *
     * @exception   ActionRegressedException
     *		    if the chooses to re-edit the host or user fields
     */
    protected abstract void promptForRole(LoginRequest request,
	List<String> roles, boolean isZone) throws ActionAbortedException,
	ActionRegressedException;

    /**
     * Prompt the user to enter zone/user data, subject to the editability and
     * preset values of the zone and user {@link LoginProperty}s of the given
     * request.
     *
     * @param	    request
     *		    the {@link LoginRequest} encapsulating the preset values and
     *		    editability of each core {@link LoginProperty}
     *
     * @param	    zones
     *		    a list of valid zones for the selected host
     *
     * @exception   ActionAbortedException
     *		    if the user cancels the operation
     *
     * @exception   ActionRegressedException
     *		    if the chooses to re-edit the host or user fields
     */
    protected abstract void promptForZoneAndUser(LoginRequest request,
	List<String> zones) throws ActionAbortedException,
	ActionRegressedException;

    /**
     * Set login status.
     *
     * @param	    request
     *		    the {@link LoginRequest} encapsulating the preset values of
     *		    each core {@link LoginProperty}
     *
     * @param	    status
     *		    the login status
     */
    protected abstract void setLoginStatus(LoginRequest request, String status);

    //
    // Private methods
    //

    @SuppressWarnings({"fallthrough"})
    private boolean authConverse(LoginRequest request,
	AuthenticationMXBean auth, AuthPrompter prompter)
	throws ActionAbortedException, ActionRegressedException {

	List<DialogMessage> messages = request.getMessages();
	boolean isFirst = true;

	try {
	    Block answer = prompter.initiate(request, auth);

	    List<LoginProperty> properties =
		new LinkedList<LoginProperty>();

	    BlockType type;
	    while (true) {
		properties.clear();

		switch (type = answer.getType()) {
		case SUCCESS:
		    // Display any lingering messages from the server
		    if (!messages.isEmpty()) {
			prompter.prompt(request, properties, isFirst);
			isFirst = false;
			messages.clear();
		    }

		    auth.complete();
		    return true;

		case ERROR:
		    return false;

		default:
		    assert type == BlockType.CONV;
		case CONV:
		    for (Message m : answer.getMessages()) {
			String text = m.getMessage();
			switch (m.getStyle()) {
			case PROMPT_ECHO_OFF:
			    properties.add(new PasswordLoginProperty(
				text, new char[0], true));
			    break;

			case PROMPT_ECHO_ON:
			    properties.add(new LoginProperty<String>(
				text, "", true));
			    break;

			case ERROR_MSG:
			    messages.add(new DialogMessage(text,
				JOptionPane.ERROR_MESSAGE));
			    break;

			case TEXT_INFO:
			    messages.add(new DialogMessage(text,
				JOptionPane.INFORMATION_MESSAGE));
			    break;
			}
		    }

		    if (!properties.isEmpty()) {
			prompter.prompt(request, properties, isFirst);
			isFirst = false;
			messages.clear();
		    }

		    List<char[]> response = new LinkedList<char[]>();
		    for (LoginProperty property : properties) {
			Object value = property.getValue();
			if (value != null) {
			    response.add(value instanceof char[] ?
				(char[])value : ((String)value).toCharArray());
			}
		    }

		    answer = auth.submit(response);
		    // clear out passwords
		    for (char[] res : response) {
			Arrays.fill(res, (char)0);
			res = null;
		    }
		}
	    }
	} catch (ObjectException e) {
	    messages.add(new DialogMessage(
		Finder.getString("login.err.io",
		request.getHost().getValue()),
		JOptionPane.ERROR_MESSAGE));
	    return false;
	}
    }

    private <T> T createMXBeanProxy(LoginRequest request, ConnectionInfo info,
	Class<T> ifaceClass, Stability s, String domain, String name)
	throws ActionFailedException {

	MBeanServerConnection mbsc = getMBeanServerConnection(request, info);
	if (mbsc == null) {
	    return null;
	}

	ObjectName oName = MBeanUtil.makeObjectName(domain, name);

	try {
	    return ifaceClass.cast(RadJMX.newMXBeanProxy(mbsc, oName,
		ifaceClass, s));
	} catch (IncompatibleVersionException e) {
	    List<DialogMessage> messages = request.getMessages();
	    messages.add(new DialogMessage(Finder.getString(
		"proxy.error.version", e.getClientVersion(),
		e.getServerVersion(), ifaceClass.getSimpleName()),
		JOptionPane.ERROR_MESSAGE));
	    requestFailed(request);
	} catch (JMException e) {
	    List<DialogMessage> messages = request.getMessages();
	    messages.add(new DialogMessage(Finder.getString(
		"proxy.error.general", oName),
		JOptionPane.ERROR_MESSAGE));
	    requestFailed(request);
	} catch (IOException e) {
	    List<DialogMessage> messages = request.getMessages();
	    messages.add(new DialogMessage(Finder.getString(
		"proxy.error.io", ifaceClass.getSimpleName()),
		JOptionPane.ERROR_MESSAGE));
	    requestFailed(request);
	}
	return null;
    }

    private AuthenticationMXBean createAuthBean(LoginRequest request,
	ConnectionInfo info) throws ActionFailedException {
	return createMXBeanProxy(request, info, AuthenticationMXBean.class,
	    Stability.PRIVATE, "com.oracle.solaris.rad.pam", "Authentication");
    }

    private JMXConnector createConnector(String host)
	throws KeyStoreException, NoSuchAlgorithmException,
	CertificateException, MalformedURLException, IOException,
	ActionAbortedException {

	if (NetUtil.isLocalAddress(host)) {
	    String[] paths = {
		RAD_PATH_AFUNIX_AUTH,
		RAD_PATH_AFUNIX_UNAUTH
	    };

	    for (String path : paths) {
		JMXServiceURL url = null;
		try {
		    url = new JMXServiceURL(RadConnector.PROTOCOL_UNIX, "", 0,
			path);
		    return JMXConnectorFactory.connect(url);
		} catch (IOException e) {
		    // Not necessarily an error
		    Logger.getLogger(getClass().getName()).log(Level.CONFIG,
			"unable to utilize local AF_UNIX connector: " +
			(url == null ? path : url), e);
		}
	    }
	}

	File truststore = getTrustStoreFile();
	if (!truststore.exists()) {
	    createTrustStore(truststore);
	}

	Map<String, Object> env = new HashMap<String, Object>();
	env.put(RadConnector.KEY_TLS_TRUSTSTORE,
	    truststore.getAbsolutePath());
	env.put(RadConnector.KEY_TLS_TRUSTPASS,
	    getTrustStorePassword());

	JMXServiceURL url = new JMXServiceURL(
	    RadConnector.PROTOCOL_TLS, host, 0);

	// Throws MalformedURLException
	JMXConnector connector = JMXConnectorFactory.newJMXConnector(url, null);

	for (;;) {
	    RadTrustManager mtm = new RadTrustManager();
	    env.put(RadConnector.KEY_TLS_RADMANAGER, mtm);

	    try {
		connector.connect(env);
		break;
	    } catch (IOException e) {
		X509Certificate[] chain = mtm.getBadChain();
		if (chain == null) {
		    throw e;
		}

		if (!handleCertFailure(host, truststore, chain[0])) {
		    throw e;
		}
	    }
	}

	return connector;
    }

    private JMXConnector createConnector(LoginRequest request)
	throws ActionAbortedException {

	JMXConnector connector = null;
	LoginProperty<String> host = request.getHost();
	String hostVal = host.getValue();
	List<DialogMessage> messages = request.getMessages();
	boolean success = false;

	try {
	    setLoginStatus(request, Finder.getString("login.status.host",
		hostVal));

	    connector = createConnector(hostVal);
	    success = true;

	// Thrown by JMXConnector.connect
	} catch (UnknownHostException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.host.unknown", hostVal), JOptionPane.ERROR_MESSAGE));

	// Thrown by JMXConnector.connect
	} catch (ConnectException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.host.refused", hostVal), JOptionPane.ERROR_MESSAGE));

	// Thrown by JMXConnector.connect
	} catch (SecurityException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.security", hostVal),
		JOptionPane.ERROR_MESSAGE));

	// Thrown by createTrustStore
	} catch (KeyStoreException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.keystore", e.getMessage()),
		JOptionPane.ERROR_MESSAGE));

	// Thrown by createTrustStore
	} catch (NoSuchAlgorithmException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.keystore", e.getMessage()),
		JOptionPane.ERROR_MESSAGE));

	// Thrown by getDaemonCertificateChain
	} catch (CertificateException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.nocerts", hostVal),
		JOptionPane.ERROR_MESSAGE));

	// Thrown by new JMXServiceURL
	} catch (MalformedURLException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.url.invalid"),
		JOptionPane.ERROR_MESSAGE));

	// Thrown by JMXConnector.connect et al
	} catch (IOException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.io", hostVal),
		JOptionPane.ERROR_MESSAGE));

	} finally {
	    if (!success) {
		host.setErrored(true);
	    }
	}

	return connector;
    }

    private IOMXBean createZonesBridgeBean(LoginRequest request,
	ConnectionInfo info) throws ActionFailedException {
	return createMXBeanProxy(request, info, IOMXBean.class,
	    Stability.PRIVATE, "com.oracle.solaris.rad.zonesbridge", "IO");
    }

    private UtilMXBean createZonesUtilBean(LoginRequest request,
	ConnectionInfo info) throws ActionFailedException {
	return createMXBeanProxy(request, info, UtilMXBean.class,
	    Stability.PRIVATE, "com.oracle.solaris.rad.zonesbridge", "Util");
    }

    private JMXConnector createZoneConnector(LoginRequest request,
	IOMXBean bean) {

	JMXConnector connector = null;
	LoginProperty<String> zone = request.getZone();
	String zoneVal = zone.getValue();
	String zoneUserVal = request.getZoneUser().getValue();
	List<DialogMessage> messages = request.getMessages();
	boolean success = false;

	try {
	    JMXServiceURL url = new JMXServiceURL(
		RadConnector.PROTOCOL_ZONESBRIDGE, zoneVal, 0,
		"/" + zoneUserVal);

	    Map<String, Object> env = new HashMap<String, Object>();
	    env.put(RadConnector.KEY_ZONESBRIDGE_MXBEAN, bean);

	    connector = JMXConnectorFactory.connect(url, env);
	    success = true;

	// Thrown by JMXConnector.connect
	} catch (SecurityException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.zone.security", zoneVal, zoneUserVal),
		JOptionPane.ERROR_MESSAGE));

	// Thrown by new JMXServiceURL
	} catch (MalformedURLException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.url.invalid"), JOptionPane.ERROR_MESSAGE));

	// Thrown by JMXConnector.connect et al
	} catch (IOException e) {
	    messages.add(new DialogMessage(Finder.getString(
		"login.err.io", zoneVal), JOptionPane.ERROR_MESSAGE));

	} finally {
	    if (!success) {
		zone.setErrored(true);
	    }
	}

	return connector;
    }

    private void gatherHostAndUserData(LoginRequest request, LoginData data)
	throws ActionAbortedException, ActionFailedException {

	LoginProperty<String> host = request.getHost();
	LoginProperty<String> user = request.getUser();
	LoginProperty<Boolean> zonePrompt = request.getZonePrompt();
	List<DialogMessage> messages = request.getMessages();

	// Validate any preset values prior to prompting user
	if (host.getValue() != null || !host.isEditable()) {
	    isHostValid(request);
	}
	if (user.getValue() != null || !user.isEditable()) {
	    isUserValid(request);
	}
	if (zonePrompt.getValue() != null || !zonePrompt.isEditable()) {
	    isPropertyValid(zonePrompt, request);
	}

	// Loop until connected to host and authenticated as user
	while (true) {
	    boolean acknowledged = false;

	    // Refresh each iteration in case a prop isEditableOnError()
	    boolean hostEditable = host.isEditable();
	    boolean userEditable = user.isEditable();
	    boolean zonePromptEditable = zonePrompt.isEditable();

	    // If an error cannot be fixed by the user...
	    if ((!zonePromptEditable && zonePrompt.isErrored()) ||
		(!hostEditable && (host.isErrored() ||
		(!userEditable && user.isErrored())))) {

		requestFailed(request);
	    }

	    if (hostEditable || userEditable || zonePromptEditable ||
		!messages.isEmpty()) {

		try {
		    promptForHostAndUser(request);
		} finally {
		    acknowledged = true;

		    // User only needs to see any message once, presumably
		    messages.clear();

		    host.setErrored(false);
		    user.setErrored(false);
		    zonePrompt.setErrored(false);
		}

		if (!isHostValid(request) || !isUserValid(request) ||
		    !isPropertyValid(zonePrompt, request)) {
		    continue;
		}
	    }

	    String hostVal = host.getValue();
	    String userVal = user.getValue();

	    // Search for existing connection
	    List<ConnectionInfo> depChain =
		getConnectionManager().getDepChain(hostVal, userVal, null, null,
		null, null);
	    if (depChain != null) {
		data.setDepChain(depChain, acknowledged);
		return;
	    }

	    // Create connection, append to messages on error
	    JMXConnector connector = createConnector(request);
	    if (connector != null) {
		ConnectionInfo info = new ConnectionInfo(hostVal, userVal, null,
		    connector);

		// Get/create auth bean, append to messages on error
		AuthenticationMXBean auth = createAuthBean(request, info);
		if (auth != null) {
		    setLoginStatus(request,
			Finder.getString("login.status.user"));

		    if (userVal.equals(auth.getuser())) {
			data.push(info, acknowledged);
			return;
		    }

		    try {
			AuthPrompter prompter = new UserPrompter();
			do {
			    if (authConverse(request, auth, prompter)) {
				acknowledged |= prompter.isAcknowledged();
				data.push(info, acknowledged);
				return;
			    }

			    // Authentication failed
			    user.setErrored(true);

			    // Add generic auth failure message if not already
			    // provided by server
			    if (messages.isEmpty()) {
				messages.add(new DialogMessage(
				    Finder.getString("login.err.user.auth",
				    hostVal, userVal),
				    JOptionPane.ERROR_MESSAGE));
			    }

			// No chance to edit, so keep iterating here
			} while (!host.isEditable() && !user.isEditable());

		    // Thrown by authConverse
		    } catch (ActionRegressedException e) {
		    }
		}
	    }
	}
    }

    private void gatherRoleData(LoginRequest request, LoginData data)
	throws ActionAbortedException, ActionFailedException,
	ActionRegressedException {

	LoginProperty<String> host = request.getHost();
	String hostVal = host.getValue();

	LoginProperty<String> user = request.getUser();
	String userVal = user.getValue();

	LoginProperty<String> zone = request.getZone();
	String zoneVal = zone.getValue();

	LoginProperty<String> zoneUser = request.getZoneUser();
	String zoneUserVal = zoneUser.getValue();

	// Get/create auth bean, append to messages on error
	AuthenticationMXBean userAuth = createAuthBean(request, data.peek(0));
	if (userAuth == null) {
	    // Not likely, but handle it anyway
	    requestFailed(request);
	}

	LoginProperty<String> role = request.getRole();
	List<DialogMessage> messages = request.getMessages();

	setLoginStatus(request, Finder.getString("login.status.roles",
	    request.getUser().getValue()));
	List<String> roles = userAuth.getroles();

	// Validate any preset value prior to prompting user
	if (role.getValue() != null || !role.isEditable()) {
	    isRoleValid(request, roles, false);
	}

	// Loop until no role is chosen, or chosen role is authenticated
	while (true) {
	    boolean acknowledged = false;

	    // Refresh each iteration in case role.isEditableOnError()
	    boolean roleEditable = role.isEditable();

	    // If an error cannot be fixed by the user...
	    if (!roleEditable && role.isErrored()) {
		requestFailed(request);
	    }

	    if ((roleEditable && !roles.isEmpty()) || !messages.isEmpty()) {
		try {
		    promptForRole(request, roles, false);
		} finally {
		    acknowledged = true;

		    // User only needs to see any message once, presumably
		    messages.clear();

		    role.setErrored(false);
		}

		if (!isRoleValid(request, roles, false)) {
		    continue;
		}
	    }

	    String roleVal = role.getValue();
	    if (roleVal == null) {
		// No need to keep going
		return;
	    }

	    // Search for existing connection
	    List<ConnectionInfo> depChain = getConnectionManager().getDepChain(
		hostVal, userVal, roleVal, null, null, null);
	    if (depChain != null) {
		data.setDepChain(depChain, acknowledged);
		return;
	    }

	    try {
		byte[] token = userAuth.createToken();

		// Create connection, append to messages on error
		JMXConnector connector = createConnector(request);
		if (connector != null) {
		    ConnectionInfo info = new ConnectionInfo(hostVal, userVal,
			roleVal, connector);

		    // Create auth bean, append to messages on error
		    AuthenticationMXBean roleAuth = createAuthBean(request,
			info);
		    if (roleAuth != null) {
			roleAuth.redeemToken(userVal, token);

			AuthPrompter prompter = new RolePrompter();
			do {
			    if (authConverse(request, roleAuth, prompter)) {
				acknowledged |= prompter.isAcknowledged();
				data.push(info, acknowledged);
				return;
			    }

			    // Authentication failed
			    role.setErrored(true);

			    // Add generic auth failure message if not already
			    // provided by server
			    if (messages.isEmpty()) {
				messages.add(new DialogMessage(
				    Finder.getString("login.err.role.auth",
				    hostVal, userVal, roleVal),
				    JOptionPane.ERROR_MESSAGE));
			    }

			// No chance to edit role, so keep iterating here
			} while (!role.isEditable());
		    }
		}

	    // Thrown by createToken/redeemToken
	    } catch (ObjectException e) {
		messages.add(new DialogMessage(Finder.getString(
		    "login.err.io", hostVal), JOptionPane.ERROR_MESSAGE));

	    // Thrown by authConverse
	    } catch (ActionRegressedException e) {
	    }
	}
    }

    private void gatherZoneHostAndUserData(LoginRequest request, LoginData data)
	throws ActionAbortedException, ActionFailedException,
	ActionRegressedException {

	IOMXBean zcon = createZonesBridgeBean(request, data.peek(0));
	UtilMXBean zutil = createZonesUtilBean(request, data.peek(0));
	if (zcon == null || zutil == null) {
	    requestFailed(request);
	}

	LoginProperty<String> zone = request.getZone();
	LoginProperty<String> zoneUser = request.getZoneUser();
	List<DialogMessage> messages = request.getMessages();

	List<String> zones = null;
	try {
	    zones = zutil.getZones(ZoneState.RUNNING);
	} catch (ObjectException e) {
	    messages.add(new DialogMessage(Finder.getString(
                "login.err.io", request.getHost().getValue()),
                JOptionPane.ERROR_MESSAGE));
	    requestFailed(request);
	}

	// Validate any preset value prior to prompting user
	if (zone.getValue() != null || !zone.isEditable()) {
	    isZoneValid(request, zones);
	}
	if (zoneUser.getValue() != null || !zoneUser.isEditable()) {
	    isZoneUserValid(request);
	}

	// Loop until connected to zone and authenticated as zoneUser
	while (true) {
	    boolean acknowledged = false;

	    // Refresh each iteration in case zone/zoneUser.isEditableOnError()
	    boolean zoneEditable = zone.isEditable();
	    boolean zoneUserEditable = zoneUser.isEditable();

	    // If an error cannot be fixed by the user...
	    if (!zoneEditable && (zone.isErrored() ||
		(!zoneUserEditable && zoneUser.isErrored()))) {

		requestFailed(request);
	    }

	    if (zoneEditable || zoneUserEditable || !messages.isEmpty()) {
		try {
		    promptForZoneAndUser(request, zones);
		} finally {
		    acknowledged = true;

		    // User only needs to see any message once, presumably
		    messages.clear();

		    zone.setErrored(false);
		    zoneUser.setErrored(false);
		}

		if (!isZoneValid(request, zones) || !isZoneUserValid(request)) {
		    continue;
		}
	    }

	    String zoneVal = zone.getValue();
	    if (zoneVal == null) {
		// No need to keep going
		return;
	    }

	    String zoneUserVal = zoneUser.getValue();

	    // Search for existing connection
	    List<ConnectionInfo> depChain =
		getConnectionManager().getDepChain(
		request.getHost().getValue(), request.getUser().getValue(),
		request.getRole().getValue(), zoneVal, zoneUserVal, null);
	    if (depChain != null) {
		data.setDepChain(depChain, acknowledged);
		return;
	    }

	    JMXConnector connector = createZoneConnector(request, zcon);
	    if (connector != null) {
		ConnectionInfo info = new ConnectionInfo(
		    request.getHost().getValue(), request.getUser().getValue(),
		    request.getRole().getValue(), zoneVal, zoneUserVal, null,
		    connector);

		// Get/create auth bean, append to messages on error
		AuthenticationMXBean auth = createAuthBean(request, info);
		if (auth != null) {
		    if (zoneUserVal.equals(auth.getuser())) {
			data.push(info, acknowledged);
			return;
		    }

		    try {
			AuthPrompter prompter = new ZoneUserPrompter();
			do {
			    if (authConverse(request, auth, prompter)) {
				acknowledged |= prompter.isAcknowledged();
				data.push(info, acknowledged);
				return;
			    }

			    // Authentication failed
			    zoneUser.setErrored(true);

			    // Add generic auth failure message if not already
			    // provided by server
			    if (messages.isEmpty()) {
				messages.add(new DialogMessage(
				    Finder.getString("login.err.user.auth",
				    zoneVal, zoneUserVal),
				    JOptionPane.ERROR_MESSAGE));
			    }

			// No chance to edit, so keep iterating here
			} while (!zone.isEditable() && !zoneUser.isEditable());

		    // Thrown by authConverse
		    } catch (ActionRegressedException e) {
		    }
		}
	    }
	}
    }

    private void gatherZoneRoleData(LoginRequest request, LoginData data)
	throws ActionAbortedException, ActionFailedException,
	ActionRegressedException {

	LoginProperty<String> host = request.getHost();
	String hostVal = host.getValue();

	LoginProperty<String> user = request.getUser();
	String userVal = user.getValue();

	LoginProperty<String> role = request.getRole();
	String roleVal = role.getValue();

	LoginProperty<String> zone = request.getZone();
	String zoneVal = zone.getValue();

	LoginProperty<String> zoneUser = request.getZoneUser();
	String zoneUserVal = zoneUser.getValue();

	// Get/create auth bean, append to messages on error
	AuthenticationMXBean userAuth = createAuthBean(request, data.peek(0));
	if (userAuth == null) {
	    // Not likely, but handle it anyway
	    requestFailed(request);
	}

	LoginProperty<String> zoneRole = request.getZoneRole();
	List<DialogMessage> messages = request.getMessages();

	setLoginStatus(request, Finder.getString("login.status.roles",
	    request.getZoneUser().getValue()));
	List<String> roles = userAuth.getroles();

	// Validate any preset value prior to prompting user
	if (zoneRole.getValue() != null || !zoneRole.isEditable()) {
	    isRoleValid(request, roles, true);
	}

	IOMXBean zcon = null;

	// Loop until no role is chosen, or chosen role is authenticated
	while (true) {
	    boolean acknowledged = false;

	    // Refresh each iteration in case zoneRole.isEditableOnError()
	    boolean zoneRoleEditable = zoneRole.isEditable();

	    // If an error cannot be fixed by the user...
	    if (!zoneRoleEditable && zoneRole.isErrored()) {
		requestFailed(request);
	    }

	    if ((zoneRoleEditable && !roles.isEmpty()) || !messages.isEmpty()) {
		try {
		    promptForRole(request, roles, true);
		} finally {
		    acknowledged = true;

		    // User only needs to see any message once, presumably
		    messages.clear();

		    zoneRole.setErrored(false);
		}

		if (!isRoleValid(request, roles, true)) {
		    continue;
		}
	    }

	    String zoneRoleVal = zoneRole.getValue();
	    if (zoneRoleVal == null) {
		// No need to keep going
		return;
	    }

	    // Search for existing connection
	    List<ConnectionInfo> depChain = getConnectionManager().getDepChain(
		hostVal, userVal, roleVal, zoneVal, zoneUserVal, zoneRoleVal);
	    if (depChain != null) {
		data.setDepChain(depChain, acknowledged);
		return;
	    }

	    try {
		byte[] token = userAuth.createToken();

		if (zcon == null) {
		    // Peek back to the host-based connection
		    zcon = createZonesBridgeBean(request, data.peek(1));
		    if (zcon == null) {
			requestFailed(request);
		    }
		}

		// Create connection, append to messages on error
		JMXConnector connector = createZoneConnector(request, zcon);
		if (connector != null) {
		    ConnectionInfo info = new ConnectionInfo(hostVal, userVal,
			roleVal, zoneVal, zoneUserVal, zoneRoleVal, connector);

		    // Create auth bean, append to messages on error
		    AuthenticationMXBean roleAuth = createAuthBean(request,
			info);
		    if (roleAuth != null) {
			roleAuth.redeemToken(userVal, token);

			AuthPrompter prompter = new ZoneRolePrompter();
			do {
			    if (authConverse(request, roleAuth, prompter)) {
				acknowledged |= prompter.isAcknowledged();
				data.push(info, acknowledged);
				return;
			    }

			    // Authentication failed
			    zoneRole.setErrored(true);

			    // Add generic auth failure message if not already
			    // provided by server
			    if (messages.isEmpty()) {
				messages.add(new DialogMessage(
				    Finder.getString("login.err.zonerole.auth",
				    hostVal, userVal, roleVal, zoneVal,
				    zoneUserVal, zoneRoleVal),
				    JOptionPane.ERROR_MESSAGE));
			    }

			// No chance to edit role, so keep iterating here
			} while (!zoneRole.isEditable());
		    }
		}

	    // Thrown by createToken/redeemToken
	    } catch (ObjectException e) {
		messages.add(new DialogMessage(Finder.getString(
		    "login.err.io", hostVal), JOptionPane.ERROR_MESSAGE));

	    // Thrown by authConverse
	    } catch (ActionRegressedException e) {
	    }
	}
    }

    private MBeanServerConnection getMBeanServerConnection(LoginRequest request,
	ConnectionInfo info) {

	try {
	    return info.getConnector().getMBeanServerConnection();
	} catch (IOException e) {
	    request.getMessages().add(new DialogMessage(
		Finder.getString("login.err.io",
		request.getHost().getValue()),
		JOptionPane.ERROR_MESSAGE));
	}
	return null;
    }

    private <T> boolean inSet(LoginProperty<T> property, List<T> valid,
	String resource, LoginRequest request) {

	if (!valid.contains(property.getValue())) {
	    String message = Finder.getString(resource,
		request.getHost().getValue(),
		request.getUser().getValue(),
		request.getRole().getValue(),
		request.getZone().getValue(),
		request.getZoneUser().getValue(),
		request.getZoneRole().getValue());

	    request.getMessages().add(new DialogMessage(message,
		JOptionPane.ERROR_MESSAGE));

	    property.setErrored(true);

	    if (property.isEditable()) {
		property.setValue(null);
	    }

	    return false;
	}

	return true;
    }

    private boolean isHostValid(LoginRequest request)
	throws ActionFailedException {

	LoginProperty<String> host = request.getHost();
	return isPropertyNonEmpty(host, request, "login.err.host.empty") &&
	    isPropertyValid(host, request);
    }

    private boolean isPropertyNonEmpty(LoginProperty<String> property,
	LoginRequest request, String resource) {

	String value = property.getValue();
	if (value == null || value.isEmpty()) {
	    request.getMessages().add(new DialogMessage(Finder.getString(
		resource), JOptionPane.ERROR_MESSAGE));
	    property.setErrored(true);
	    return false;
	}

	return true;
    }

    private <T> boolean isPropertyValid(LoginProperty<T> property,
	LoginRequest request, T... valid) throws ActionFailedException {

	try {
	    property.validate(request, valid);
	    return true;
	} catch (LoginPropertyException e) {
	    property.setErrored(true);
	    request.getMessages().add(e.getDialogMessage());
	    if (e.isFatal()) {
		requestFailed(request);
	    }
	    return false;
	}
    }

    private boolean isRoleValid(LoginRequest request, List<String> roles,
	boolean isZone) throws ActionFailedException {

	LoginProperty<String> role = isZone ? request.getZoneRole() :
	    request.getRole();

	return (role.getValue() == null ||
	    inSet(role, roles, "login.err.role.invalid", request)) &&
	    isPropertyValid(role, request,
	    roles.toArray(new String[roles.size()]));
    }

    private boolean isUserValid(LoginRequest request)
	throws ActionFailedException {

	LoginProperty<String> user = request.getUser();
	return isPropertyNonEmpty(user, request, "login.err.user.empty") &&
	    isPropertyValid(user, request);
    }

    private boolean isZoneValid(LoginRequest request, List<String> zones)
	throws ActionFailedException {

	LoginProperty<String> zone = request.getZone();
	if (zone.getValue() == null) {
	    request.getMessages().add(new DialogMessage(Finder.getString(
		"login.err.zone.empty"), JOptionPane.ERROR_MESSAGE));
	    zone.setErrored(true);
	    return false;
	}

	String resource = "login.err.zone.invalid";
	if (request.getRole().getValue() != null) {
	    resource += ".role";
	}

	return inSet(zone, zones, resource, request) &&
	    isPropertyValid(zone, request,
	    zones.toArray(new String[zones.size()]));
    }

    private boolean isZoneUserValid(LoginRequest request)
	throws ActionFailedException {

	LoginProperty<String> zoneUser = request.getZoneUser();
	return isPropertyNonEmpty(zoneUser, request,
	    "login.err.zoneuser.empty") && isPropertyValid(zoneUser, request);
    }

    private void requestFailed(LoginRequest request)
	throws ActionFailedException {

	promptForFailedRequest(request);

	List<DialogMessage> messages = request.getMessages();
	throw new ActionFailedException(messages.isEmpty() ? null :
	    messages.get(0).getText());
    }
}
