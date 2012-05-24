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

package com.oracle.solaris.vp.panel.common.smf;

import java.beans.PropertyChangeEvent;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.util.misc.event.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class InstanceStatistics
    extends ManagedObjectMonitor<InstanceManagedObject>
    implements PropertyChangeEventSource
{
    private int onlineCount_;
    private int maintCount_;
    private int degradeCount_;
    private int totalCount_;

    public InstanceStatistics(ManagedObject<InstanceManagedObject> instances)
    {
	super(instances);
	updateStats();
    }

    public InstanceStatistics()
    {
	this(new EmptyManagedObject<InstanceManagedObject>());
    }

    @Override
    public void intervalAdded(IntervalEvent event) {
	super.intervalAdded(event);
	updateStats();
    }

    @Override
    public void intervalRemoved(IntervalEvent event) {
	super.intervalRemoved(event);
	updateStats();
    }

    @Override
    protected void managedObjectPropertyChange(InstanceManagedObject obj,
	PropertyChangeEvent evt) {

	updateStats();
    }

    private void resetStats()
    {
	totalCount_ = 0;
	onlineCount_ = 0;
	maintCount_ = 0;
	degradeCount_ = 0;
    }

    private void updateStats()
    {
	synchronized (listenees_) {
	    resetStats();

	    for (SmfManagedObject smo : listenees_)
		updateOnAdd(smo);
	    pListeners_.propertyChange(new PropertyChangeEvent(this,
		ManagedObject.PROPERTY_STATUS_TEXT, null, null));
	    pListeners_.propertyChange(new PropertyChangeEvent(this,
		ManagedObject.PROPERTY_STATUS, null, null));
	}
    }

    private void updateOnAdd(SmfManagedObject smo)
    {
	if (!(smo instanceof InstanceManagedObject))
	    return;

	totalCount_++;
	switch (((InstanceManagedObject)smo).getSMFState()) {
	case ONLINE:
	    onlineCount_++;
	    break;
	case MAINT:
	    maintCount_++;
	    break;
	case DEGRADED:
	    degradeCount_++;
	}
    }

    private void updateOnRemove(SmfManagedObject smo)
    {
	if (!(smo instanceof InstanceManagedObject))
	    return;

	totalCount_--;
	switch (((InstanceManagedObject)smo).getSMFState()) {
	case ONLINE:
	    onlineCount_--;
	    break;
	case MAINT:
	    maintCount_--;
	    break;
	case DEGRADED:
	    degradeCount_--;
	}
    }

    public String getStatusText()
    {
	String state;
	int count;

	if (maintCount_ > 0) {
	    state = "maintenance";
	    count = maintCount_;
	} else if (degradeCount_ > 0) {
	    state = "degraded";
	    count = degradeCount_;
	} else {
	    state = "healthy";
	    count = onlineCount_;
	}

	return Finder.getString("smf.status." + state + "." + count, count);
    }

    public ManagedObjectStatus getStatus()
    {
	if (maintCount_ > 0)
	    return ManagedObjectStatus.ERROR;
	else if (degradeCount_ > 0)
	    return ManagedObjectStatus.WARNING;
	else
	    return ManagedObjectStatus.HEALTHY;
    }
}
