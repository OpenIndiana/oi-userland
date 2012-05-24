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

import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.util.List;
import javax.management.InstanceNotFoundException;
import javax.swing.Icon;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.util.misc.IconUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasIcons;

public class SmfMonitoredResource extends MonitoredResource implements HasIcons
{
    //
    // Static data
    //

    public static final String NAME = Finder.getString("monitored.smf.name");

    //
    // Instance data
    //

    private ClientContext context;
    private RepoManagedObject repo;
    private InstanceStatistics stats;
    private PropertyChangeListener propFwdListener =
	new PropertyChangeForwarder(this);

    //
    // Constructors
    //

    public SmfMonitoredResource(ClientContext context)
	throws InstanceNotFoundException, IOException, TrackerException {

	this.context = context;
	setName(NAME);

	repo = new RepoManagedObject("repo", context);
	stats = new InstanceStatistics(repo);
	stats.addPropertyChangeListener(propFwdListener);
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return IconUtil.getClosestIcon(getIcons(), height);
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return SmfManagedObject.icons;
    }

    //
    // ManagedObject methods
    //

    @Override
    public void dispose() {
	repo.dispose();
	super.dispose();
    }

    @Override
    public ManagedObjectStatus getStatus() {
	return stats.getStatus();
    }

    @Override
    public String getStatusText() {
	return stats.getStatusText();
    }

    //
    // MonitoredResource methods
    //

    @Override
    public Navigable[] getPanelAddress() {
	ManagedObjectStatus status = getStatus();
	if (status.equals(ManagedObjectStatus.HEALTHY)) {
		return new Navigable[] {
			context.getNavigator().getPath().get(0),
			new SimpleNavigable("svcs", null)
		    };
	} else {
		return new Navigable[] {
			context.getNavigator().getPath().get(0),
			new SimpleNavigable("svcs", null),
			new SimpleNavigable("main", null),
			new SimpleNavigable("instances", null,
				"filter", "unhealthy")
		    };
	}
    }
}
