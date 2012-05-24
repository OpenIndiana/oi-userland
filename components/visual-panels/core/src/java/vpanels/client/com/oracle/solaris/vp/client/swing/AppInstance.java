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

package com.oracle.solaris.vp.client.swing;

import java.awt.event.*;
import java.awt.Window;
import java.net.URL;
import java.security.*;
import java.util.*;
import java.util.logging.*;
import javax.help.*;
import javax.swing.*;
import com.oracle.solaris.vp.client.common.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.control.InvalidParameterException;
import com.oracle.solaris.vp.panel.common.view.*;
import com.oracle.solaris.vp.panel.swing.control.SwingNavigator;

@SuppressWarnings({"serial"})
public class AppInstance implements ClientContext, ConnectionListener {
    static {
	// Force early load of runtime properties
	AppProperties a = AppProperties.singleton;

	// Set look and feel unless user has a preference
	String gtk = "com.sun.java.swing.plaf.gtk.GTKLookAndFeel";

	if (System.getProperty("swing.defaultlaf") == null) {
	    String lafName = UIManager.getSystemLookAndFeelClassName();
	    // Refuse to be a victim of Solaris's Motif default
	    if (lafName.contains("MotifLookAndFeel"))
		lafName = gtk;
	    try {
		UIManager.setLookAndFeel(lafName);
	    } catch (Exception ignore) {
	    }
	}

	LookAndFeel laf = UIManager.getLookAndFeel();

	// Handle Gnome-specific bugs
	if (laf != null && laf.getClass().getName().equals(gtk)) {
	    // Gnome L&F doesn't set this correctly
	    UIManager.put("ToolTip.background", new JToolTip().getBackground());

	    // Gnome L&F is the only L&F that does this
	    UIManager.put("Slider.paintValue", Boolean.FALSE);
	}
    }

    //
    // Instance data
    //

    private App app;
    private BusyIndicator busy;
    private ConnectionInfo info;
    private HelpBroker helpBroker;
    private SwingNavigator navigator;
    private Properties hints;

    private AppLoginManager loginManager;
    private ActionListener showHelpAction;
    private ConnectionListeners cListeners = new ConnectionListeners();

    //
    // Constructors
    //

    private AppInstance(App app, Properties hints,
	List<ConnectionInfo> depChain) {

	init(app, hints);
	setDepChain(depChain);
	initNavigator();
	app.instanceCreated(this);
    }

    public AppInstance(App app, Properties hints, LoginRequest request)
	throws ActionAbortedException, ActionFailedException {

	init(app, hints);

	// Don't prompt user for acknowledgement for default local connection
        ConnectionInfo current = new ConnectionInfo(RadLoginManager.LOCAL_HOST,
	    RadLoginManager.LOCAL_USER, null, null);

	List<ConnectionInfo> depChain = loginManager.getConnectionInfo(
	    request, current);

	setDepChain(depChain);
	initNavigator();
	app.instanceCreated(this);
    }

    //
    // ConnectionListener methods
    //

    @Override
    public void connectionChanged(ConnectionEvent event) {
        // This method should only called by the ConnectionManager when a failed
        // connection has been restored
	assert info == event.getOldConnectionInfo();

	setConnectionInfo(event.getConnectionInfo());
    }

    @Override
    public void connectionFailed(ConnectionEvent event) {
	cListeners.connectionFailed(
	    new ConnectionEvent(this, event.getConnectionInfo()));
    }

    //
    // ClientContext methods
    //

    @Override
    public void addConnectionListener(ConnectionListener listener) {
	cListeners.add(listener);
    }

    @Override
    public void closeInstance(final boolean isCancel)
	throws ActionAbortedException {

	// Using PrivilegedExceptionAction offers no compile-time checking of
	// thrown Exceptions, so use this mildly awkward method instead

	final ActionAbortedException[] err = new ActionAbortedException[1];

	AccessController.doPrivileged(
	    new PrivilegedAction<Object>() {
		@Override
		public Object run() {
		    try {
			closeInstanceImp(isCancel);
		    } catch (ActionAbortedException e) {
			err[0] = e;
		    }
		    return null;
		}
	    });

	if (err[0] != null) {
	    throw err[0];
	}
    }

