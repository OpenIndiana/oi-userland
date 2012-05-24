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

import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.TabbedControl;
import com.oracle.solaris.vp.panel.swing.smf.*;

public class ServiceTabbedControl extends TabbedControl<SmfPanelDescriptor> {
    //
    // Static data
    //

    public static final String ID = "service";
    public static final Navigable NAVIGABLE = new SimpleNavigable(ID, null);

    //
    // Instance data
    //

    private MainControl parent;

    //
    // Constructors
    //

    public ServiceTabbedControl(SmfPanelDescriptor descriptor,
	MainControl parent) {

	super(ID, null, descriptor);
	this.parent = parent;
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    SmfPanelDescriptor descriptor = getPanelDescriptor();

            addChildren(new GeneralControl(descriptor,
		new HasServiceTracker() {
		    @Override
		    public ServiceTracker getServiceTracker() {
			return parent.getSmfManagedObject().getServiceTracker();
		    }
		}));

            addChildren(new SmfPropertiesControl<SmfPanelDescriptor>(
		descriptor, parent));

	    addChildren(new SmfDependenciesControl<SmfPanelDescriptor,
		ServiceManagedObject>(
		descriptor, parent, descriptor.getRepo()));
	}
    }

    //
    // TabbedControl methods
    //

    @Override
    protected boolean isInsettable(Control child) {
	if (child instanceof SmfDependenciesControl ||
	    child instanceof SmfPropertiesControl) {
	    return false;
	}
	return true;
    }
}
