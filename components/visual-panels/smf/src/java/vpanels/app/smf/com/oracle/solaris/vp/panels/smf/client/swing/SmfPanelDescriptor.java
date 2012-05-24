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

import java.io.IOException;
import javax.management.InstanceNotFoundException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.PanelFrameControl;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * Panel descriptor for the Swing SMF panel
 */
public class SmfPanelDescriptor
    extends AbstractPanelDescriptor<SmfManagedObject>
    implements SwingPanelDescriptor<SmfManagedObject> {

    //
    // Instance data
    //

    private DefaultControl control;
    private RepoManagedObject repo;
    private MainControl svccontrol;

    //
    // Constructors
    //

    public SmfPanelDescriptor(String id, ClientContext context)
	throws InstanceNotFoundException, IOException, TrackerException {

	super(id, context);
	setName(Finder.getString("smf.panel.name"));

	repo = new RepoManagedObject(id, context);

	svccontrol = new MainControl(this);
	svccontrol.getStats().addPropertyChangeListener(
	    new PropertyChangeForwarder(this));

	final Control qControl = new QuitControl<SmfPanelDescriptor>(this);

	control = new PanelFrameControl<SmfPanelDescriptor>(this) {
	    @Override
	    public Navigable[] getForwardingPath(boolean childStopped) {
                // Each top-level Control in this panel requires parameters --
                // if this is our final destination, we should just quit
		return new Navigable[] {
		    qControl
		};
	    }
	};
	control.addChildren(svccontrol, new FmriControl(this), qControl);
    }

    //
    // ManagedObject methods
    //

    /**
     * Stops monitoring the connection to the remote host.
     */
    @Override
    public void dispose() {
	repo.dispose();
	super.dispose();
    }

    @Override
    public ManagedObjectStatus getStatus() {
	return svccontrol.getStats().getStatus();
    }

    @Override
    public String getStatusText() {
	return svccontrol.getStats().getStatusText();
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public Control getControl() {
	return control;
    }

    @Override
    public boolean getHasFullPrivileges() {
	return (getClientContext().getConnectionInfo().getUser().
	    equals("root"));
    }

    //
    // SmfPanelDescriptor methods
    //

    public RepoManagedObject getRepo() {
	return repo;
    }
}
