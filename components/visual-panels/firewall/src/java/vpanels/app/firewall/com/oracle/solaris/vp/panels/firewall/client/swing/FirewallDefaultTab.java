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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.Component;
import java.util.Map;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;

public class FirewallDefaultTab
    extends SettingsControl<FirewallPanelDescriptor, FirewallSettingsPanel>
    {

    //
    // Static data
    //

    public static final String ID = "global_default";
    private static final String NAME =
	Finder.getString("settings.objects.default.title");
    private static final String DEFAULT_POLICY_DESC =
        Finder.getString("description.policy.default");

    //
    // Constructors
    //

    public FirewallDefaultTab(FirewallPanelDescriptor descriptor) {
	super(ID, NAME, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "firewall-default";
    }

    @Override
    protected UnsavedChangesAction getUnsavedChangesAction() {
	// Automatically save changes to the FirewallPanelDescriptor --
	// let MainControl prompt the user to save them to the repo
	return UnsavedChangesAction.SAVE;
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
        ActionUnauthorizedException {

	AccessProperty accessProperty = getComponent().getAccessProperty();
	MutableProperty<Boolean> enabledProperty =
	    getComponent().getEnableProperty();

	AccessPolicy policy = accessProperty.getValue();
	if (policy.getType() == Type.CUSTOM &&
	    policy.getCustomFile().isEmpty()) {

	    throw new ActionFailedException(Finder.getString(
		"error.settings.customfile.empty"));
	}

	setPropertyChangeIgnore(true);
	try {
	    getPanelDescriptor().updateAccessPolicy(policy);
	    getPanelDescriptor().getEnabledProperty().setValue(
		enabledProperty.getValue());
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
	return new FirewallSettingsPanel(
	    getPanelDescriptor().getFileSystemView(), DEFAULT_POLICY_DESC);
    }

    @Override
    protected void initComponent() {
	getComponent().setPanelDescriptor(getPanelDescriptor());
	getComponent().init(getPanelDescriptor());
    }
}
