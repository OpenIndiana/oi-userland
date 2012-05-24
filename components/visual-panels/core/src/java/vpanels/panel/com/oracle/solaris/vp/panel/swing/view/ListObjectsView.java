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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.Dimension;
import java.util.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.action.StructuredAction;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.ExtScrollPane;

/**
 * The {@code ListObjectsView} class displays the children of a {@code
 * ManagedObject} in a {@code JList}.
 */
public class ListObjectsView<C extends ManagedObject> extends ObjectsView<C> {
    //
    // Instance data
    //

    private ManagedObjectList list;
    private ManagedObjectTableModel<C> model;
    private ExtScrollPane scroll;

    //
    // Constructors
    //

    public ListObjectsView(ManagedObject<C> pObject,
	StructuredAction<List<C>, ?, ?>[] mActions,
	StructuredAction<List<C>, ?, ?> dmAction, boolean iconView) {

	super(pObject, mActions, dmAction);

	SimplePopupMenu popupMenu = mActions == null || mActions.length == 0 ?
	    null : new SimplePopupMenu(mActions);

	model = new ManagedObjectTableModel<C>(pObject);
	model.addListDataListener(
	    new ListDataListener() {
		@Override
		public void contentsChanged(ListDataEvent e) {
		    fireObjectCountChange();
		}

		@Override
		public void intervalAdded(ListDataEvent e) {
		    fireObjectCountChange();
		}

		@Override
		public void intervalRemoved(ListDataEvent e) {
		    fireObjectCountChange();
		}
	    });

	list = new ManagedObjectList(model, popupMenu, dmAction, iconView) {
	    @Override
	    public Dimension getPreferredScrollableViewportSize() {
		Dimension d = super.getPreferredScrollableViewportSize();
		// Provide a sane max preferred height
		d.height = Math.min(d.height, 400);
		return d;
	    }
	};

	list.setOpaque(true);
	list.setFillsViewportHeight(true);

	// Notify Actions of changes in selection model
	list.getSelectionModel().addListSelectionListener(
	    updateActionSelectionListener);

	scroll = new ExtScrollPane(list);
	scroll.removeBorder();
	scroll.setBorder(ObjectsPanel.BORDER_CONTENT_LINE);
    }

    //
    // ObjectsView methods
    //

    @Override
    public ExtScrollPane getComponent() {
	return scroll;
    }

    @Override
    public String getName() {
	return Finder.getString("objects.header.view.value.list");
    }

    @Override
    public int getObjectCount() {
	return model.getSize();
    }

    @Override
    public List<C> getSelection() {
	int[] indexes = list.getSelectedIndices();
	List<C> selection = new ArrayList<C>(indexes.length);

	for (int i = 0; i < indexes.length; i++) {
	    selection.add(model.getElementAt(indexes[i]));
	}

	return selection;
    }

    //
    // ListObjectsView methods
    //

    public ManagedObjectList getList() {
	return list;
    }
}
