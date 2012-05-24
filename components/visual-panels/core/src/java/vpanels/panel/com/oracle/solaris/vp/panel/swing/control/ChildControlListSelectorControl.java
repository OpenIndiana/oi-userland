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

package com.oracle.solaris.vp.panel.swing.control;

import java.beans.*;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.swing.view.ListSelectorPanel;

@SuppressWarnings({"serial"})
public class ChildControlListSelectorControl<P extends PanelDescriptor,
    C extends ListSelectorPanel, O extends ControlManagedObject>
    extends ListSelectorControl<P, C, O> {

    //
    // Inner classes
    //

    private static class ManagedObjectListModel extends DefaultListModel
	implements PropertyChangeListener {

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
	    int index = indexOf(evt.getSource());
	    fireContentsChanged(this, index, index);
	}
    }

    //
    // Instance data
    //

    /*
     * This list should be kept consistent with the parent's children list.
     */
    protected List<O> objects_ = new ArrayList<O>();

    private ListModel model;

    //
    // Constructors
    //

    public ChildControlListSelectorControl(String id, String name, P descriptor)
    {
	super(id, name, descriptor);
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(C comp) {
	super.configComponent(comp);

	// List of Controls is not likely to benefit from multiple selection
	getComponent().getSelectionComponent().setSelectionMode(
	    ListSelectionModel.SINGLE_SELECTION);
    }

    //
    // ListSelectorControl methods
    //

    @Override
    protected int getListIndexOf(Control child) {
	return children.indexOf(child);
    }

    @Override
    protected ListModel getListModel() {
	if (model == null) {
	    ensureChildrenCreated();
	    ManagedObjectListModel dModel = new ManagedObjectListModel();
	    for (O child : objects_) {
		dModel.addElement(child);
		child.addPropertyChangeListener(dModel);
	    }
	    model = dModel;
	}

	return model;
    }

    @Override
    protected Navigable[] getPathForSelection(List<O> selection) {
	if (selection.size() != 1) {
	    return null;
	}

	Control selected = selection.get(0).getControl();

	return new Navigable[] {
	    new SimpleNavigable(selected.getId(), selected.getName())
	};
    }

    //
    // ChildControlListSelectorControl methods
    //

    public void addChild(O child) {
	objects_.add(child);
	super.addChildren(child.getControl());
	addToLayout(child.getControl());
    }
}
