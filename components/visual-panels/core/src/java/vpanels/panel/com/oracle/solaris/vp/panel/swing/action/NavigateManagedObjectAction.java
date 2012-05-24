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

package com.oracle.solaris.vp.panel.swing.action;

import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;

@SuppressWarnings({"serial"})
public class NavigateManagedObjectAction<C extends ManagedObject>
    extends EditManagedObjectAction<C, Object, Object> {

    //
    // Private data
    //

    private String id_;
    private String param_;
    private Control control_;

    //
    // Constructors
    //

    public NavigateManagedObjectAction(SwingControl control, String id,
	String param) {

	super(TEXT, ICONS, control);
	id_ = id;
	param_ = param;
	control_ = control;
    }

    //
    // StructuredAction methods
    //

    @Override
    public Object invoke(Object unused) throws ActionAbortedException,
	ActionFailedException {

	// Assume valid selection
	C obj = getPresetInput().get(0);

	Navigable navigable = new SimpleNavigable(id_, null, param_,
	    obj.getId());

	control_.getNavigator().goToAsync(false, control_, navigable);

	return null;
    }
}
