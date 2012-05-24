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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.util.List;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.action.EnableManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;

@SuppressWarnings({"serial"})
public class EnableVirtualHostAction
    extends EnableManagedObjectAction<ManagedObject, Object, Object> {

    //
    // Instance data
    //

    private SwingControl control;

    //
    // Constructors
    //

    public EnableVirtualHostAction(SwingControl control, boolean enable) {
	super(enable ? TEXT_ENABLE : TEXT_DISABLE, null, control, enable);
	this.control = control;
    }

    //
    // StructuredAction methods
    //

    /**
     * Enables this {@code Action} iff the selection contains only {@link
     * VirtualHost}s, and the enabled state of at least one would be changed by
     * this action.
     */
    @Override
    public void refresh() {
	boolean enabled = false;
	List<ManagedObject> selection = getPresetInput();

	for (ManagedObject o : selection) {
	    if (!(o instanceof VirtualHost)) {
		enabled = false;
		break;
	    }

	    if (!enabled) {
		VirtualHost vHost = (VirtualHost)o;
		if (vHost.isEnabled() != getEnable()) {
		    enabled = true;
		}
	    }
	}

	setEnabled(enabled);
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public Object workBusy(List<ManagedObject> selection, Object input)
	throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	boolean enable = getEnable();

	for (ManagedObject object : selection) {
	    VirtualHost vHost = (VirtualHost)object;
	    vHost.getEnabledProperty().setFirstValue(enable);
	}

	return null;
    }
}
