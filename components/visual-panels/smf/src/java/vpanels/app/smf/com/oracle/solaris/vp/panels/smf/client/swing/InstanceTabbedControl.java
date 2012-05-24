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

package com.oracle.solaris.vp.panels.smf.client.swing;

import java.util.Map;
import com.oracle.solaris.scf.common.FMRI;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.TabbedControl;
import com.oracle.solaris.vp.panel.swing.smf.*;

public class InstanceTabbedControl extends TabbedControl<SmfPanelDescriptor>
    implements HasSmfManagedObject<InstanceManagedObject>, HasServiceTracker {

    //
    // Static data
    //

    public static final String ID = "instance";
    public static final String PARAM_INSTANCE = "instance";

    //
    // Instance data
    //

    private MainControl parent;
    private InstanceManagedObject instance;

    //
    // Constructors
    //

    public InstanceTabbedControl(SmfPanelDescriptor descriptor,
	MainControl parent) {

	super(ID, null, descriptor);
	this.parent = parent;
    }

    //
    // HasServiceTracker methods
    //

    @Override
    public ServiceTracker getServiceTracker() {
	return getSmfManagedObject().getServiceTracker();
    }

    //
    // HasSmfManagedObject methods
    //

    @Override
    public InstanceManagedObject getSmfManagedObject() {
	return instance;
    }

    //
    // Control methods
    //

    @Override
    public boolean isBrowsable() {
	// This Control requires init parameters
	return false;
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	String param = getParameter(parameters, PARAM_INSTANCE);
	FMRI fmri = parent.getSmfManagedObject().getSMFFmri().toInstanceFMRI(
	    param);

	SmfManagedObject smo = getPanelDescriptor().getRepo().getSMO(
	    fmri.toString());
	if (smo == null || !(smo instanceof InstanceManagedObject)) {
	    throw new InvalidParameterException(getId(), PARAM_INSTANCE,
		param);
	}

	setInstance((InstanceManagedObject)smo);

	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	// Remove reference so it can be garbage collected if deleted
	setInstance(null);
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    SmfPanelDescriptor descriptor = getPanelDescriptor();

	    addChildren(new GeneralControl(descriptor, this));
	    addChildren(new SmfPropertiesControl<SmfPanelDescriptor>(
		descriptor, this));
	    addChildren(new SmfDependenciesControl<SmfPanelDescriptor,
		InstanceManagedObject>(
		descriptor, this, descriptor.getRepo()));
	    addChildren(new SmfLogControl<SmfPanelDescriptor>(
		descriptor, this));
	}
    }

    //
    // TabbedControl methods
    //

    @Override
    protected boolean isInsettable(Control child) {
	if (child instanceof SmfDependenciesControl ||
	    child instanceof SmfPropertiesControl ||
	    child instanceof SmfLogControl) {
	    return false;
	}
	return true;
    }

    //
    // Private methods
    //

    private void setInstance(InstanceManagedObject instance) {
	this.instance = instance;
	setName(instance == null ? null : instance.getSMFFmri().getInstance());
    }
}
