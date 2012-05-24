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

import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.security.cert.Certificate;
import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.client.common.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.util.swing.GUIUtil;
import com.oracle.solaris.vp.util.swing.glass.*;

public class AppLoginManager extends RadLoginManager {
    //
    // Instance data
    //

    private HasWindow hasWindow;
    private LoginPane loginPane;
    private BusyGlassPane busyPane;
    private CertificatePane certPane;
    private LoginDialog dialog;
    private Timer loginTimer;

    //
    // Constructors
    //

    public AppLoginManager(ConnectionManager manager, HasWindow hasWindow) {
	super(manager);
	this.hasWindow = hasWindow;
    }

    //
    // RadLoginManager methods
    //

    @Override
    public List<ConnectionInfo> getConnectionInfo(LoginRequest request,
        LoginInfo current) throws ActionAbortedException, ActionFailedException
    {
	final Window owner = hasWindow == null ?
	    null : hasWindow.getComponent();

	if (dialog != null && dialog.getOwner() != owner) {
	    dialog.dispose();
	    dialog = null;
	}

	if (dialog == null) {
	    // Lazy create
	    if (loginPane == null) {
		loginPane = new LoginPane();
		certPane = new CertificatePane();
		busyPane = new BusyGlassPane();
	    }

	    dialog = new LoginDialog(owner, loginPane, certPane, busyPane);
	}

	// Get root and glass panes.
	final Window window = (hasWindow != null)
	    ? hasWindow.getComponent() : null;
	final RootPaneContainer rootPane = (window instanceof RootPaneContainer)
	    ? (RootPaneContainer) window : null;
	final Component glassPane = (rootPane != null)
	    ? rootPane.getGlassPane() : null;

	EventQueue.invokeLater(
	    new Runnable() {
		@Override
		public void run() {
		    // Set temp blocking pane for static logins.
		    if (rootPane != null) {
			rootPane.setGlassPane(new BlockingGlassPane());
			rootPane.getGlassPane().setVisible(true);
		    }
		    dialog.setLocationRelativeTo(owner);
		}
	    });

	try {
	    return super.getConnectionInfo(request, current);
	} finally {
	    GUIUtil.invokeAndWait(
		new Runnable() {
		    @Override
		    public void run() {
			dialog.setVisible(false);

			// Restore glass pane.
			if (rootPane != null) {
			    rootPane.setGlassPane(glassPane);
			    rootPane.getGlassPane().setVisible(false);
			}

			// Stop login timer.
			loginTimer.stop();
		    }
		});
	}
    }

    @Override
    public File getTrustStoreFile() {
	return App.TRUSTSTORE_FILE;
    }

    @Override
    protected void promptForAck(LoginRequest request)
	throws ActionAbortedException {

	dialog.getLoginPane().promptForAck(request);
    }

    @Override
    protected void promptForAuth(LoginRequest request,
        List<LoginProperty> properties, boolean isZone, boolean isUserAuth,
        boolean isFirst) throws ActionAbortedException, ActionRegressedException
    {
        dialog.getLoginPane().promptForAuth(request, properties, isZone,
	    isUserAuth, isFirst);
    }

    @Override
    protected void promptForCertificate(
	String host, Certificate certificate) throws ActionAbortedException {

	dialog.getCertificatePane().promptForCertificate(host, certificate);
    }

    @Override
    protected void promptForFailedRequest(LoginRequest request) {
        dialog.getLoginPane().promptForFailedRequest(request);
    }

    @Override
    protected void promptForHostAndUser(LoginRequest request)
	throws ActionAbortedException {

	dialog.getLoginPane().promptForHostAndUser(request);
    }

    @Override
    protected void promptForRole(LoginRequest request, List<String> roles,
        boolean isZone) throws ActionAbortedException, ActionRegressedException
    {
	dialog.getLoginPane().promptForRole(request, roles, isZone);
    }

    @Override
    protected void promptForZoneAndUser(LoginRequest request,
        List<String> zones) throws ActionAbortedException,
        ActionRegressedException {

	dialog.getLoginPane().promptForZoneAndUser(request, zones);
    }

    @Override
    protected void setLoginStatus(LoginRequest request, String status) {
	busyPane.setMessage(status);

	// Start login timer.
	if (loginTimer != null) {
	    loginTimer.stop(); // In case timer is still running.
	} else {
	    loginTimer = new Timer(busyPane.getDelay(), new ActionListener() {
		public void actionPerformed(ActionEvent evt) {
		    loginTimer.stop();

		    if (!dialog.isVisible()) {
			// Fade immediately.
			busyPane.setDelay(0);

			// Hide previously displayed login and cert panes.
			loginPane.setVisible(false);
			certPane.setVisible(false);

			// Display busy indicator.
			dialog.getGlassPane().setVisible(true);
			dialog.setVisible(true);
		    }
		}});
	}
	loginTimer.start();
    }

    //
    // AppLoginManager methods
    //

    public LoginDialog getDialog() {
	return dialog;
    }
}
