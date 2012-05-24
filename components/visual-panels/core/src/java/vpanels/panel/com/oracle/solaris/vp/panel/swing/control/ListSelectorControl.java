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

import java.awt.EventQueue;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.swing.view.ListSelectorPanel;

@SuppressWarnings({"serial"})
public abstract class ListSelectorControl<P extends PanelDescriptor,
    C extends ListSelectorPanel, S> extends SelectorControl<P, C, S> {

    //
    // Inner classes
    //

    protected class NavListSelectionModel extends DefaultListSelectionModel {
	//
	// ListSelectionModel methods
	//

	@Override
	public void setSelectionInterval(int index0, int index1) {
	    super.setSelectionInterval(index0, index1);
	    if (!getValueIsAdjusting()) {
		goToSelected();
	    }
	}

	@Override
	public void setValueIsAdjusting(boolean adjusting) {
	    boolean oldVal = getValueIsAdjusting();
	    if (oldVal != adjusting) {
		super.setValueIsAdjusting(adjusting);
		if (!adjusting && oldVal) {
		    goToSelected();
		}
	    }
	}

	//
	// NavListSelectionModel methods
	//

	public void setSelectionIntervalDirectly(int index0, int index1) {
	    super.setSelectionInterval(index0, index1);
	}
    }

    //
    // Instance data
    //

    private NavListSelectionModel listSelModel;

    //
    // Constructors
    //

    public ListSelectorControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);

	// Re-retrieve/create the model now that Control is started
	getComponent().getSelectionComponent().setModel(getListModel());
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	// Reset model so that GC-able data within can be reclaimed
	getComponent().getSelectionComponent().setModel(new DefaultListModel());
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(C panel) {
	super.configComponent(panel);

	listSelModel = new NavListSelectionModel();
	panel.getSelectionComponent().setSelectionModel(listSelModel);

	listSelModel.addListSelectionListener(
	    new ListSelectionListener() {
		@Override
		public void valueChanged(ListSelectionEvent e) {
		    if (!e.getValueIsAdjusting()) {
			updateActions();
		    }
		}
	    });
    }

    //
    // SelectorControl methods
    //

    @Override
    protected List<S> getSelectableValues() {
	ListModel model = getListModel();
	int n = model.getSize();
	List<S> values = new ArrayList<S>(n);

	for (int i = 0; i < n; i++) {
	    @SuppressWarnings({"unchecked"})
	    S object = (S)model.getElementAt(i);
	    values.add(object);
	}

	return values;
    }

    @Override
    protected List<S> getSelectedValues() {
	Object[] selection =
	    getComponent().getSelectionComponent().getSelectedValues();

	List<S> objects = new ArrayList<S>(selection.length);

	for (Object item : selection) {
	    @SuppressWarnings({"unchecked"})
	    S object = (S)item;
	    objects.add(object);
	}

	return objects;
    }

    @Override
    protected void selectRunningChild() {
	Control child = getRunningChild();
	if (child != null) {
	    final int index = getListIndexOf(child);
	    if (index != -1) {
		EventQueue.invokeLater(
		    new Runnable() {
			@Override
			public void run() {
			    // Set list selection directly without going through
			    // the Navigator
			    listSelModel.setSelectionIntervalDirectly(index,
				index);
			}
		    });
	    }
	}
    }

    //
    // ListSelectorControl methods
    //

    /**
     * Gets the index of the list item that corresponds to the given child
     * {@code Control}.
     *
     * @return	    an index, or -1 if no index is appropriate
     */
    protected abstract int getListIndexOf(Control child);

    /**
     * Gets the model to use in the {@link ListSelectorPanel}'s list.
     */
    protected abstract ListModel getListModel();
}
