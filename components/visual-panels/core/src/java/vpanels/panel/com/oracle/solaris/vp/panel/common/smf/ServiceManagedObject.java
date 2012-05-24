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

import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObjectStatus;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class ServiceManagedObject extends SmfManagedObject {
    //
    // Instance data
    //

    private Service svc;
    private RepoManagedObject repo;

    //
    // Constructors
    //

    ServiceManagedObject(RepoManagedObject repo, ClientContext context,
	Service svc) throws TrackerException {

	super(context, svc.getFmri(), svc.getObjectName());
	this.repo = repo;
	this.svc = svc;
    }

    //
    // ManagedObject methods
    //

    @Override
    public ManagedObjectStatus getStatus() {
	return ManagedObjectStatus.HEALTHY;
    }

    //
    // DepManagedObject methods
    //

    @Override
    public String getDepType() {
	return Finder.getString("smf.depend.type.service");
    }

    @Override
    public String getDepState() {
	// Could be out of date
	for (String inst : svc.getInstances()) {
	    SmfManagedObject i = repo.getSMO(inst);
	    if (i == null || !(i instanceof InstanceManagedObject)) {
		continue;
	    }
	    if (((InstanceManagedObject)i).getSMFState() == SmfState.ONLINE) {
		return ServiceUtil.getStateString(SmfState.ONLINE);
	    }
	}

	return ServiceUtil.getStateString(SmfState.OFFLINE);
    }

    //
    // ServiceManagedObject methods
    //

    public SmfState getSMFState() {
	return SmfState.NONE;
    }
}
