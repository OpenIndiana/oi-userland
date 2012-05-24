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
import javax.accessibility.*;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.util.*;
import java.io.*;

import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * SMC code adapted for Visual Panels
 *
 * Selection Panel incorpoarting exclude/include trees
 */
public class SelPanel extends DoubleTrees {

    public SelPanel() {

	setListeners();

    }

    public SelPanel(String srcHeader, String dstHeader) {

	super(srcHeader, dstHeader);
	setListeners();

    }

    /**
     * Create any dynamic images we need.
     */
    public void addNotify() {

	super.addNotify();

	delItem.setIcon(Finder.getIcon("images/remove.png"));
	delItem.setHorizontalTextPosition(JButton.RIGHT);

	delAllItem.setIcon(Finder.getIcon("images/remove_all.png"));
	delAllItem.setHorizontalTextPosition(JButton.RIGHT);

	addItem.setIcon(Finder.getIcon("images/add.png"));
	addItem.setHorizontalTextPosition(JButton.LEFT);

	addAllItem.setIcon(Finder.getIcon("images/add_all.png"));
	addAllItem.setHorizontalTextPosition(JButton.LEFT);

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

	addAllItem.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		moveAll(srcTree, dstTree);
	    }
	});

	delAllItem.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		moveAll(dstTree, srcTree);
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

    private void handleMouse(MouseEvent e) {

	JTree  tree1, tree2;

	if (e.getSource() == srcTree) {
	    tree1 = srcTree;
	    tree2 = dstTree;
	    addItem.setEnabled(true);
	    delItem.setEnabled(false);
	} else {
	    tree1 = dstTree;
	    tree2 = srcTree;
	    addItem.setEnabled(false);
	    delItem.setEnabled(true);
	}
	TreePath selPath = tree1.getPathForLocation(e.getX(), e.getY());

	if (selPath != null) {
	    tree2.clearSelection();
	    int selCount = selPath.getPathCount();
	    DblTreeNode node = (DblTreeNode)selPath.getLastPathComponent();
	    if (e.getClickCount() == 1) {
		// mySingleClick(tree1, selPath);
	    } else if (e.getClickCount() == 2) {
		if (node.isLeaf())
		    move(tree1, tree2);
	    }
	}

    }


    public void move(JTree src, JTree dst) {

	DblTreeNode node;

	TreePath selPath = src.getSelectionPath();
	if (selPath == null) // nothing selected (should be disabled)
	    return;
	else if (selPath.getPathCount() == 1)
	    moveAll(src, dst);
	else {
	    node = (DblTreeNode)selPath.getLastPathComponent();

	    if (node.isLeaf()) {
		moveLeaf(src, dst, node);
	    } else {  // node is branch
		moveBranch(src, dst, node, true, true);
	    }

	    if (src == srcTree) {
		addItem.setEnabled(false);
		delItem.setEnabled(true);
	    } else {
		addItem.setEnabled(true);
		delItem.setEnabled(false);
	    }
	}

    }


    private SelPTreeNode matchParent(
	DblTreeNode parent,
	DblTreeNode root,
	DefaultTreeModel dstModel) {

	Enumeration kids;
	SelPTreeNode treeNode = new SelPTreeNode();
	int level = parent.getLevel();
	if (level == 0) {
	    treeNode.newparent = root;
	    return treeNode;
	}

	DblTreeNode [] nodes = new DblTreeNode[level];
	nodes[level - 1] = parent;
	for (int i = nodes.length; i > 1; i--) {
	    nodes [i - 2] = (DblTreeNode) nodes[i - 1].getParent();
	}

	for (int i = 0; i < nodes.length; i++) {
	    treeNode.newparent = null;
	    treeNode.index = 0;
	    String parentString = nodes[i].toString();
	    kids = root.children();
	    while (kids.hasMoreElements()) {
		DblTreeNode testnode;
		String teststring;
		int diff;

		testnode = (DblTreeNode)kids.nextElement();

		diff = testnode.compareTo(nodes[i]);

		if (diff == 0) { // matching branch
		    treeNode.newparent = testnode;
		    break;
		} else if (testnode.isLeaf()) {
		    treeNode.index++;
		    continue;
		} else if (diff < 0) {
		    treeNode.index++;
		    continue;
		} else {
		    break;
		}
	    }

	    if (treeNode.newparent != null) {
		root = treeNode.newparent;
	    } else {
		DblTreeNode newNode = (DblTreeNode)nodes[i].clone();
		dstModel.insertNodeInto(newNode, root, treeNode.index);
		treeNode.newparent = newNode;
		root = newNode;
	    }
	}
	return treeNode;

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
	    if (dstNode.isLeaf() == false)
		break;  // leaves come first
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

    public void moveBranch(JTree src, JTree dst, DblTreeNode parent,
      boolean top, boolean select) {
	initBranch(src, dst, parent, top, select, false);
    }

    public void initBranch(JTree src, JTree dst, DblTreeNode parent,
	boolean top, boolean select, boolean force) {

	DefaultTreeModel    srcModel = (DefaultTreeModel)src.getModel();
	DefaultTreeModel    dstModel = (DefaultTreeModel)dst.getModel();
	DblTreeNode newparent, clonedParent, root;

	root = (DblTreeNode)dstModel.getRoot();

	DblTreeNode [] kidsArray = new DblTreeNode[parent.getChildCount()];
	Enumeration kids = parent.children();
	int i = 0;
	while (kids.hasMoreElements()) {
	    kidsArray[i++] = (DblTreeNode)kids.nextElement();
	}
	int index = 0;

	// find same branch in destination tree
	SelPTreeNode treeNode = matchParent(parent, root, dstModel);
	newparent = treeNode.newparent;

	// add all the kids
	// At this point we know there is at least one child of dst parent

	for (i = 0; i < kidsArray.length; i++) {
	    DblTreeNode srcNode = kidsArray[i];

	    if (srcNode.isLeaf() == false) {
		initBranch(src, dst, srcNode, false, false, force);
		continue;
	    }
	    if (force == false && srcNode.isEnabled() == false)
		continue;

	    Enumeration dstKids = newparent.children();
	    index = matchChild(src, dst, srcNode, newparent, dstKids, 0);
	}

	if (parent.isRoot() == false)
	    while (parent.getChildCount() == 0) {
		DblTreeNode grandParent;
		grandParent = (DblTreeNode) parent.getParent();
		srcModel.removeNodeFromParent(parent);
		if (grandParent == null || grandParent.isRoot())
		    break;
		else
		    parent = grandParent;
	    }

	if (newparent.getChildCount() == 0) {
	    if (top)
		while (newparent.getChildCount() == 0) {
		    DblTreeNode grandParent;
		    grandParent = (DblTreeNode) newparent.getParent();
		    dstModel.removeNodeFromParent(newparent);
		    if (grandParent == null || grandParent.isRoot())
			break;
		    else
			newparent = grandParent;
		}
	    else
		dstModel.removeNodeFromParent(newparent);
	} else if (select) {
	    TreePath nodepath = new TreePath(newparent.getPath());

	    dst.expandPath(nodepath);
	    // dst.makeVisible(nodepath);
	    dst.setSelectionPath(nodepath);
	    dst.scrollPathToVisible(nodepath);
	}

    }


    public void moveLeaf(JTree src, JTree dst, DblTreeNode node) {

	if (node.isEnabled())
	    initLeaf(src, dst, node);
	TreePath nodepath = new TreePath(node.getPath());
	dst.setSelectionPath(nodepath);

    }


    public void initLeaf(JTree src, JTree dst, DblTreeNode node) {

	DefaultTreeModel    srcModel = (DefaultTreeModel)src.getModel();
	DefaultTreeModel    dstModel = (DefaultTreeModel)dst.getModel();
	DblTreeNode parent, newparent, clonedParent, root;
	int index = 0;
	root = (DblTreeNode)dstModel.getRoot();

	// find parent
	parent = (DblTreeNode)node.getParent();

	// find same branch in destination tree

	SelPTreeNode treeNode = matchParent(parent, root, dstModel);
	newparent = treeNode.newparent;

	Enumeration kids = newparent.children();
	index = matchChild(src, dst, node, newparent, kids, index);
	TreePath nodepath = new TreePath(node.getPath());

	dst.expandPath(nodepath);
	dst.scrollPathToVisible(nodepath);

	// check for last child
	while ((parent.isRoot() == false)
	    && parent.getChildCount() == 0) {
	    DblTreeNode grandParent;
	    grandParent = (DblTreeNode) parent.getParent();
	    srcModel.removeNodeFromParent(parent);
	    if (grandParent == null)
		break;
	    else
		parent = grandParent;
	}

    }


    public void moveAll(JTree src, JTree dst) {

	DefaultTreeModel    srcModel = (DefaultTreeModel)src.getModel();
	DblTreeNode srcRoot = (DblTreeNode)srcModel.getRoot();

	src.clearSelection();
	Enumeration kids = srcRoot.children();
	DblTreeNode [] kidsArray = new DblTreeNode[srcRoot.getChildCount()];
	int i = 0;
	while (kids.hasMoreElements()) {
	    kidsArray[i++] = (DblTreeNode)kids.nextElement();
	}

	for (i = 0; i < kidsArray.length; i++) {
	    if (kidsArray[i].isLeaf())
		moveLeaf(src, dst, kidsArray[i]);
	    else
		moveBranch(src, dst, kidsArray[i], true, false);

	}
	DblTreeNode dstRoot = (DblTreeNode)dst.getModel().getRoot();
	if (dstRoot.getChildCount() > 0) {
	    DblTreeNode child = (DblTreeNode)dstRoot.getFirstChild();
	    TreePath nodepath = new TreePath(child.getPath());
	    dst.setSelectionPath(nodepath);
	    dst.scrollPathToVisible(nodepath);
	}

	if (src == srcTree) {
	    addItem.setEnabled(false);
	    delItem.setEnabled(true);
	} else {
	    addItem.setEnabled(true);
	    delItem.setEnabled(false);
	}
    }


    public boolean findNode(String findStr) {

	DblTreeNode root;
	DblTreeNode otherRoot;
	DblTreeNode currentNode;
	JTree currentTree;
	JTree otherTree;
	Enumeration searchNodes;
	DefaultTreeModel    srcModel = (DefaultTreeModel)srcTree.getModel();
	DefaultTreeModel    dstModel = (DefaultTreeModel)dstTree.getModel();

	TreePath selPath = srcTree.getSelectionPath();
	if (selPath == null) { // Try the other tree
	    selPath = dstTree.getSelectionPath();
	    if (selPath == null) { // Start at the upper left
		return false;
	    }
	    currentTree = dstTree;
	    otherTree = srcTree;
	    root = (DblTreeNode)dstModel.getRoot();
	    otherRoot = (DblTreeNode)srcModel.getRoot();

	} else {
	    currentTree = srcTree;
	    otherTree = dstTree;
	    root = (DblTreeNode)srcModel.getRoot();
	    otherRoot = (DblTreeNode)dstModel.getRoot();
	}

	currentNode = (DblTreeNode)selPath.getLastPathComponent();

	searchNodes = myRowFirstEnumeration(root, null);
	Vector<DblTreeNode> fromTop = new Vector<DblTreeNode>();
	while (searchNodes.hasMoreElements()) {
	    DblTreeNode node = (DblTreeNode) searchNodes.nextElement();

	    if (node == currentNode) {
		while (searchNodes.hasMoreElements()) {
		    node = (DblTreeNode) searchNodes.nextElement();
		    String nodeStr = node.toString();
		    if (nodeStr.lastIndexOf(findStr) != -1) {
			TreePath nodepath = new TreePath(node.getPath());
			currentTree.expandPath(nodepath);
			currentTree.setSelectionPath(nodepath);
			currentTree.scrollPathToVisible(nodepath);
			return true;
		    }
		}
	    } else {
		fromTop.addElement(node);
		continue;
	    }
	}

	// Not found in remainder of current tree...

	searchNodes = myRowFirstEnumeration(otherRoot, null);
	while (searchNodes.hasMoreElements()) {
	    DblTreeNode node = (DblTreeNode) searchNodes.nextElement();
	    String nodeStr = node.toString();
	    if (nodeStr.lastIndexOf(findStr) != -1) {
		currentTree.clearSelection();
		TreePath nodepath = new TreePath(node.getPath());
		otherTree.expandPath(nodepath);
		otherTree.setSelectionPath(nodepath);
		otherTree.scrollPathToVisible(nodepath);

		// Switch buttons

		if (otherTree == srcTree) {
		    addItem.setEnabled(true);
		    delItem.setEnabled(false);
		} else {
		    addItem.setEnabled(false);
		    delItem.setEnabled(true);
		}
	    return true;
	    }
	}

	// Not found in other tree
	// Try from top of current tree...

	searchNodes = fromTop.elements();
	while (searchNodes.hasMoreElements()) {
	    DblTreeNode node = (DblTreeNode) searchNodes.nextElement();
	    String nodeStr = node.toString();
	    if (nodeStr.lastIndexOf(findStr) != -1) {
		TreePath nodepath = new TreePath(node.getPath());
		currentTree.expandPath(nodepath);
		currentTree.setSelectionPath(nodepath);
		currentTree.scrollPathToVisible(nodepath);
		return true;
	    } else
		continue;
	}
	// Not found in current tree...
	return false;

    }

    private Enumeration myRowFirstEnumeration(DblTreeNode root,
    	Vector<DblTreeNode> v) {

	if (v == null)
	    v = new Vector<DblTreeNode>();
	Enumeration kids = root.children();
	while (kids.hasMoreElements()) {
	    DblTreeNode node = (DblTreeNode)kids.nextElement();
	    v.addElement(node);
	    Enumeration gkids = myRowFirstEnumeration(node, v);
	}
	return v.elements();

    }


    public void refreshTrees() {

	JTree currentTree;
	JTree dummyTree;
	TreePath selPath = srcTree.getSelectionPath();
	if (selPath == null) {
	    selPath = dstTree.getSelectionPath();
	    if (selPath == null)
		return;
	    currentTree = dstTree;
	} else {
	    currentTree = srcTree;
	}

	DefaultTreeModel treeModel =
	    new DefaultTreeModel(new DblTreeNode("dummy"));
	dummyTree = new JTree(treeModel);

	moveAll(srcTree, dummyTree);
	moveAll(dummyTree, srcTree);
	moveAll(dstTree, dummyTree);
	moveAll(dummyTree, dstTree);

	if (currentTree == srcTree) {
	    addItem.setEnabled(true);
	    delItem.setEnabled(false);
	    dstTree.setSelectionPath(selPath);
	} else {
	    addItem.setEnabled(false);
	    delItem.setEnabled(true);
	    srcTree.setSelectionPath(selPath);
	}

    }

    public void resetAll() {

	DblTreeNode srcRoot = (DblTreeNode)srcTree.getModel().getRoot();
	DblTreeNode dstRoot = (DblTreeNode)dstTree.getModel().getRoot();

	dstTree.clearSelection();
	Enumeration kids = dstRoot.children();
	DblTreeNode [] kidsArray = new DblTreeNode[dstRoot.getChildCount()];
	int i = 0;
	while (kids.hasMoreElements()) {
	    kidsArray[i++] = (DblTreeNode)kids.nextElement();
	}

	for (i = 0; i < kidsArray.length; i++) {
	    if (kidsArray[i].isLeaf())
		initLeaf(dstTree, srcTree, kidsArray[i]);
	    else
		initBranch(dstTree, srcTree, kidsArray[i], true, false, true);

	}
	if (srcRoot.getChildCount() > 0) {
	    DblTreeNode child = (DblTreeNode)srcRoot.getFirstChild();
	    TreePath nodepath = new TreePath(child.getPath());
	    srcTree.setSelectionPath(nodepath);
	    srcTree.scrollPathToVisible(nodepath);
	}

	addItem.setEnabled(true);
	delItem.setEnabled(false);
    }

    public void resetModels() {
	srcTree.setModel(new DefaultTreeModel(new DblTreeNode("All Items")));
	dstTree.setModel(new DefaultTreeModel(new DblTreeNode("All Items")));
    }
}

class SelPTreeNode {

    DblTreeNode newparent;
    int index;

    public SelPTreeNode() {
	newparent = null;
	index = 0;
    }
}
