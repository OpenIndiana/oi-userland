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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.Component;
import java.util.Map;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class FirewallOverrideTab
    extends SettingsControl<FirewallPanelDescriptor, FirewallSettingsPanel>
    {

    //
    // Static data
    //
    private static final String ID = "Override";
    private static final String NAME =
        Finder.getString("settings.objects.override.title");
    private static final String OVERRIDE_POLICY_DESC =
        Finder.getString("description.policy.override");

    //
    // Constructors
    //

    public FirewallOverrideTab(FirewallPanelDescriptor descriptor) {
	super(ID, NAME, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "firewall-override";
    }

    @Override
    protected UnsavedChangesAction getUnsavedChangesAction() {
	// Automatically save changes to the ApachePanelDescriptor --
	// let MainControl prompt the user to save them to the repo
	return UnsavedChangesAction.SAVE;
    }

    @Override
    protected boolean isChanged() {
	return (getComponent().getAccessProperty().isChanged());
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
        ActionUnauthorizedException {

	AccessProperty aProperty = getComponent().getAccessProperty();
	setPropertyChangeIgnore(true);

	try {
	    getPanelDescriptor().updateOvrAccessPolicy(aProperty.getValue());
	} catch (SecurityException e) {
	    throw new ActionUnauthorizedException(e);
	} finally {
	    setPropertyChangeIgnore(false);
	}
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {
	setPropertyChangeSource(getPanelDescriptor());
	super.start(navigator, parameters);
    }

    //
    // SwingControl methods
    //

    @Override
    protected FirewallSettingsPanel createComponent() {
	return new FirewallSettingsPanel(null, OVERRIDE_POLICY_DESC,
	    Type.NONE, Type.DENY, Type.ALLOW);
    }

    @Override
    protected void initComponent() {
	getComponent().setPanelDescriptor(getPanelDescriptor());
	getComponent().init(getPanelDescriptor().getOvrAccessPolicy());
    }
}
