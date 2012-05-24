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

import java.security.cert.Certificate;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.action.ActionAbortedException;
import com.oracle.solaris.vp.util.misc.DialogMessage;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.SettingsButtonBar;

@SuppressWarnings({"serial"})
public class CertificatePane extends DialogPane {
    //
    // Instance data
    //

    private CertificateCollapsiblePane certPanel;

    //
    // Constructors
    //

    public CertificatePane() {
	certPanel = new CertificateCollapsiblePane();
	setContent(certPanel, false, false);

	SettingsButtonBar buttonBar = getButtonBar();
	JButton cancelButton = buttonBar.getCancelButton();
	cancelButton.addActionListener(setClickedButtonActionListener);
	cancelButton.setText(Finder.getString("login.button.no"));

	JButton okayButton = buttonBar.getOkayButton();
	okayButton.addActionListener(setClickedButtonActionListener);
	okayButton.setText(Finder.getString("login.button.yes"));
    }

    //
    // CertificatePane methods
    //

    public void promptForCertificate(String host, Certificate certificate)
	throws ActionAbortedException {

	DialogMessage message = new DialogMessage(Finder.getString(
	    "certificate.message", host), JOptionPane.WARNING_MESSAGE);

	List<DialogMessage> messages = new ArrayList<DialogMessage>(1);
	messages.add(message);
	getMessagePanel().setMessages(messages);

	certPanel.setCollapsed(true);
	certPanel.getCertificatePane().setCertificate(certificate);

	awaitOkay();
    }
}
