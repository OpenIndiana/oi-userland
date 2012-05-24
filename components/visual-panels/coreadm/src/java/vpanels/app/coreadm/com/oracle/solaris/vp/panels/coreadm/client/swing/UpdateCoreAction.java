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

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.util.List;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.swing.action.UpdateManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;

public class UpdateCoreAction
    extends UpdateManagedObjectAction<CoreManagedObject, Object, Object> {

    //
    // Instance data
    //

    private SwingControl<CoreAdmPanelDescriptor, ?> control;

    //
    // Constructors
    //

    public UpdateCoreAction(SwingControl<CoreAdmPanelDescriptor, ?> control) {
	super(TEXT, ICONS, control);

	this.control = control;
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public Object workBusy(List<CoreManagedObject> selection,
	Object input) throws ActionAbortedException,
	ActionFailedException, ActionUnauthorizedException {

	control.getPanelDescriptor().updateCoreConfig();

	return null;
    }
}
