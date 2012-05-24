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
 * Copyright (c) 2004, 2012, Oracle and/or its affiliates. All rights reserved.
 */


package com.oracle.solaris.vp.panels.usermgr.client.swing;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;
import javax.swing.border.*;
import javax.swing.tree.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;


/**
 * SMC code adapted for Visual Panels
 *
 * DoubleTrees class implements an excluded and included tree
 */
public class DoubleTrees extends JPanel {

    public final static Border emptyBorder10 = new EmptyBorder(10, 10, 10, 10);

    public JTree srcTree;
    public JTree dstTree;
    public JButton addItem;
    public JButton delItem;
    public JButton addAllItem;
    public JButton delAllItem;

    public JPanel selPanel = this;

    /**
     * Constructor.
     */
    public DoubleTrees() {
	String srcHeader = "excluded_tree_header";
	String dstHeader = "included_tree_header";

	makePanel(srcHeader, dstHeader);
    }


    public DoubleTrees(String srcHeader, String dstHeader) {
	makePanel(srcHeader, dstHeader);
    }

    private void makePanel(JPanel panel, String srcHeader, String dstHeader) {
	DoubleTreesLayout layout = new DoubleTreesLayout();
	panel.setLayout(layout);

	DoubleTreesConstraints constraints = new DoubleTreesConstraints();

	// src label

	JLabel srcLabel = new JLabel();
	setUpLabel(srcLabel, srcHeader);

	constraints.location = constraints.LEFT_LABEL;
	constraints.insets = new Insets(5, 5, 5, 5);

	layout.setConstraints(srcLabel, constraints);
	panel.add(srcLabel);

	// src tree

	JScrollPane srcScroll = newTree();
	srcTree = (JTree) srcScroll.getViewport().getView();

	constraints.location = constraints.LEFT_SCROLLPANE;
	constraints.insets = new Insets(5, 5, 5, 5);

	layout.setConstraints(srcScroll, constraints);
	panel.add(srcScroll);

	srcLabel.setLabelFor(srcTree);

	// buttons

	JPanel buttonPanel = new JPanel();

	Component spacer1 = Box.createVerticalStrut(5);
	Component spacer2 = Box.createVerticalStrut(25);
	Component spacer3 = Box.createVerticalStrut(5);

	GridBagLayout buttonLayout = new GridBagLayout();
	GridBagConstraints buttonConstraints = new GridBagConstraints();

	buttonPanel.setLayout(buttonLayout);

	addItem = new JButton();
	addItem.setEnabled(false);
	setUpButton(addItem, "usermgr.advanced.add_btn");

	delItem = new JButton();
	delItem.setEnabled(false);
	setUpButton(delItem, "usermgr.advanced.remove_btn");

	addAllItem = new JButton();
	setUpButton(addAllItem, "usermgr.advanced.add_all_btn");

	delAllItem = new JButton();
	setUpButton(delAllItem, "usermgr.advanced.remove_all_btn");

	buttonConstraints.gridx = 0;
	buttonConstraints.gridy = buttonConstraints.RELATIVE;
	buttonConstraints.gridwidth = 1;
	buttonConstraints.gridheight = 1;
	buttonConstraints.weightx = 0.0;
	buttonConstraints.weighty = 0.0;
	buttonConstraints.fill = buttonConstraints.HORIZONTAL;
	buttonConstraints.anchor = buttonConstraints.CENTER;

	buttonPanel.add(addItem, buttonConstraints);
	buttonPanel.add(spacer1, buttonConstraints);
	buttonPanel.add(delItem, buttonConstraints);
	buttonPanel.add(spacer2, buttonConstraints);
	buttonPanel.add(addAllItem, buttonConstraints);
	buttonPanel.add(spacer3, buttonConstraints);
	buttonPanel.add(delAllItem, buttonConstraints);

	constraints.location = constraints.BUTTONS;

	layout.setConstraints(buttonPanel, constraints);
	panel.add(buttonPanel);

	// dst label

	JLabel dstLabel = new JLabel();
	setUpLabel(dstLabel, dstHeader);

	constraints.location = constraints.RIGHT_LABEL;
	constraints.insets = new Insets(5, 5, 5, 5);

	layout.setConstraints(dstLabel, constraints);
	panel.add(dstLabel);

	// dst tree

	JScrollPane dstScroll = newTree();
	dstTree = (JTree) dstScroll.getViewport().getView();

	constraints.location = constraints.RIGHT_SCROLLPANE;
	constraints.insets = new Insets(5, 5, 5, 5);

	layout.setConstraints(dstScroll, constraints);
	panel.add(dstScroll);

	dstLabel.setLabelFor(dstTree);
    }

