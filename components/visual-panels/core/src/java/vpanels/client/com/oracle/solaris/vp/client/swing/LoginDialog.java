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
import java.beans.*;
import javax.swing.WindowConstants;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.ExtDialog;
import com.oracle.solaris.vp.util.swing.glass.*;
import com.oracle.solaris.vp.util.swing.layout.*;

public class LoginDialog extends ExtDialog {
    //
    // Instance data
    //

    private WindowListener listener =
	new WindowAdapter() {
	    @Override
	    public void windowClosing(WindowEvent e) {
		loginPane.setClickedButton(
		    loginPane.getButtonBar().getCancelButton());
		certPane.setClickedButton(
		    loginPane.getButtonBar().getCancelButton());
	    }
	};

    private LoginPane loginPane;
    private CertificatePane certPane;
    private BusyGlassPane busyPane;

    private PropertyChangeListener promptListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(final PropertyChangeEvent event) {
		EventQueue.invokeLater(
		    new Runnable() {
			@Override
			public void run() {
			    if (event.getNewValue().equals(true)) {
				Component comp = (Component)event.getSource();
				if (comp == loginPane) {
				    certPane.setVisible(false);
				} else if (comp == certPane) {
				    loginPane.setVisible(false);
				}
				comp.setVisible(true);
				getGlassPane().setVisible(false);
				setVisible(true);
			    } else {
				getGlassPane().setVisible(true);
			    }
			}
		    });
	    }
	};

    //
    // Constructors
    //

    public LoginDialog(Window owner, LoginPane loginPane,
	CertificatePane certPane, BusyGlassPane busyPane) {

	super(owner, Finder.getString("login.title"),
	    Dialog.DEFAULT_MODALITY_TYPE);

	this.loginPane = loginPane;
	this.certPane = certPane;
	this.busyPane = busyPane;

	LayeredGlassPane glass = new LayeredGlassPane();
	glass.add(new BlockingGlassPane(false));
	glass.add(busyPane);

	setGlassPane(glass);

	loginPane.addPropertyChangeListener(DialogPane.PROPERTY_PROMPTING,
	    promptListener);

	certPane.addPropertyChangeListener(DialogPane.PROPERTY_PROMPTING,
	    promptListener);

	addWindowListener(listener);

	ColumnLayout layout = new ColumnLayout(VerticalAnchor.FILL);
	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL);

	Container cont = getContentPane();
	cont.setLayout(layout);
	cont.add(loginPane, c);
	cont.add(certPane, c);

	setDefaultCloseOperation(WindowConstants.HIDE_ON_CLOSE);
	pack();
	setAutoResizeEnabled(true);
    }

    //
    // Window methods
    //

    @Override
    public void dispose() {
	loginPane.removePropertyChangeListener(
	    DialogPane.PROPERTY_PROMPTING, promptListener);
	certPane.removePropertyChangeListener(
	    DialogPane.PROPERTY_PROMPTING, promptListener);
	removeWindowListener(listener);
	super.dispose();
    }

    //
    // LoginDialog methods
    //

    public CertificatePane getCertificatePane() {
	return certPane;
    }

    public LoginPane getLoginPane() {
	return loginPane;
    }
}
