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

package com.oracle.solaris.vp.panel.swing.smf;

import java.awt.Component;
import java.io.IOException;
import java.util.logging.*;
import javax.management.InstanceNotFoundException;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class SmfLogControl<P extends PanelDescriptor>
    extends SettingsControl<P, SmfLogPanel> {

    //
    // Static data
    //

    private static final String ID = "log";
    private static final String NAME = Finder.getString("service.log.name");

    //
    // Instance data
    //

    private HasServiceTracker tracker;

    //
    // Constructors
    //

    public SmfLogControl(P descriptor, HasServiceTracker tracker) {
	super(ID, NAME, descriptor);
	this.tracker = tracker;
    }

    //
    // SwingControl methods
    //

    @Override
    protected SmfLogPanel createComponent() {
	return new SmfLogPanel();
    }

    @Override
    protected void deinitComponent() {
        doInit(null);
    }

    @Override
    protected void initComponent() {
        doInit(tracker.getServiceTracker());
    }

    //
    // Private methods
    //

    private void doInit(ServiceTracker tracker) {
	Exception t = null;

	try {
	    getComponent().init(tracker);
	} catch (InstanceNotFoundException e) {
	    t = e;
	} catch (IOException e) {
	    t = e;
	}

	if (t != null) {
	    Logger.getLogger(getClass().getPackage().getName()).log(
		Level.SEVERE, "error instantiating log component", t);
	}
    }
}
