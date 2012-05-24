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
import javax.swing.JTree;
import javax.swing.event.*;
import javax.swing.tree.*;
import com.oracle.solaris.vp.panel.common.control.Control;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.swing.view.TreeSelectorPanel;

@SuppressWarnings({"serial"})
public abstract class TreeSelectorControl<P extends PanelDescriptor,
    C extends TreeSelectorPanel, S> extends SelectorControl<P, C, S> {

    //
    // Inner classes
    //

    protected class NavTreeSelectionModel extends DefaultTreeSelectionModel {
	//
	// TreeSelectionModel methods
	//

	@Override
	public void setSelectionPaths(TreePath[] paths) {
	    setSelectionPathsDirectly(paths);
	    goToSelected();
	}

	//
	// NavTreeSelectionModel methods
	//

	public void setSelectionPathsDirectly(TreePath... paths) {
	    super.setSelectionPaths(paths);

	    if (paths != null & paths.length != 0) {
		getComponent().getSelectionComponent().scrollPathToVisible(
		    paths[0]);
	    }
	}
    }

    //
    // Instance data
    //

    private NavTreeSelectionModel treeSelModel;

    //
    // Constructors
    //

    public TreeSelectorControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(C panel) {
	super.configComponent(panel);

	JTree tree = panel.getSelectionComponent();
	tree.setModel(getTreeModel());

	treeSelModel = new NavTreeSelectionModel();
	tree.setSelectionModel(treeSelModel);

	treeSelModel.addTreeSelectionListener(
	    new TreeSelectionListener() {
		@Override
		public void valueChanged(TreeSelectionEvent e) {
		    updateActions();
		}
	    });

	initExpand();
    }

    //
    // SelectorControl methods
    //

    @Override
    protected List<S> getSelectableValues() {
	List<S> values = new LinkedList<S>();
	TreeModel model = getTreeModel();
	TreePath path = new TreePath(model.getRoot());
	addValues(values, model, path, true);

	return values;
    }

    @Override
    protected List<S> getSelectedValues() {
	TreePath[] selection =
	    getComponent().getSelectionComponent().getSelectionPaths();

	List<S> objects;
	if (selection == null || selection.length == 0) {
	    objects = Collections.emptyList();
	} else {
	    objects = new ArrayList<S>(selection.length);
	    for (TreePath path : selection) {
		S object = getSelectionForPath(path);
		objects.add(object);
	    }
	}

	return objects;
    }

    @Override
    protected void selectRunningChild() {
	Control child = getRunningChild();
	if (child != null) {
	    final TreePath path = getTreePathOf(child);
	    if (path != null) {
		EventQueue.invokeLater(
		    new Runnable() {
			@Override
			public void run() {
			    // Set tree selection directly without going through
			    // the Navigator
			    treeSelModel.setSelectionPathsDirectly(path);
			}
		    });
	    }
	}
    }

    //
    // TreeSelectorControl methods
    //

    /**
     * Determines whether the given {@code TreePath} should be expanded when the
     * expanded/collapsed state of each node in the tree is initialized.
     * <p/>
     * This default implementation returns {@code false}.
     *
     * @param	    path
     *		    a path to a non-leaf node in the tree
     *
     * @return	    {@code true} to expand the given path, {@code false}
     *		    to collapse it
     *
     * @see	    #initExpand
     */
    public boolean getExpandOnInit(TreePath path) {
	return false;
    }

    /**
     * Convert the given {@link TreePath} into a selected object.
     * <p/>
     * This default implementation assumes the last node in the given path is a
     * {@code DefaultMutableTreeNode} and returns the value from its {@code
     * getUserObject} method, cast to an {@code S}.
     *
     * @throws	    ClassCastException
     *		    if the underlying {@code TreeModel} does not follow the
     *		    above convention
     */
    protected S getSelectionForPath(TreePath path) {
	DefaultMutableTreeNode node = (DefaultMutableTreeNode)
	    path.getLastPathComponent();

	@SuppressWarnings({"unchecked"})
	S value = (S)node.getUserObject();

	return value;
    }

    /**
     * Gets the model to use in the {@link TreeSelectorPanel}'s tree.
     */
    protected abstract TreeModel getTreeModel();

    /**
     * Gets the {@code TreePath} that corresponds to the given child {@code
     * Control}.
     *
     * @return	    a {@code TreePath}, or {@code null} if no {@code TreePath}
     *		    is appropriate
     */
    protected abstract TreePath getTreePathOf(Control child);

    /**
     * Initializes the expanded/collapsed state of each node in the tree.
     *
     * @see	    #getExpandOnInit
     */
    protected void initExpand() {
	JTree tree = getComponent().getSelectionComponent();
	TreeModel model = tree.getModel();

	for (int row = 0; row < tree.getRowCount(); row++) {
	    TreePath path = tree.getPathForRow(row);
	    Object node = path.getLastPathComponent();
	    if (!model.isLeaf(node)) {
		if (getExpandOnInit(path)) {
		    tree.expandRow(row);
		} else {
		    tree.collapseRow(row);
		}
	    }
	}
    }

    //
    // Private methods
    //

    private void addValues(List<S> values, TreeModel model, TreePath path,
	boolean isRoot) {

	if (!isRoot || getComponent().getSelectionComponent().isRootVisible()) {
	    S value = getSelectionForPath(path);
	    values.add(value);
	}

	Object object = path.getLastPathComponent();
	for (int i = 0, n = model.getChildCount(object); i < n; i++) {
	    Object child = model.getChild(object, i);
	    TreePath childPath = path.pathByAddingChild(child);
	    addValues(values, model, childPath, false);
	}
    }
}
