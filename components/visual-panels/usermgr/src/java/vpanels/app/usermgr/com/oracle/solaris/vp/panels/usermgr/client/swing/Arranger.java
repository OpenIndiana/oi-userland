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
 * Copyright (c) 2000, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;
import javax.swing.border.*;
import javax.swing.tree.*;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.util.*;
import java.io.*;

import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * SMC code adapted for Visual Panels
 */
public class Arranger extends DoubleTrees {

    JButton moveUpItem, moveDownItem;

    public Arranger() {

	// Map DoubleTrees variables here for better descriptive names
	moveUpItem = addAllItem;
	moveDownItem = delAllItem;

	setListeners();
    }

    public Arranger(String srcHeader, String dstHeader) {

	super(srcHeader, dstHeader);

	// Map DoubleTrees variables here for better descriptive names
	moveUpItem = addAllItem;
	moveDownItem = delAllItem;

	setListeners();

    }

    /**
     * Create any dynamic images we need.
     */
    public void addNotify() {

	ActionString actionString;

	super.addNotify();

	delItem.setIcon(Finder.getIcon("images/remove.png"));
	delItem.setHorizontalTextPosition(JButton.RIGHT);

	moveDownItem.setIcon(Finder.getIcon("images/move_dn.png"));
	moveDownItem.setHorizontalTextPosition(JButton.LEFT);
        actionString = new ActionString("usermgr.advanced.move_down_btn");
        moveDownItem.setText(actionString.getString());
        moveDownItem.setMnemonic(actionString.getMnemonic());

	addItem.setIcon(Finder.getIcon("images/add.png"));
	addItem.setHorizontalTextPosition(JButton.LEFT);

	moveUpItem.setIcon(Finder.getIcon("images/move_up.png"));
	moveUpItem.setHorizontalTextPosition(JButton.LEFT);
	actionString = new ActionString("usermgr.advanced.move_up_btn");
        moveUpItem.setText(actionString.getString());
        moveUpItem.setMnemonic(actionString.getMnemonic());

    } // addNotify