    private void makePanel(String srcHeader, String dstHeader) {
	makePanel(this, srcHeader, dstHeader);
    }

    private JScrollPane newTree() {
	DefaultTreeModel treeModel = new DefaultTreeModel(
		new DblTreeNode("All Items"));

	JTree tree = new JTree(treeModel);
	JScrollPane treeScroll = new JScrollPane(tree);

	tree.getSelectionModel().setSelectionMode(
		TreeSelectionModel.SINGLE_TREE_SELECTION);

	tree.setLargeModel(true);
	tree.setRootVisible(false);
	tree.setShowsRootHandles(true);

	treeScroll.setVerticalScrollBarPolicy(
		ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
	treeScroll.setHorizontalScrollBarPolicy(
		ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);

	tree.putClientProperty("JTree.lineStyle", "Angled");

	return treeScroll;
    }

    /**
     * Convenience method for creating & initializing
     * a new JLabel
     *
     * @param  label the component to initialize
     * @param  txt the text displayed
     */
    private void setUpLabel(JLabel label, String txt) {
        ActionString actionString = new ActionString(txt);
        label.setText(actionString.getString());
        label.setDisplayedMnemonic(actionString.getMnemonic());
	label.setHorizontalAlignment(label.LEFT);
	label.setVerticalAlignment(label.BOTTOM);
    }

    /**
     * Convenience method for creating & initializing
     * a new JButton
     *
     * @param  button the component to initialize
     * @param  txt the text displayed
     */
    private void setUpButton(AbstractButton button, String txt) {
        ActionString actionString = new ActionString(txt);
        button.setText(actionString.getString());
        button.setMnemonic(actionString.getMnemonic());
    }

    /**
     * Set initial selection of a tree node
     *
     */
    public void setInitSelection() {
	DblTreeNode child;
	TreePath nodepath;

	DefaultTreeModel srcModel = (DefaultTreeModel)srcTree.getModel();
	DefaultTreeModel dstModel = (DefaultTreeModel)dstTree.getModel();
	DblTreeNode srcRoot = (DblTreeNode)srcModel.getRoot();
	DblTreeNode dstRoot = (DblTreeNode)dstModel.getRoot();

	if (srcTree.isRootVisible()) {

	    nodepath = new TreePath(srcRoot);
	    srcTree.setSelectionPath(nodepath);
            addItem.setEnabled(true);
            delItem.setEnabled(false);

	} else if (srcRoot.getChildCount() > 0) {

	    child = (DblTreeNode)srcRoot.getFirstChild();
	    nodepath = new TreePath(child.getPath());
	    srcTree.setSelectionPath(nodepath);
	    srcTree.scrollPathToVisible(nodepath);
	    addItem.setEnabled(true);
	    delItem.setEnabled(false);

        } else if (dstTree.isRootVisible()) {

	    nodepath = new TreePath(dstRoot);
	    dstTree.setSelectionPath(nodepath);
            addItem.setEnabled(false);
            delItem.setEnabled(true);

	} else if (dstRoot.getChildCount() > 0) {

	    child = (DblTreeNode)dstRoot.getFirstChild();
	    nodepath = new TreePath(child.getPath());
	    dstTree.setSelectionPath(nodepath);
	    dstTree.scrollPathToVisible(nodepath);
	    addItem.setEnabled(false);
	    delItem.setEnabled(true);

	}
    }
}
