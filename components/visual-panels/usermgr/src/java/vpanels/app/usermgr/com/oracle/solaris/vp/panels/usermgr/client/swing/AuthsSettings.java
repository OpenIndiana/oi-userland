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
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import javax.swing.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;


/**
 * Implements Authorization Settings in the Advanced
 * Settings
 */
public class AuthsSettings extends AdvancedSettings {

    private static final String NAME =
    	Finder.getString("usermgr.advanced.auths");
    private static final Icon ICON = Finder.getIcon(
	"images/user-24.png");

    private UserMgrPanelDescriptor panelDesc = null;
    private UserManagedObject userObj = null;
    private AuthsPanel panel = null;

    public AuthsSettings() {
	super(NAME, ICON);
    }

    public void setUser(UserManagedObject userObj) {
	if (panel == null) {
		panel = new AuthsPanel(panelDesc, userObj);
	}
	panel.setUser(userObj);
	getProperty().update(userObj.getAuths(), false);
    }

    public void updateUser() {
	userObj = panel.updateUser();
	getProperty().setValue(userObj.getAuths());
    }

    public boolean isChanged() {
        if (userObj != null) {
	    return (userObj.getAuthsProperty().isChanged());
	} else {
	    return false;
	}
    }

    public void init(UserMgrPanelDescriptor panelDesc) {
	this.panelDesc = panelDesc;
    }

    public JPanel getPanel() {
    	return panel;
    }
}