    public void setListeners() {

	addItem.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		move(srcTree, dstTree);
	    }
	});

	delItem.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		move(dstTree, srcTree);
	    }
	});

	moveUpItem.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		reorder(dstTree, -1);
	    }
	});

	moveDownItem.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		reorder(dstTree, +1);
		}
	    });

	MouseListener ml = new MouseAdapter() {
	    public void mouseClicked(MouseEvent e) {
		handleMouse(e);
	    }

	    public void mousePressed(MouseEvent e) {
		handleMouse(e);
	    }
	};

	srcTree.addMouseListener(ml);
	dstTree.addMouseListener(ml);

    }

    private void updateMoveButtons(DblTreeNode node, boolean flag) {

	if (flag) {
	    DefaultTreeModel    dstModel = (DefaultTreeModel)dstTree.getModel();
	    DblTreeNode root = (DblTreeNode)dstModel.getRoot();

	    int index = dstModel.getIndexOfChild(root, node);
	    int limit = dstModel.getChildCount(root);

	    if (index > 0)
		moveUpItem.setEnabled(true);
	    else
		moveUpItem.setEnabled(false);
	    if (index < (limit - 1))
		moveDownItem.setEnabled(true);
	    else
		moveDownItem.setEnabled(false);
	} else {
	    moveUpItem.setEnabled(false);
	    moveDownItem.setEnabled(false);
	}

    }

    private void handleMouse(MouseEvent e) {

	JTree  tree1, tree2;

	if (e.getSource() == srcTree) {
	    tree1 = srcTree;
	    tree2 = dstTree;

	    delItem.setEnabled(false);
	    moveUpItem.setEnabled(false);
	    moveDownItem.setEnabled(false);
	} else {
            tree1 = dstTree;
	    tree2 = srcTree;
	    addItem.setEnabled(false);
	}
	TreePath selPath = tree1.getPathForLocation(e.getX(), e.getY());

	if (selPath != null) {
	    tree2.clearSelection();
	    int selCount = selPath.getPathCount();

	    DblTreeNode node = (DblTreeNode)selPath.getLastPathComponent();
	    if (e.getClickCount() < 2) {
		boolean flag;
		if (selCount == 2)
		    flag = true;
		else
		    flag = false;

		if (e.getSource() == srcTree) {
		    addItem.setEnabled(flag);
		} else {
		    delItem.setEnabled(flag);
		    updateMoveButtons(node, flag);
		}
	    } else if (e.getClickCount() == 2) {
		if ((selCount == 2) && node.isLeaf())
		    move(tree1, tree2);
	    }
        }

    }

    public void move(JTree src, JTree dst) {
	DblTreeNode node;

	TreePath selPath = src.getSelectionPath();
	if (selPath == null) // nothing selected (should be disabled)
	    return;
	else if (selPath.getPathCount() != 2)
	    return;
	else {
	    node = (DblTreeNode)selPath.getLastPathComponent();
	    moveLeaf(src, dst, node);

	    if (src == dstTree) {
		addItem.setEnabled(true);
		delItem.setEnabled(false);
		updateMoveButtons(node, false);
	    } else {
		addItem.setEnabled(false);
		delItem.setEnabled(true);
		updateMoveButtons(node, true);
	    }
	}

    }


    private int matchChild(JTree src,
	JTree dst,
	DblTreeNode srcNode,
	DblTreeNode newparent,
	Enumeration dstKids,
	int index) {

	DefaultTreeModel    srcModel = (DefaultTreeModel)src.getModel();
	DefaultTreeModel    dstModel = (DefaultTreeModel)dst.getModel();

	DblTreeNode dstNode = null;
	String srcString = srcNode.toString();
	while (dstKids.hasMoreElements()) {
	    String teststring;

	    dstNode = (DblTreeNode)dstKids.nextElement();
	    // if(dstNode.isLeaf() == false)
	    //	break;  // leaves come first
	    teststring = dstNode.toString();
	    if (teststring.compareTo(srcString) < 0) {
		index++;
		continue;
	    } else {
		break;
	    }
	}

	srcModel.removeNodeFromParent(srcNode);
	dstModel.insertNodeInto(srcNode, newparent, index);
	index++;
	return index;

    }

    public void moveLeaf(JTree src, JTree dst, DblTreeNode node) {

	if (node.isEnabled()) {
	    TreePath nodepath = new TreePath(node.getPath());
	    boolean expanded = src.isExpanded(nodepath);
	    initLeaf(src, dst, node);
	    nodepath = new TreePath(node.getPath());
	    dst.setSelectionPath(nodepath);

	    if (expanded)
		dst.expandPath(nodepath);
	}

    }


    public void initLeaf(JTree src, JTree dst, DblTreeNode node) {

	DefaultTreeModel    srcModel = (DefaultTreeModel)src.getModel();
	DefaultTreeModel    dstModel = (DefaultTreeModel)dst.getModel();
	DblTreeNode parent, newparent, clonedParent, root;
	int index = 0;
	root = (DblTreeNode)dstModel.getRoot();
	int limit = dstModel.getChildCount(root);

	if (dst == dstTree) {
	    srcModel.removeNodeFromParent(node);
	    dstModel.insertNodeInto(node, root, limit);
	} else {
	    Enumeration kids = root.children();
	    index = matchChild(src, dst, node, root, kids, index);
	}

	TreePath nodepath = new TreePath(node.getPath());
	dst.scrollPathToVisible(nodepath);
    }


    public void reorder(JTree dst, int delta) {

	DefaultTreeModel    dstModel = (DefaultTreeModel)dst.getModel();
	DblTreeNode dstRoot = (DblTreeNode)dstModel.getRoot();
	DblTreeNode node;

	TreePath selPath = dst.getSelectionPath();
	if (selPath == null) // nothing selected (should be disabled)
	    return;

	node = (DblTreeNode)selPath.getLastPathComponent();
	int index = dstModel.getIndexOfChild(dstRoot, node);
	int limit = dstModel.getChildCount(dstRoot);
	index += delta;

	if ((index < 0) || (index >= limit))
	    return;

	boolean expanded = dst.isExpanded(selPath);
	dst.clearSelection();

	dstModel.removeNodeFromParent(node);
	dstModel.insertNodeInto(node, dstRoot, index);

	TreePath nodepath = new TreePath(node.getPath());
	if (expanded)
	    dst.expandPath(nodepath);

	dst.setSelectionPath(nodepath);
	dst.scrollPathToVisible(nodepath);

	if (index > 0)
	    moveUpItem.setEnabled(true);
	else
	    moveUpItem.setEnabled(false);

	if (index < (limit - 1))
	    moveDownItem.setEnabled(true);
	else
	    moveDownItem.setEnabled(false);

    }

    /**
     * Set the focus listeners for the components in the selector panel that
     * can have unique help that may be context-specific.  Client apps
     * should call this method after the Arranger is created, but
     * before the dialog is shown.  Any of the listener arguments can be
     * null, if the client app can accept the default help for the particular
     * component.
     *
     * @param upButtonListener		listener for the move-up button
     * @param downButtonListener	listener for the move-down button
     * @see ContextHelpListener
     */
    public void setFocusListeners(
                FocusListener upButtonListener,
                FocusListener downButtonListener) {

        if (upButtonListener != null)
            moveUpItem.addFocusListener(upButtonListener);

        if (downButtonListener != null)
            moveDownItem.addFocusListener(downButtonListener);

    } // setFocusListeners

    public void resetModels() {
	srcTree.setModel(new DefaultTreeModel(new DblTreeNode("All Items")));
	dstTree.setModel(new DefaultTreeModel(new DblTreeNode("All Items")));
    }
}
