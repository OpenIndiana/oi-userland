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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.EventQueue;
import java.beans.*;
import java.util.List;
import javax.swing.tree.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.swing.tree.NotifyingTreeNode;
import com.oracle.solaris.vp.util.misc.event.*;

@SuppressWarnings({"serial"})
public class ManagedObjectTreeNode
    extends NotifyingTreeNode<ManagedObject<? extends ManagedObject>>
    implements IntervalListener, PropertyChangeListener {

    //
    // Constructors
    //

    public ManagedObjectTreeNode(ManagedObject<?> object) {
	super(object);

	addNodes(0, -1);
	object.addIntervalListener(this);
	object.addPropertyChangeListener(this);
    }

    //
    // IntervalListener methods
    //

    @Override
    public void intervalAdded(final IntervalEvent e) {
	// We are likely not on the event queue thread
	EventQueue.invokeLater(
	    new Runnable() {
		@Override
		public void run() {
		    int first = e.getFirstIndex();
		    int last = e.getLastIndex();
		    addNodes(first, last);
		}
	    });
    }

    @Override
    public void intervalRemoved(final IntervalEvent e) {
	// We are likely not on the event queue thread
	EventQueue.invokeLater(
	    new Runnable() {
		@Override
		public void run() {
		    int first = e.getFirstIndex();
		    int last = e.getLastIndex();
		    removeNodes(first, last);
		}
	    });
    }

    //
    // PropertyChangeListener methods
    //

    @Override
    public void propertyChange(PropertyChangeEvent e) {
	// We are likely not on the event queue thread
	EventQueue.invokeLater(
	    new Runnable() {
		@Override
		public void run() {
		    fireTreeNodeChanged();
		}
	    });
    }

    //
    // Private methods
    //

    private void addNodes(int first, int last) {
	List<? extends ManagedObject> children = getUserObject().getChildren();
	if (last < 0) {
	    last = children.size() + last;
	}

	int size = last - first + 1;
	MutableTreeNode[] nodes = new MutableTreeNode[size];
	int[] indexes = new int[size];

	for (int i = 0; i < size; i++) {
	    int index = first + i;
	    ManagedObject child = children.get(index);
	    nodes[i] = new ManagedObjectTreeNode(child);
	    indexes[i] = index;
	    insert(nodes[i], indexes[i]);
	}

	fireTreeNodesInserted(nodes, indexes);
    }

    private void removeNodes(int first, int last) {
	int size = last - first + 1;

	TreeNode[] nodes = new TreeNode[size];
	int[] indexes = new int[size];

	for (int i = size - 1; i >= 0; i--) {
	    int index = first + i;
	    nodes[i] = getChildAt(index);
	    indexes[i] = index;
	    remove(index);
	}

	fireTreeNodesRemoved(nodes, indexes);
    }
}
