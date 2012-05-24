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

package com.oracle.solaris.vp.panels.sysmon.client.swing;

import java.io.IOException;
import java.util.List;
import javax.management.InstanceNotFoundException;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.control.Control;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasIcons;

public class SysMonPanelDescriptor
    extends AbstractPanelDescriptor<MonitoredResource>
    implements SwingPanelDescriptor<MonitoredResource>, HasIcons {

    //
    // Static data
    //

    protected static final List<ImageIcon> icons = Finder.getIcons(
	"images/sysmon-16.png",
	"images/sysmon-22.png",
	"images/sysmon-24.png",
	"images/sysmon-32.png");

    //
    // Instance data
    //

    private boolean connHealthy = true;

    private ConnectionListener connListener =
	new ConnectionListener() {
	    @Override
	    public void connectionChanged(ConnectionEvent event) {
                setConnHealthy(true);
	    }

	    @Override
	    public void connectionFailed(ConnectionEvent event) {
                setConnHealthy(false);
	    }
	};

    private Control control;

    //
    // Constructors
    //

    public SysMonPanelDescriptor(String id, ClientContext context)
	throws InstanceNotFoundException, IOException, TrackerException {

	super(id, context);

	setName(Finder.getString("panel.name"));

	addChildren(new SmfMonitoredResource(context));

	control = new SysMonTrayControl(getId(), getName(), this);

	setStatus();
	setStatusText();

	context.addConnectionListener(connListener);
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return icons;
    }

    //
    // AbstractManagedObject methods
    //

    @Override
    protected ManagedObjectStatus getCalculatedStatus() {
	return (!connHealthy)
            ? ManagedObjectStatus.ERROR
            : super.getCalculatedStatus();
    }

    @Override
    protected String getCalculatedStatusText() {
	if (!connHealthy) {
            return Finder.getString("status.offline",
		getClientContext().getConnectionInfo().getHost());
        }

	int count = 0;
	ManagedObjectStatus status = ManagedObjectStatus.HEALTHY;

	for (ManagedObject child : children) {
	    ManagedObjectStatus cStatus = child.getStatus();
	    int compare = status.compareTo(cStatus);
	    if (compare < 0) {
		status = cStatus;
		count = 1;
	    } else if (compare == 0) {
		count++;
	    }
	}

        return Finder.getString(
	    "status." + status.toString().toLowerCase() + "." + count,
	    children.size(), count);
    }

    //
    // SysMonPanelDescriptor methods
    //

    public Control getControl() {
	return control;
    }

    /**
     * Set connection health.
     *
     * @param connHealthy A value of false indicates a broken connection.
     */
    private void setConnHealthy(boolean connHealthy) {
        this.connHealthy = connHealthy;
	setStatus();
	setStatusText();
    }
}
