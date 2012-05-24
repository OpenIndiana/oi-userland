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
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.action.CloneManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings({"serial"})
public class CloneVirtualHostAction
    extends CloneManagedObjectAction<ManagedObject, String, VirtualHost> {

    //
    // Instance data
    //

    private SwingControl<ApachePanelDescriptor, ?> control;

    //
    // Constructors
    //

    public CloneVirtualHostAction(
	SwingControl<ApachePanelDescriptor, ?> control) {

	super(TEXT, ICONS, control);
	this.control = control;
	setLoops(true);
    }

    //
    // StructuredAction methods
    //

    @Override
    public String getRuntimeInput(List<ManagedObject> selection, String domain)
	throws ActionAbortedException {

	Object response = JOptionPane.showInputDialog(
	    getHasComponent().getComponent(),
	    Finder.getString("vhosts.action.clone.message"),
	    Finder.getString("vhosts.action.clone.title"),
	    JOptionPane.PLAIN_MESSAGE, null, null, domain);

	if (response == null) {
	    throw new ActionAbortedException();
	}

	return response.toString();
    }

    /**
     * Enables this {@code Action} iff a single {@link VirtualHost} is selected.
     */
    @Override
    public void refresh() {
	List<ManagedObject> selection = getPresetInput();
	boolean enabled = selection.size() == 1 &&
	    selection.get(0) instanceof VirtualHost;

	setEnabled(enabled);
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public VirtualHost workBusy(List<ManagedObject> selection,
	String domain) throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	VirtualHost.validateDomainName(domain, null);

	// Assume valid selection
	VirtualHost orig = (VirtualHost)selection.get(0);

	VirtualHost clone = orig.clone();
	clone.getEnabledProperty().setFirstValue(false);
	clone.getDomainProperty().setFirstValue(domain);

	control.getPanelDescriptor().addChildren(clone);

	// Navigate to the new virtual host
	Navigable navigable = new SimpleNavigable(
	    VirtualHostControl.ID, null,
	    VirtualHostControl.PARAM_ID, clone.getId());

	control.getNavigator().goToAsync(false, control, navigable);

	return clone;
    }
}
