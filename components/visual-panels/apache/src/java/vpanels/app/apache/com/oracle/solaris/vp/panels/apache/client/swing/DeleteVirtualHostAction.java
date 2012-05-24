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

import java.awt.Component;
import java.util.List;
import javax.swing.JOptionPane;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.Control;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.action.DeleteManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.GUIUtil;

@SuppressWarnings({"serial"})
public class DeleteVirtualHostAction
    extends DeleteManagedObjectAction<ManagedObject, Object, VirtualHost[]> {

    //
    // Static data
    //

    private static final String TEXT = Finder.getString(
	"vhosts.action.delete.button");

    //
    // Instance data
    //

    private SwingControl control;

    //
    // Constructors
    //

    public DeleteVirtualHostAction(SwingControl control) {
	super(TEXT, null, control);
	this.control = control;
    }

    //
    // StructuredAction methods
    //

    @Override
    public Object getRuntimeInput(List<ManagedObject> selection, Object input)
	throws ActionAbortedException {

	int count = selection.size();
	if (count == 0) {
	    throw new ActionAbortedException();
	}

	String message = Finder.getString(
	    "vhosts.action.delete.confirm." + count,
	    selection.get(0).getName(), count);

	int response = GUIUtil.showConfirmation(
	    getHasComponent().getComponent(), null, message,
	    JOptionPane.YES_NO_OPTION);

	if (response != JOptionPane.YES_OPTION) {
	    throw new ActionAbortedException();
	}

	return null;
    }

    /**
     * Enables this {@code Action} iff the selection is not empty and is all
     * {@link VirtualHost}s.
     */
    @Override
    public void refresh() {
	boolean enabled = getPresetInput().size() != 0;

	if (enabled) {
	    List<ManagedObject> selection = getPresetInput();
	    for (ManagedObject o : selection) {
		if (!(o instanceof VirtualHost)) {
		    enabled = false;
		    break;
		}
	    }
	}

	setEnabled(enabled);
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public VirtualHost[] workBusy(List<ManagedObject> selection,
	Object input) throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	// Selection has been verified as VirtualHosts
	VirtualHost[] vHosts = selection.toArray(
	    new VirtualHost[selection.size()]);

	if (!selection.isEmpty()) {
	    ApachePanelDescriptor descriptor = vHosts[0].getPanelDescriptor();
	    descriptor.scheduleRemove(vHosts);

	    // If the running Control is a VirtualHostControl for a just-deleted
	    // VirtualHost, reset the Control and navigate back to its parent
	    Control child = control.getRunningChild();
	    if (child instanceof VirtualHostControl) {
		VirtualHost vHost =
		    ((VirtualHostControl)child).getVirtualHost();

		if (selection.contains(vHost)) {
		    child.doCancel();
		}
	    }
	}

	return vHosts;
    }
}
