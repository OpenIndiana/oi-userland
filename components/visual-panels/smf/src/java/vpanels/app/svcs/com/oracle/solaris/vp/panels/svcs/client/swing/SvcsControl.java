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

package com.oracle.solaris.vp.panels.svcs.client.swing;

import java.beans.*;
import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.*;

public class SvcsControl extends ListSelectorControl<SvcsPanelDescriptor,
    ListSelectorPanel, InstanceFilter>
{
    //
    // Static data
    //

    public static final String ID = "main";

    //
    // Instance data
    //

    private class ManagedObjectListModel extends DefaultListModel
	implements PropertyChangeListener
    {
	public void propertyChange(PropertyChangeEvent evt) {
	    int index = indexOf(evt.getSource());
	    fireContentsChanged(evt, index, index);
	}
    }

    private ManagedObjectListModel lm_ = new ManagedObjectListModel();

    //
    // Constructors
    //

    public SvcsControl(SvcsPanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "smf-overview";
    }

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	return new Navigable[] {
	    new SimpleNavigable(InstancesControl.ID, null,
		InstancesControl.PARAM_FILTER, "enabled")
	};
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    InstancesControl child = new InstancesControl(getPanelDescriptor());
	    addChildren(child);
	    addToLayout(child);
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(ListSelectorPanel comp) {
	super.configComponent(comp);

	addDefaultCloseAction(true);
	addDefaultHelpAction();

	getComponent().getSelectionComponent().setSelectionMode(
	    ListSelectionModel.SINGLE_SELECTION);
    }

    @Override
    protected ListSelectorPanel createComponent() {
	ListSelectorPanel panel = new ListSelectorPanel();

	JList list = panel.getSelectionComponent();
	ManagedObjectCellRenderer<InstanceFilter> renderer =
	    new ManagedObjectCellRenderer<InstanceFilter>();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);

	return panel;
    }

    //
    // SelectorControl methods
    //

    @Override
    protected Navigable[] getPathForSelection(List<InstanceFilter> selection) {
	if (selection.size() != 1) {
	    return null;
	}

	InstanceFilter filter = selection.get(0);

	return new Navigable[] {
	    new SimpleNavigable(InstancesControl.ID, filter.getName(),
		InstancesControl.PARAM_FILTER, filter.getId())
	};
    }

    @Override
    protected boolean isInsettable(Control child) {
	return false;
    }

    //
    // ListSelectorControl methods
    //

    @Override
    protected int getListIndexOf(Control child) {
	InstanceFilter filter = ((InstancesControl)child).getFilter();
	return (lm_.indexOf(filter));
    }

    @Override
    protected ListModel getListModel() {
	if (lm_.isEmpty()) {
	    for (InstanceFilter f : getPanelDescriptor().getFilters()) {
		lm_.addElement(f);
		f.addPropertyChangeListener(lm_);
	    }
	}
	return (lm_);
    }
}