    @Override
    public BusyIndicator getBusyIndicator() {
	List<Control> controls = navigator.getPath();
	for (int i = controls.size() - 1; i >= 0; i--) {
	    Control control = controls.get(i);
	    if (control instanceof HasBusyIndicator) {
		BusyIndicator busy =
		    ((HasBusyIndicator)control).getBusyIndicator();

		if (busy != null) {
		    return busy;
		}
	    }
	}

	if (busy == null) {
	    busy = new SimpleBusyIndicator();
	}

	return busy;
    }

    @Override
    public ConnectionInfo getConnectionInfo() {
	return info;
    }

    @Override
    public HelpBroker getHelpBroker() {
	return helpBroker;
    }

    @Override
    public Navigator getNavigator() {
	return navigator;
    }

    @Override
    public Properties getRuntimeHints() {
	return hints;
    }

    @Override
    public ClientContext login(final LoginRequest request,
        final boolean forceNewContext) throws ActionAbortedException,
        ActionFailedException {

	// Using PrivilegedExceptionAction offers no compile-time checking of
	// thrown Exceptions, so use this mildly awkward method instead

	final ActionAbortedException[] abort = new ActionAbortedException[1];
	final ActionFailedException[] fail = new ActionFailedException[1];

	ClientContext context = AccessController.doPrivileged(
	    new PrivilegedAction<ClientContext>() {
		@Override
		public ClientContext run() {
		    try {
			return loginImp(request, forceNewContext);
		    } catch (ActionAbortedException e) {
			abort[0] = e;
		    } catch (ActionFailedException e) {
			fail[0] = e;
		    }
		    return null;
		}
	    });

	if (abort[0] != null) {
	    throw abort[0];
	}

	if (fail[0] != null) {
	    throw fail[0];
	}

	return context;
    }

    @Override
    public boolean removeConnectionListener(ConnectionListener listener) {
	return cListeners.remove(listener);
    }

    @Override
    public void showHelp() {
	Window window = navigator.getLastWindow();

	if (window == null) {
            // Absurdly, the Swing help viewer needs a non-null window to show,
            // even if that window is not visible
	    window = new Window(null);
	}

	ActionEvent event = new ActionEvent(
	    window, ActionEvent.ACTION_PERFORMED, "showHelp");

	showHelpAction.actionPerformed(event);
    }

    @Override
    public LoginHistory getLoginHistory() {
        return app.getLoginHistoryManager();
    }

    //
    // AppInstance methods
    //

    /**
     * Closes this {@code AppInstance} unconditionally.
     */
    public void close() {
	ConnectionInfo info = getConnectionInfo();
	if (info != null) {
	    app.getConnectionManager().remove(this, info);
	}
	app.instanceClosed(this);
    }

    public App getApp() {
	return app;
    }

    /**
     * Sets the dependency chain of {@link ConnectionListener}s derived from the
     * login process.
     *
     * @param	    depChain
     *		    a dependency chain of {@link ConnectionInfo}s
     */
    protected void setDepChain(List<ConnectionInfo> depChain) {
	ConnectionInfo oldInfo = getConnectionInfo();
	ConnectionInfo info = depChain.get(0);

	if (oldInfo != info) {
	    ConnectionManager connManager = app.getConnectionManager();
	    if (oldInfo != null) {
		connManager.remove(this, oldInfo);
	    }

	    connManager.add(this, depChain);
	    setConnectionInfo(info);
	}
    }

    /**
     * Sets the current connection, notifying any registered {@link
     * ConnectionListener}s.
     *
     * @param	    info
     *		    a {@link ConnectionInfo}
     */
    protected void setConnectionInfo(ConnectionInfo info) {
	ConnectionInfo oldInfo = getConnectionInfo();

	if (oldInfo != info) {
	    this.info = info;

	    // Set and notify any listeners (ie, panels) of change
	    cListeners.connectionChanged(
		new ConnectionEvent(this, info, oldInfo));
	}
    }

