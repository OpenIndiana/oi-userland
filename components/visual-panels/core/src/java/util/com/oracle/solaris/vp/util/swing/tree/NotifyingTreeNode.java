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

package com.oracle.solaris.vp.util.swing.tree;

import java.util.*;
import javax.swing.event.*;
import javax.swing.tree.*;
import com.oracle.solaris.vp.util.swing.event.TreeModelListeners;

/**
 * The {@code NotifyingTreeNode} class propagates insertions/deletions to the
 * {@code TreeNode} to registered listeners.  The {@code NotifyingTreeNode} adds
 * itself as a {@code TreeModelListener} to each of its children.
 */
@SuppressWarnings({"serial"})
public class NotifyingTreeNode<U> extends TypedTreeNode<U>
    implements TreeModelListener {

    //
    // Instance data
    //

    private TreeModelListeners listeners = new TreeModelListeners();

    //
    // Constructors
    //

    public NotifyingTreeNode() {
    }

    public NotifyingTreeNode(Object userObject) {
	super(userObject);
    }

    public NotifyingTreeNode(Object userObject, boolean allowsChildren) {
	super(userObject, allowsChildren);
    }

    //
    // TreeModelListener methods
    //

    /**
     * Propagates the given event to registered listeners.
     */
    @Override
    public void treeNodesChanged(TreeModelEvent e) {
	listeners.treeNodesChanged(e);
    }

    /**
     * Propagates the given event to registered listeners.
     */
    @Override
    public void treeNodesInserted(TreeModelEvent e) {
	listeners.treeNodesInserted(e);
    }

    /**
     * Propagates the given event to registered listeners.
     */
    @Override
    public void treeNodesRemoved(TreeModelEvent e) {
	listeners.treeNodesRemoved(e);
    }

    /**
     * Propagates the given event to registered listeners.
     */
    @Override
    public void treeStructureChanged(TreeModelEvent e) {
	listeners.treeStructureChanged(e);
    }

    //
    // DefaultMutableTreeNode methods
    //

    @Override
    public void insert(MutableTreeNode child, int index) {
	super.insert(child, index);

	if (child instanceof TreeModelListener) {
	    ((NotifyingTreeNode)child).addTreeModelListener(this);
	}
    }

    @Override
    public void remove(int index) {
	TreeNode child = getChildAt(index);
	if (child instanceof TreeModelListener) {
	    ((NotifyingTreeNode)child).removeTreeModelListener(this);
	}

	super.remove(index);
    }

    //
    // NotifyingTreeNode methods
    //

    public void addTreeModelListener(TreeModelListener listener) {
	listeners.add(listener);
    }

    /**
     * Called when this {@code TreeNode} has changed.
     */
    public void fireTreeNodeChanged() {
	TreePath path = null;
	int index = 0;

	TreeNode parent = getParent();
	if (parent != null) {
	    index = parent.getIndex(this);
	}

	TreeModelEvent event = new TreeModelEvent(
	    this, path, new int[] {index}, new TreeNode[] {this});

	treeNodesChanged(event);
    }

    /**
     * Called when child {@code TreeNode}s of this {@code TreeNode} have
     * changed.
     */
    public void fireTreeNodesChanged(TreeNode[] nodes, int[] indexes) {
	TreeModelEvent event =
	    new TreeModelEvent(this, getTreePath(), indexes, nodes);

	treeNodesChanged(event);
    }

    public void fireTreeNodesInserted(TreeNode[] nodes, int[] indexes) {
	TreeModelEvent event =
	    new TreeModelEvent(this, getTreePath(), indexes, nodes);

	treeNodesInserted(event);
    }

    public void fireTreeNodesRemoved(TreeNode[] nodes, int[] indexes) {
	TreeModelEvent event =
	    new TreeModelEvent(this, getTreePath(), indexes, nodes);

	treeNodesRemoved(event);
    }

    public void fireTreeStructureChanged() {
	TreeModelEvent event = new TreeModelEvent(this, getTreePath());
	treeStructureChanged(event);
    }

    public TreePath getTreePath() {
	List<Object> path = new ArrayList<Object>();
	path.add(this);

	TreeNode parent = getParent();
	while (parent != null) {
	    path.add(0, parent);
	    parent = parent.getParent();
	}

	Object[] array = path.toArray(new Object[path.size()]);
	return new TreePath(array);
    }

    public void removeTreeModelListener(TreeModelListener listener) {
	listeners.remove(listener);
    }
}
