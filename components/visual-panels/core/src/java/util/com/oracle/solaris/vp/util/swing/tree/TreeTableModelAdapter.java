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
import javax.swing.ListModel;
import javax.swing.event.*;
import javax.swing.table.TableModel;
import javax.swing.tree.TreeNode;
import com.oracle.solaris.vp.util.swing.ListDataListenerAdapter;
import com.oracle.solaris.vp.util.swing.event.TableModelListeners;

/**
 * The {@code TreeTableModelAdapter} class maps a {@link TreeTableModel} onto a
 * {@code TableModel} and a {@code ListModel}.
 */
@SuppressWarnings({"serial"})
public class TreeTableModelAdapter implements TableModel, ListModel,
    TreeModelListener {

    //
    // Instance data
    //

    private List<ModelRowData> rows = new LinkedList<ModelRowData>();
    private TreeTableModel model;
    private TableModelListeners listeners = new TableModelListeners();

    private Map<ListDataListener, ListDataListenerAdapter> listenerMap =
	new HashMap<ListDataListener, ListDataListenerAdapter>();

    private int listColumn;

    //
    // Constructors
    //

    public TreeTableModelAdapter(TreeTableModel model) {
	this.model = model;

	addRows(0, (TreeNode)model.getRoot(), 0);
	model.addTreeModelListener(this);
    }

    //
    // TableModel methods
    //

    @Override
    public void addTableModelListener(TableModelListener l) {
	listeners.add(l);
    }

    @Override
    public Class<?> getColumnClass(int column) {
	return model.getColumnClass(column);
    }

    @Override
    public int getColumnCount() {
	return model.getColumnCount();
    }

    @Override
    public String getColumnName(int column) {
	return model.getColumnName(column);
    }

    @Override
    public int getRowCount() {
	return rows.size();
    }

    @Override
    public Object getValueAt(int row, int column) {
	return model.getValueAt(getTreeNode(row), column);
    }

    @Override
    public boolean isCellEditable(int row, int column) {
	return model.isCellEditable(getTreeNode(row), column);
    }

    @Override
    public void removeTableModelListener(TableModelListener l) {
	listeners.remove(l);
    }

    @Override
    public void setValueAt(Object value, int row, int column) {
	model.setValueAt(value, getTreeNode(row), column);
    }

    //
    // ListModel methods
    //

    @Override
    public void addListDataListener(ListDataListener l) {
	synchronized (listenerMap) {
	    if (!listenerMap.containsKey(l)) {
		ListDataListenerAdapter adapter =
		    new ListDataListenerAdapter(l);

		addTableModelListener(adapter);
		listenerMap.put(l, adapter);
	    }
	}
    }

    /**
     * Returns the value of the cell in the {@link #getListColumn list column}
     * of the given row.
     */
    @Override
    public Object getElementAt(int row) {
	return getValueAt(row, getListColumn());
    }

    @Override
    public int getSize() {
	return getRowCount();
    }

    @Override
    public void removeListDataListener(ListDataListener l) {
	synchronized (listenerMap) {
	    ListDataListenerAdapter adapter = listenerMap.get(l);
	    if (adapter != null) {
		removeTableModelListener(adapter);
		listenerMap.remove(l);
	    }
	}
    }

    //
    // TreeModelListener methods
    //

    @Override
    public void treeNodesChanged(TreeModelEvent e) {
	synchronized (rows) {
	    for (Object child : e.getChildren()) {
		TreeNode node = (TreeNode)child;
		int index = indexOf(node);

		TableModelEvent event = new TableModelEvent(
		    this, index, index, TableModelEvent.ALL_COLUMNS,
		    TableModelEvent.UPDATE);

		fireTableChanged(event);
	    }
	}
    }

    @Override
    public void treeNodesInserted(TreeModelEvent e) {
	TreeNode node = (TreeNode)e.getTreePath().getLastPathComponent();
	ModelRowData row = getRow(indexOf(node));
	int level = row.getLevel() + 1;

	int[] indexes = e.getChildIndices();
	Object[] children = e.getChildren();

	synchronized (rows) {
	    for (int i = 0; i < indexes.length; i++) {
		int first = indexOf(node, indexes[i]);
		TreeNode child = (TreeNode)children[i];
		int last = addRows(first, child, level) - 1;

		TableModelEvent event = new TableModelEvent(
		    this, first, last, TableModelEvent.ALL_COLUMNS,
		    TableModelEvent.INSERT);

		fireTableChanged(event);
	    }
	}
    }

    @Override
    public void treeNodesRemoved(TreeModelEvent e) {
	TreeNode node = (TreeNode)e.getTreePath().getLastPathComponent();
	Object[] children = e.getChildren();

	synchronized (rows) {
	    for (int i = children.length - 1; i >= 0; i--) {
		TreeNode child = (TreeNode)children[i];
		int first = indexOf(child);
		int last = indexOf(child, -1) - 1;

		for (int j = last; j >= first; j--) {
		    rows.remove(j);
		}

		TableModelEvent event = new TableModelEvent(
		    this, first, last, TableModelEvent.ALL_COLUMNS,
		    TableModelEvent.DELETE);

		fireTableChanged(event);
	    }
	}
    }

    @Override
    public void treeStructureChanged(TreeModelEvent e) {
	TableModelEvent event = new TableModelEvent(
	    this, TableModelEvent.HEADER_ROW);

	fireTableChanged(event);
    }

    //
    // TreeTableModelAdapter methods
    //

    public void fireTableChanged(TableModelEvent e) {
	listeners.tableChanged(e);
    }

    /**
     * Gets the column to returned by the {@code ListModel} method {@link
     * #getElementAt}.
     *
     * @see	    #setListColumn
     */
    public int getListColumn() {
	return listColumn;
    }

    protected ModelRowData getParent(ModelRowData row) {
	synchronized (rows) {
	    TreeNode parent = row.getTreeNode().getParent();
	    if (parent != null) {
		return getRow(parent);
	    }
	    return null;
	}
    }

    protected ModelRowData getRow(int row) {
	synchronized (rows) {
	    return rows.get(row);
	}
    }

    protected ModelRowData getRow(TreeNode node) {
	synchronized (rows) {
	    for (ModelRowData row : rows) {
		if (row.getTreeNode() == node) {
		    return row;
		}
	    }
	}
	return null;
    }

    public TreeNode getTreeNode(int row) {
	return getRow(row).getTreeNode();
    }

    public TreeTableModel getTreeTableModel() {
	return model;
    }

    public int indexOf(TreeNode node) {
	for (int i = 0, n = rows.size(); i < n; i++) {
	    ModelRowData row = getRow(i);
	    if (row.getTreeNode() == node) {
		return i;
	    }
	}
	return -1;
    }

    /**
     * Sets the column to returned by the {@code ListModel} method {@link
     * #getElementAt}.  The default value is 0.
     *
     * @see	    #getListColumn
     */
    public void setListColumn(int listColumn) {
	this.listColumn = listColumn;
    }

    //
    // Private methods
    //

    /**
     * Adds the given {@code TreeNode} and its children to the list of rows;
     * returns the current insertion point.
     */
    private int addRows(int index, TreeNode node, int level) {
	synchronized (rows) {
	    ModelRowData row = new ModelRowData(node, level);
	    rows.add(index, row);
	    index++;
	    level++;
	    for (Enumeration i = node.children(); i.hasMoreElements();) {
		TreeNode child = (TreeNode)i.nextElement();
		index = addRows(index, child, level);
	    }
	    return index;
	}
    }

    /**
     * Gets the index of the {@code (childIndex + 1)}th child of the given node.
     *
     * @return	    an index, or -1 if the given {@code TreeNode} is not found
     */
    private int indexOf(TreeNode node, int childIndex) {
	synchronized (rows) {
	    int i = indexOf(node);
	    if (i != -1) {
		ModelRowData row = getRow(i++);
		if (row.getTreeNode() == node) {

		    for (int n = rows.size(); i < n; i++) {
			int level = getRow(i).getLevel();
			if (level <= row.getLevel()) {
			    break;
			}

			if (level == row.getLevel() + 1) {
			    childIndex--;
			    if (childIndex == -1) {
				break;
			    }
			}
		    }
		}
	    }

	    return i;
	}
    }
}
