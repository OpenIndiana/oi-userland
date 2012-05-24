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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.Component;
import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.ListSelectorPanel;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.SimpleCellRenderer;

public class MainControl extends ListSelectorControl<FirewallPanelDescriptor,
    ListSelectorPanel, ManagedObject> {

    //
    // Static data
    //

    public static final String ID = "main";

    //
    // Instance data
    //

    private ListModel model;

    //
    // Constructors
    //

    public MainControl(FirewallPanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public void childStarted(Control child) {
	super.childStarted(child);

	if (child instanceof ServiceEditControl) {
	    getComponent().getChangeableAggregator().addChangeables(
	    ((SettingsControl<?, ?>)child).getComponent().
	    getChangeableAggregator());
	} else {
	    getComponent().getChangeableAggregator().addChangeables(
	    ((GlobalControl)child).getChangeableAggregator());
	}
    }

    @Override
    public void childStopped(Control child) {
	super.childStopped(child);

	if (child instanceof ServiceEditControl) {
	    getComponent().getChangeableAggregator().removeChangeable(
	    ((SettingsControl<?, ?>)child).getComponent().
	    getChangeableAggregator());
	} else {
	    getComponent().getChangeableAggregator().removeChangeable(
	    ((GlobalControl)child).getChangeableAggregator());
	}
    }

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	return new Navigable[] {
	    new SimpleNavigable(GlobalControl.ID, null)
	};
    }

    @Override
    public String getHelpMapID() {
	return "firewall-panel";
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    FirewallPanelDescriptor descriptor = getPanelDescriptor();
	    SwingControl[] controls = {
		new GlobalControl(descriptor),
		new ServiceEditControl(descriptor)
	    };

	    addChildren(controls);

	    // Add the Components of these children to the UI now, so that the
	    // UI will be sized to fit the largest Component
	    addToLayout(controls);
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(ListSelectorPanel panel) {
	super.configComponent(panel);
	addDefaultApplyAction();
	addDefaultCancelAction(true);
	addDefaultOkayAction(true);
	addDefaultHelpAction();
    }

    @Override
    protected ListSelectorPanel createComponent() {
	ListSelectorPanel panel = new ListSelectorPanel();
	panel.setSelectionTitle(Finder.getString("policy.list.title"));

	JList list = panel.getSelectionComponent();
	SimpleCellRenderer renderer = new MainListCellRenderer();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);

	addAction(panel, new AddServiceAction(this), true, true);
	addAction(panel, new RemoveServiceAction(this), true, true);

	return panel;
    }

    //
    // ListSelectorControl methods
    //

    @Override
    protected int getListIndexOf(Control child) {
	if (child instanceof GlobalControl)
	    return 0;

	FirewallPanelDescriptor descriptor = getPanelDescriptor();
	ServiceManagedObject service =
	    ((ServiceEditControl) child).getManagedService();

	int cIndex = descriptor.indexOf(service);
	assert cIndex >= 0;

	// Add offset for global policy at item 0
	cIndex++;

	ListModel model = getComponent().getSelectionComponent().getModel();
	ServiceManagedObject modelService =
	    (ServiceManagedObject) model.getElementAt(cIndex);
	assert (modelService.getId().equals(service.getId()));

	return cIndex;
    }

    @Override
    protected ListModel getListModel() {
	if (model == null) {
	    model = new MainListModel(getPanelDescriptor());
	}

	return model;
    }

    @Override
    protected Navigable[] getPathForSelection(List<ManagedObject> selection) {
	if (selection.size() != 1) {
	    return null;
	}

	ManagedObject selected = selection.get(0);
	Navigable navigable;

	if (selected instanceof FirewallPanelDescriptor) {
	    navigable = new SimpleNavigable(GlobalControl.ID,
		MainListCellRenderer.TEXT_GLOBAL);
	} else {
	    ServiceManagedObject sobj = (ServiceManagedObject)selected;

	    navigable = new SimpleNavigable(ServiceEditControl.ID,
		sobj.getName(), ServiceEditControl.PARAM_SVC, sobj.getId());
	}
	return new Navigable[] {navigable};
    }
}
