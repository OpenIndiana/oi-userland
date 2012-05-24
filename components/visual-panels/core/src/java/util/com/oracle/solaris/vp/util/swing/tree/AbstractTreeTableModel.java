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

import java.util.Comparator;
import javax.swing.event.*;
import javax.swing.table.*;
import javax.swing.tree.*;
import com.oracle.solaris.vp.util.common.propinfo.PropInfo;
import com.oracle.solaris.vp.util.swing.propinfo.SwingPropInfo;

@SuppressWarnings({"serial"})
public abstract class AbstractTreeTableModel extends DefaultTreeModel
    implements TreeTableModel, TreeModelListener {

    //
    // Instance data
    //

    private PropInfo<?, ?>[] props;

    //
    // Constructors
    //

    public AbstractTreeTableModel(TreeNode root, PropInfo<?, ?>[] props) {
	super(root);
	this.props = props;
    }

    public AbstractTreeTableModel(TreeNode root, boolean asksAllowsChildren,
	PropInfo<?, ?>[] props) {

	super(root, asksAllowsChildren);
	this.props = props;
    }

    //
    // TreeModel methods
    //

    @Override
    public TreeNode getRoot() {
	return (TreeNode)super.getRoot();
    }

    //
    // TreeTableModel methods
    //

    @Override
    public Class<?> getColumnClass(int column) {
	TreeNode root = getRoot();
	try {
	    return getValueAt(root, column).getClass();
	}

	// Most likely NullPointerException
	catch (Throwable e) {
	    return Object.class;
	}
    }

    @Override
    public int getColumnCount() {
	return props == null ? 0 : props.length;
    }

    @Override
    public String getColumnName(int column) {
	return props[column].getLabel();
    }

    @Override
    @SuppressWarnings({"unchecked"})
    public Object getValueAt(TreeNode node, int column) {
	Object o = getUserObject(node);
	PropInfo prop = props[column];
	return prop.getValue(o);
    }

    @Override
    @SuppressWarnings({"unchecked"})
    public boolean isCellEditable(TreeNode node, int column) {
	Object o = getUserObject(node);
	PropInfo prop = props[column];
	return prop.isEditable(o);
    }

    @Override
    public boolean isTreeColumn(int column) {
	return column == 0;
    }

    @Override
    @SuppressWarnings({"unchecked"})
    public void setValueAt(Object value, TreeNode node, int column) {
	Object o = getUserObject(node);
	PropInfo prop = props[column];
	prop.setValue(o, value);
    }

    //
    // AbstractTreeTableModel methods
    //

    public Comparator<?> getComparator(int column) {
	return props[column].getComparator();
    }

    public PropInfo<?, ?>[] getPropInfos() {
	return props;
    }

    public TableCellEditor getTableCellEditor(int column) {
	TableCellEditor editor = null;

	PropInfo prop = props[column];
	if (prop instanceof SwingPropInfo) {
	    editor = ((SwingPropInfo)prop).getTableCellEditor();
	}

	return editor;
    }

    public TableCellRenderer getTableCellRenderer(int column) {
	TableCellRenderer renderer = null;

	PropInfo prop = props[column];
	if (prop instanceof SwingPropInfo) {
	    renderer = ((SwingPropInfo)prop).getTableCellRenderer();
	}

	return renderer;
    }

    protected abstract Object getUserObject(TreeNode node);

    //
    // TreeModelListener methods
    //

    /**
     * Propagates the given event to registered listeners.
     */
    @Override
    public void treeNodesChanged(TreeModelEvent e) {
	TreeModelListener[] listeners = getTreeModelListeners();
	for (int i = 0; i < listeners.length; i++) {
	    listeners[i].treeNodesChanged(e);
	}
    }

    /**
     * Propagates the given event to registered listeners.
     */
    @Override
    public void treeNodesInserted(TreeModelEvent e) {
	TreeModelListener[] listeners = getTreeModelListeners();
	for (int i = 0; i < listeners.length; i++) {
	    listeners[i].treeNodesInserted(e);
	}
    }

    /**
     * Propagates the given event to registered listeners.
     */
    @Override
    public void treeNodesRemoved(TreeModelEvent e) {
	TreeModelListener[] listeners = getTreeModelListeners();
	for (int i = 0; i < listeners.length; i++) {
	    listeners[i].treeNodesRemoved(e);
	}
    }

    /**
     * Propagates the given event to registered listeners.
     */
    @Override
    public void treeStructureChanged(TreeModelEvent e) {
	TreeModelListener[] listeners = getTreeModelListeners();
	for (int i = 0; i < listeners.length; i++) {
	    listeners[i].treeStructureChanged(e);
	}
    }
}
