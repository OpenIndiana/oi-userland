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

package com.oracle.solaris.vp.panels.svcs.client.swing;

import java.util.*;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.smf.InstanceManagedObject;
import com.oracle.solaris.vp.panel.swing.action.PropertiesManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.smf.EnableServiceAction;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class InstancesControl
    extends SettingsControl<SvcsPanelDescriptor, InstancesPanel> {

    /*
     * Static data
     */

    public static final String ID = "instances";
    private static final String NAME = Finder.getString("smf.instances.title");

    /*
     * Instance data
     */
    private StructuredAction<List<InstanceManagedObject>, ?, ?> editAction_ =
	new PropertiesManagedObjectAction<InstanceManagedObject>(this) {

	@Override
	public Navigable[] getRuntimeInput(
	    List<InstanceManagedObject> selection, Navigable[] path) {

	    // Assume valid selection
	    InstanceManagedObject obj = selection.get(0);

	    return new Navigable[] {
		getNavigator().getPath().get(0),
		new SimpleNavigable("smf", null),
		new SimpleNavigable("svc", null, "service",
		    obj.getServiceFmri().getService()),
		new SimpleNavigable("instance", null, "instance",
		    obj.getSMFFmri().getInstance())
	    };
	}

	@Override
	public Object workBusy(List selection, Navigable[] path)
	    throws ActionAbortedException, ActionFailedException,
	    ActionUnauthorizedException {

	    if (path == null) {
		throw new ActionAbortedException();
	    }

	    try {
		// Create a new ClientContext and navigate to path
		getClientContext().login(null, true).getNavigator().
		    goToAsyncAndWait(true, null, path);

	    } catch (NavigationAbortedException e) {
		throw new ActionAbortedException(e);

	    } catch (NavigationException e) {
		throw new ActionFailedException(e);
	    }

	    return null;
	}
    };

    private EnableServiceAction enableAction_ =
	new EnableServiceAction(this, true);

    private EnableServiceAction disableAction_ =
	new EnableServiceAction(this, false);

    @SuppressWarnings({"unchecked"})
    protected StructuredAction<List<InstanceManagedObject>, ?, ?>[] actions_ =
	new StructuredAction[] {
	    enableAction_, disableAction_, editAction_
	};

    private InstanceFilter filter_ = null;

    public static final String PARAM_FILTER = "filter";

    /*
     * Constructors
     */

    public InstancesControl(SvcsPanelDescriptor descriptor)
    {
	super(ID, NAME, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "smf-instance";
    }

    @Override
    public boolean isBrowsable() {
	// This Control requires init parameters
	return false;
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	String param = getParameter(parameters, PARAM_FILTER);

	InstanceFilter filter = getPanelDescriptor().getFilter(param);
	if (filter == null)
	    throw new InvalidParameterException(getId(), PARAM_FILTER, param);

	filter_ = filter;
	setName(filter.getName());

	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	// Remove reference so it can be garbage collected if deleted
	filter_ = null;
    }

    /*
     * SwingControl methods
     */

    @Override
    protected InstancesPanel createComponent()
    {
	InstancesPanel panel =
	   new InstancesPanel(getPanelDescriptor(), actions_, editAction_);

	return panel;
    }

    @Override
    protected void initComponent()
    {
	try {
	    getComponent().getFmo().setManagedObject(
		filter_.getManagedObject());
	} catch (Throwable t) {
	    System.out.println("setManagedObject failed: " + t);
	    t.printStackTrace();
	}
    }

    @Override
    protected void deinitComponent()
    {
	// getComponent().getFmo().setPredicate(TruePredicate.getInstance());
    }

    public InstanceFilter getFilter()
    {
	return (filter_);
    }
}
