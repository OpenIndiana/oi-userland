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
import java.util.Date;
import com.oracle.solaris.scf.common.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObjectStatus;
import com.oracle.solaris.vp.util.misc.Enableable;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class InstanceManagedObject extends SmfManagedObject
    implements Enableable {

    //
    // Static data
    //

    /* public static final String PROPERTY_ENABLED = "enabled"; */
    public static final String PROPERTY_STATE = "state";

    //
    // Instance data
    //

    private SmfState state;
    private Date stime;
    private final FMRI svcFmri;

    //
    // Constructors
    //

    InstanceManagedObject(ClientContext context, Instance inst)
    	throws TrackerException {

	super(context, inst.getFmri(), inst.getObjectName());
	svcFmri = getSMFFmri().toServiceFMRI();
	state = inst.getState();
	stime = inst.getSTime();
    }

    //
    // ManagedObject methods
    //

    @Override
    public ManagedObjectStatus getStatus() {
	return ServiceUtil.getPanelStatus(state);
    }

    @Override
    public String getStatusText() {
	return ServiceUtil.getStateSynopsis(state, null);
    }

    //
    // DepManagedObject methods
    //

    @Override
    public String getDepType() {
	return Finder.getString("smf.depend.type.instance");
    }

    @Override
    public String getDepState() {
	return ServiceUtil.getStateString(getSMFState());
    }

    //
    // NotificationListener methods
    //

    /**
     * Handles changes to this {@code InstanceManagedObject}'s service.
     * This implementation listens only for {@code StateChangeNotification}s and
     * fires a {@code PropertyChangeEvent} to registered {@code
     * PropertyChangeEvent}s.
     */
    public void handleStateChange(StateChange sc) {
	SmfState oldState = state;
	state = sc.getState();
	stime = sc.getStateTime();
	firePropertyChange(new PropertyChangeEvent(this, PROPERTY_STATE,
	    oldState, state));
    }

    //
    // InstanceManagedObject methods
    //

    public FMRI getServiceFmri() {
	return svcFmri;
    }

    public SmfState getSMFState() {
	return state;
    }

    public Date getLastChange() {
	return stime;
    }

    public boolean isEnabled() {
	/* More or less true */
	return state != state.DISABLED;
    }

    public void setEnabled(boolean enable) throws ScfException {
	ServiceMXBean bean = getService();
	if (bean != null) {
	    bean.setPersistentlyEnabled(enable);
	}
    }
}
