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

package com.oracle.solaris.vp.panels.svcs.client.swing;

import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.InstanceManagedObject;
import com.oracle.solaris.vp.util.misc.event.*;
import com.oracle.solaris.vp.util.misc.predicate.Predicate;

public class InstanceFilter extends AbstractManagedObject<
    FilterManagedObject<InstanceManagedObject>>
{
    private FilterManagedObject<InstanceManagedObject> fmo_;
    private IntervalListener listener_ = new IntervalListener() {
	public void intervalAdded(IntervalEvent event) {
	    updateStatusText();
	}

	public void intervalRemoved(IntervalEvent event) {
	    updateStatusText();
	}
    };

    InstanceFilter(String id, ManagedObject<InstanceManagedObject> instances,
	String name, Predicate<? super InstanceManagedObject> pred)
    {
	super(id);
	setName(name);
	fmo_ = new FilterManagedObject<InstanceManagedObject>(instances, pred);
	fmo_.addIntervalListener(listener_);
	updateStatusText();
    }

    public ManagedObject<InstanceManagedObject> getManagedObject()
    {
	return (fmo_);
    }

    private void updateStatusText()
    {
	int size = fmo_.getChildren().size();
	setStatusText(size != 1 ? String.format("%d instances", size) :
	    String.format("%d instance", size));
    }
}
