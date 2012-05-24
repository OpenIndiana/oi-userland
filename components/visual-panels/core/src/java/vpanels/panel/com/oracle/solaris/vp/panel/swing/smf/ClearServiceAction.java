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

package com.oracle.solaris.vp.panel.swing.smf;

import java.util.List;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.action.UpdateManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings("serial")
public class ClearServiceAction
    extends UpdateManagedObjectAction<SmfManagedObject, Object, Object> {

    protected static final String TEXT_CLEAR =
	Finder.getString("service.action.clear");

    //
    // Constructors
    //

    public ClearServiceAction(SwingControl control) {
	super(TEXT_CLEAR, ICONS, control);
    }

    //
    // StructuredAction methods
    //

    @Override
    public void refresh() {
	super.refresh();

	if (isEnabled()) {
	    // Verify each selected item is an InstanceManagedObject
	    for (SmfManagedObject o : getPresetInput()) {
		if (!(o instanceof InstanceManagedObject)) {
		    setEnabled(false);
		    break;
		}
	    }
	}
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public Object workBusy(List<SmfManagedObject> selection, Object input)
	throws ActionFailedException, ActionUnauthorizedException {

	for (SmfManagedObject object : selection) {
	    // Selection has been verified as InstanceManagedObjects
	    InstanceManagedObject inst = (InstanceManagedObject)object;
	    try {
		inst.getService().clear();
	    } catch (ScfException e) {
		SmfUtil.throwActionException(e);
	    } catch (SecurityException e) {
		throw new ActionUnauthorizedException(e);
	    }
	}

	return null;
    }
}
