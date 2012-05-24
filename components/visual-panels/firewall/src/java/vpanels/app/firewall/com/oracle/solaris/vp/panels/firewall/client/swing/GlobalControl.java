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

import java.net.UnknownHostException;
import java.util.Map;
import java.util.logging.Level;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.smf.SmfUtil;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class GlobalControl extends TabbedControl<FirewallPanelDescriptor> {
    //
    // Static data
    //

    public static final String ID = "global";
    public static final String NAME = Finder.getString("global.name");

    //
    // Instance data
    //

    FirewallDefaultTab defaultTab;
    FirewallOverrideTab overrideTab;
    FirewallOpenPortsTab openPortsTab;

    ChangeableAggregator changeableAggregator = new ChangeableAggregator();

    //
    // Constructors
    //

    public GlobalControl(FirewallPanelDescriptor descriptor) {
	super(ID, NAME, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public void childStarted(Control child) {
	super.childStarted(child);

	ChangeableAggregator childAgg =
	    ((SettingsControl<?, ?>)child).getComponent().
	    getChangeableAggregator();

	if (changeableAggregator.getChangeables().contains(childAgg))
	    return;

	changeableAggregator.addChangeables(childAgg);
    }

    @Override
    protected boolean isChanged() {
	return (changeableAggregator.isChanged());
    }

    @Override
    protected void reset() throws ActionAbortedException, ActionFailedException
    {
	getPanelDescriptor().resetPolicies();
	changeableAggregator.reset();
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	setPropertyChangeIgnore(true);
	try {
	    getPanelDescriptor().saveToRepo();
	} catch (ScfException e) {
	    SmfUtil.throwActionException(e);
	} catch (UnknownHostException e) {
	    getLog().log(Level.SEVERE, e.getMessage());
	    throw new ActionFailedException(e);
	} finally {
	    setPropertyChangeIgnore(false);
	}
	changeableAggregator.save();
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {
	setPropertyChangeSource(getPanelDescriptor());
	super.start(navigator, parameters);
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {

	    defaultTab = new FirewallDefaultTab(getPanelDescriptor());
	    overrideTab = new FirewallOverrideTab(getPanelDescriptor());
	    openPortsTab = new FirewallOpenPortsTab(getPanelDescriptor());

	    addChildren(defaultTab);
	    addChildren(openPortsTab);
	    addChildren(overrideTab);
	}
    }

    //
    // GlobalControl methods
    //

    public ChangeableAggregator getChangeableAggregator() {
	return changeableAggregator;
    }
}