    //
    // Private methods
    //

    private void closeInstanceImp(boolean isCancel)
	throws ActionAbortedException {

	JDialog dialog = loginManager.getDialog();
	if (dialog != null && dialog.isVisible()) {
	    throw new ActionAbortedException();
	}

	try {
	    // Unwind navigation stack to force user to handle pending changes
	    navigator.goToAsyncAndWait(isCancel, null);

	} catch (NavigationAbortedException e) {
	    throw new ActionAbortedException(e);

	} catch (NavigationFailedException e) {
	    // Should not be possible

	} catch (InvalidAddressException e) {
	    // Should not be possible

	} catch (InvalidParameterException e) {
	    // Should not be possible

	} catch (EmptyNavigationStackException e) {
	    // Should not be possible

	} catch (RootNavigableNotControlException e) {
	    // Should not be possible
	}

	close();
    }

    private void createHelp() {
	String helpSetName =
	    getClass().getPackage().getName().replaceAll("\\.", "/") +
	    "/help/app";

	HelpSet helpSet;
	try {
	    ClassLoader loader = getClass().getClassLoader();
	    URL url = HelpSet.findHelpSet(loader, helpSetName);
	    helpSet = new HelpSet(loader, url);
	} catch (HelpSetException e) {
	    String message = String.format(
		"could not load helpset: %s", helpSetName);

	    Logger.getLogger(getClass().getName()).log(
		Level.WARNING, message, e);
	    helpSet = new HelpSet();
	}

	helpBroker = helpSet.createHelpBroker();
	showHelpAction = new CSH.DisplayHelpFromSource(helpBroker);
    }

    private void createNavigator() {
	navigator = new SwingNavigator();

	// Re-navigate to most appropriate path on error
	navigator.addNavigationListener(new NavigationErrorHandler());
    }

    private void init(App app, Properties hints) {
	this.app = app;
	this.hints = hints;

	createNavigator();
	createHelp();

        loginManager = new AppLoginManager(app.getConnectionManager(),
	    new HasWindow() {
		@Override
		public Window getComponent() {
		    return SwingNavigator.getLastWindow(getNavigator());
		}
	    });
    }

    private void initNavigator() {
	AppRootControl root = new AppRootControl(this);
	try {
	    navigator.goToAsyncAndWait(false, null, root);
	} catch (NavigationException unlikely) {
	}
    }

    private ClientContext loginImp(LoginRequest request,
        boolean forceNewContext) throws ActionAbortedException,
        ActionFailedException {

	if (request == null) {
	    LoginProperty<String> host =
		new LoginProperty<String>(info.getHost(), false);

	    LoginProperty<String> user =
		new LoginProperty<String>(info.getUser(), false);

	    LoginProperty<String> role =
		new LoginProperty<String>(info.getRole(), false);

	    LoginProperty<String> zone =
		new LoginProperty<String>(info.getZone(), false);

	    LoginProperty<String> zoneUser =
		new LoginProperty<String>(info.getZoneUser(), false);

	    LoginProperty<String> zoneRole =
		new LoginProperty<String>(info.getZoneRole(), false);

            boolean zonePromptVal = zone.getValue() != null ||
		zoneUser.getValue() != null || zoneRole.getValue() != null;
	    LoginProperty<Boolean> zonePrompt =
		new LoginProperty<Boolean>(zonePromptVal, false);

            request = new LoginRequest(host, user, role, zonePrompt, zone,
		zoneUser, zoneRole);
	}

	List<ConnectionInfo> depChain = loginManager.getConnectionInfo(
	    request, getConnectionInfo());

	ConnectionInfo info = depChain.get(0);

	ClientContext context;

	// Open new instance (window) if changing host/zone
	if (forceNewContext || !this.info.matchesHost(info.getHost()) ||
	    !this.info.matchesZone(info.getZone())) {
	    context = new AppInstance(app, hints, depChain);
	} else {
	    setDepChain(depChain);
	    context = this;
	}

	return context;
    }
}
