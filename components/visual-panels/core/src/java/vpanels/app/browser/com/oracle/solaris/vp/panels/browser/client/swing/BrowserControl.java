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

package com.oracle.solaris.vp.panels.browser.client.swing;

import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.action.StructuredAction;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.action.LaunchManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.*;

public class BrowserControl extends ListSelectorControl<BrowserPanelDescriptor,
    ListSelectorPanel, PanelManagedObject>
{
    //
    // Static data
    //

    public static final String ID = "main";

    //
    // Instance data
    //

    private DefaultListModel lm_ = new DefaultListModel();

    private StructuredAction<List<PanelManagedObject>, ?, ?> launchAction_ =
	new LaunchManagedObjectAction<PanelManagedObject>(this) {

	@Override
	public Navigable[] getRuntimeInput(List<PanelManagedObject> selection,
	    Navigable[] path) {

	    // Assume valid selection
	    PanelManagedObject obj = selection.get(0);

	    return new Navigable[] {
		getNavigator().getPath().get(0),
		new SimpleNavigable(obj.getCustom().getName(), null)
	    };
	}
    };

    //
    // Constructors
    //

    public BrowserControl(BrowserPanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	return new Navigable[] {
	    new SimpleNavigable(PanelControl.ID, null,
		PanelControl.PARAM_PANEL, "browser")
	};
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    PanelControl ctl = new PanelControl(getPanelDescriptor());
	    addChildren(ctl);
	    addToLayout(ctl);
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(ListSelectorPanel comp) {
	super.configComponent(comp);
	addDefaultCloseAction(true);
	getComponent().getSelectionComponent().setSelectionMode(
	    ListSelectionModel.SINGLE_SELECTION);
    }

    @Override
    protected ListSelectorPanel createComponent() {
	ListSelectorPanel panel = new ListSelectorPanel();

	JList list = panel.getSelectionComponent();
	ManagedObjectCellRenderer<PanelManagedObject> renderer =
	    new ManagedObjectCellRenderer<PanelManagedObject>();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);

	addAction(panel, launchAction_, true, true);

	return panel;
    }

    //
    // SelectorControl methods
    //

    @Override
    protected Navigable[] getPathForSelection(
	List<PanelManagedObject> selection) {

	if (selection.size() != 1) {
	    return null;
	}

	PanelManagedObject panel = selection.get(0);

	return new Navigable[] {
	    new SimpleNavigable(PanelControl.ID, panel.getName(),
		PanelControl.PARAM_PANEL, panel.getId())
	};
    }

    //
    // ListSelectorControl methods
    //

    @Override
    protected int getListIndexOf(Control child) {
	PanelManagedObject panel = ((PanelControl)child).getManagedObject();
	return (lm_.indexOf(panel));
    }

    @Override
    protected ListModel getListModel() {
	if (lm_.isEmpty()) {
	    for (PanelManagedObject p : getPanelDescriptor().getChildren())
		lm_.addElement(p);
	}
	return (lm_);
    }

    //
    // BrowserControl methods
    //

    void newConnection() {
	lm_.clear();
	getListModel();
	getNavigator().goToAsync(false, this);
    }
}
