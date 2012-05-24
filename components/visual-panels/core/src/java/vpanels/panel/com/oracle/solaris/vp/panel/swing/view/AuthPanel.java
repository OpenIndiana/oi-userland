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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.BorderLayout;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.util.misc.NetUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class AuthPanel extends JPanel {
    //
    // Instance data
    //

    private ConnectionInfo info;
    private boolean privileged;
    private JLabel label;
    private JButton button;

    //
    // Constructors
    //

    public AuthPanel() {
	setOpaque(false);
	label = new JLabel();

	button = new JButton();
	new RolloverHandler(button);

	int gap = GUIUtil.getHalfGap();
	setLayout(new BorderLayout());
	add(label, BorderLayout.CENTER);
	add(button, BorderLayout.EAST);
    }

    //
    // AuthPanel methods
    //

    public JButton getButton() {
	return button;
    }

    public ConnectionInfo getConnectionInfo() {
	return info;
    }

    public boolean getPrivileged() {
	return privileged;
    }

    public void setConnectionInfo(ConnectionInfo info) {
	this.info = info;
	updateAuth();
    }

    public void setPrivileged(boolean privileged) {
	this.privileged = privileged;
	updateAuth();
    }

    protected void updateAuth() {
	label.setText(Finder.getString("auth.label", toString(info, true)));

	button.setIcon(Finder.getIcon(privileged ?
	    "images/auth/lock/authorized-16.png" :
	    "images/auth/lock/unauthorized-16.png"));

	button.setToolTipText(Finder.getString(privileged ?
	    "auth.tooltip.authorized" : "auth.tooltip.unauthorized"));
    }

    //
    // Static methods
    //

    public static String toString(String host, String user, String role,
	String zone, String zoneUser, String zoneRole, boolean shortForm) {

	if (NetUtil.isLoopbackAddress(host)) {
	    host = NetUtil.getHostName();
	}

	StringBuilder resource = new StringBuilder("auth.text");
	if (shortForm) {
	    resource.append(".short");
	}

	resource.append(".host.user");
	if (role != null) {
	    resource.append(".role");
	}

	if (zone != null) {
	    resource.append(".zone.user");
	    if (zoneRole != null) {
		resource.append(".role");
	    }
	}

        return Finder.getString(resource.toString(), host, user, role, zone,
	    zoneUser, zoneRole);
    }

    public static String toString(LoginInfo info, boolean shortForm) {
	if (info == null) {
	    return null;
	}

        return toString(info.getHost(), info.getUser(), info.getRole(),
	    info.getZone(), info.getZoneUser(), info.getZoneRole(), shortForm);
    }

    public static String toString(LoginRequest request, boolean shortForm) {
	if (request == null) {
	    return null;
	}

	boolean isZone = request.getZonePrompt().getValue();
	String zone = isZone ? request.getZone().getValue() : null;
	String zoneUser = isZone ? request.getZoneUser().getValue() : null;
	String zoneRole = isZone ? request.getZoneRole().getValue() : null;

        return toString(request.getHost().getValue(),
	    request.getUser().getValue(), request.getRole().getValue(), zone,
	    zoneUser, zoneRole, shortForm);
    }
}
