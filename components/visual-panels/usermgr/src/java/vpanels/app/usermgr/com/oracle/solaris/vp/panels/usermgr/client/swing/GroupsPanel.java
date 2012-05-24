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
 * Copyright (c) 1998, 2012, Oracle and/or its affiliates. All rights reserved.
 */


package com.oracle.solaris.vp.panels.usermgr.client.swing;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;
import javax.swing.tree.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * SMC code adapted for Visual Panels
 *
 * Groups Panel for Groups settings
 */
public class GroupsPanel extends JPanel {

    public static SelPanel groupPanel;
    private static DblTreeNode srcRoot;
    private static DblTreeNode dstRoot;
    private DefaultTreeModel srcModel, dstModel;
    private DblTreeNode[] groupNodes;
    private GroupTreeNode[] groupTreeNodes;

    private UserManagedObject userObj = null;
    private UserMgrPanelDescriptor panelDesc = null;

    private boolean isGroupListOK = true;

    /**
     * Creates the Group Tab for the User.
     */
    public GroupsPanel(UserMgrPanelDescriptor panelDesc,
		UserManagedObject userObj) {

	super();
	this.panelDesc = panelDesc;
	this.userObj = userObj;

	createGui();
	loadGroupTrees();

    } // end constructor

    private void createGui() {

	GridBagLayout gbl = new GridBagLayout();
	GridBagConstraints gbc = new GridBagConstraints();
	setLayout(gbl);

        // Excluded and Included rights panel
        groupPanel = new SelPanel("usermgr.advanced.groups.available",
		"usermgr.advanced.groups.assigned");

        groupPanel.srcTree.setCellRenderer(new GroupRenderer(this));
        groupPanel.dstTree.setCellRenderer(new GroupRenderer(this));

        Constraints.constrain(this, groupPanel,
            0, 0, 1, 1, gbc.BOTH, gbc.CENTER, 1.0, 1.0, 10, 10, 10, 10);

    } // end of CreateGui

    /**
     * Load the Source and Destination trees for rights excluded and
     * included lists.
     */
    private void loadGroupTrees() {

    	Vector<String> vAllGroupObjs = getAvailableGroups();

	groupPanel.resetModels();
	// For modifying a user:
	// Initialize the excluded rights list with all groups

	srcModel = (DefaultTreeModel) groupPanel.srcTree.getModel();
	srcRoot = (DblTreeNode) srcModel.getRoot();

	dstModel = (DefaultTreeModel) groupPanel.dstTree.getModel();
	dstRoot = (DblTreeNode) dstModel.getRoot();

	groupNodes = new DblTreeNode[vAllGroupObjs.size()];
	groupTreeNodes = new GroupTreeNode[vAllGroupObjs.size()];

	int n = 0;
	Enumeration e = vAllGroupObjs.elements();

	// Build an array of tree nodes that can be used for sorting.
	while (e.hasMoreElements()) {
	    String groupObj =  (String)e.nextElement();
	    String groupName = groupObj;
	    groupTreeNodes[n] = new GroupTreeNode(groupObj);
	    n++;
	}

	// Sort the list of GroupTreeNode objects.

	if (groupTreeNodes.length > 1) {
	    NodeCompare comp = new NodeCompare();
	    Sort.sort(groupTreeNodes, comp);
	}

	// With the sorted tree nodes, now we build the src tree.
	for (int i = 0; i < groupTreeNodes.length; i++) {

	    groupNodes[i] = new DblTreeNode((Object) groupTreeNodes[i]);

	    srcModel.insertNodeInto(groupNodes[i], srcRoot, i);
	    TreePath nodepath = new TreePath(groupNodes[i].getPath());

	    // Make initial display of excluded list
	    groupPanel.srcTree.scrollPathToVisible(nodepath);
	}

        String groupsStr = userObj.getGroups();
	if (groupsStr == null)
		return;

        String[] assignedGroups = userObj.getGroups().split(",");
        if (assignedGroups.length == 0) {
            return;
        }

        // Move groups of current user from excluded list
        // to included list.
        // Note that a dimmed group will stay dimmed after the move.
        // Therefore, a user can not "unassign" a dimmed group on the
        // included list.

        for (int i = 0; i < groupNodes.length; i++) {
            boolean foundGroup = false;
            String groupString = groupNodes[i].toString();

            for (int j = 0; j < assignedGroups.length; j++) {
                if (groupString.equals(assignedGroups[j])) {
                    foundGroup = true;
                    break;
                }
            }

            if (foundGroup) {
                groupPanel.initLeaf(groupPanel.srcTree,
                    groupPanel.dstTree, groupNodes[i]);
            }
        }

    } // end loadGroupTrees

    private Vector<String> getAvailableGroups() {
        Vector<String> groups = new Vector<String>();
	for (String s : panelDesc.getSupplGroups()) {
	    groups.add(s);

	}
    	return (groups);
    }

    public void setUser(UserManagedObject userObj) {
    	this.userObj = userObj;
	loadGroupTrees();
    }

    public UserManagedObject updateUser() {
        Vector<String> vGroups = getAssignedGroups();
	String groupsStr;

	if (vGroups.size() > 0) {
		groupsStr = vGroups.elementAt(0);
	} else {
		groupsStr = "";
	}

	for (int i = 1; i < vGroups.size(); i++) {
	    groupsStr = groupsStr.concat(",");
	    groupsStr = groupsStr.concat(vGroups.elementAt(i));
        }
	userObj.getGroupsProperty().setValue(groupsStr);
	return (userObj);
    }

    /**
     */
    public Vector<String> getAssignedGroups() {
	Vector<String> newGroups = new Vector<String>();

	if (isGroupListOK == false) {
	    return newGroups;
	}

        DblTreeNode root = (DblTreeNode) dstModel.getRoot();
        Enumeration kids;
        kids = root.children();

        while (kids.hasMoreElements()) {
            DblTreeNode childNode;
            childNode = (DblTreeNode)kids.nextElement();
            newGroups.addElement(childNode.toString());
        }

	return newGroups;
    }


    class GroupTreeNode {

        String name;
        String groupObj = null;

        public GroupTreeNode(String groupObj) {
            this.groupObj = groupObj;
            this.name = groupObj;
        }

        public String getGroupObj() {
            return groupObj;
        }

        public String toString() {
            return name;
        }
    }


    class NodeCompare implements Compare {

	/**
	 * The compare method compares two GroupTreeNode objects by comparing
	 * their group names.  The parameters are specified as Object class
	 * objects for QuickSort.
	 *
	 * @param a - The first Node.
	 * @param b - The second Node.
	 *
	 */
        public final int doCompare(Object a, Object b) {

            GroupTreeNode e1, e2;
            String e1Name, e2Name;

            e1 = (GroupTreeNode) a;
            e2 = (GroupTreeNode)b;
            e1Name = e1.toString();
            e2Name = e2.toString();
            return (e1Name.compareTo(e2Name));

        }

    }


    class GroupRenderer extends DefaultTreeCellRenderer {

        private boolean selected;
        GroupsPanel rightSubProps;

        public GroupRenderer(GroupsPanel rightSubProps) {

	    this.rightSubProps = rightSubProps;
            setClosedIcon(null);
            setOpenIcon(null);
            setLeafIcon(null);

        }

        public Component getTreeCellRendererComponent(
            JTree tree,
            Object value,
            boolean selected,
            boolean expanded,
            boolean leaf,
            int row,
            boolean hasFocus) {

            this.selected = selected;

            DefaultTreeCellRenderer cr =
                (DefaultTreeCellRenderer) tree.getCellRenderer();
            cr.setLeafIcon(null);
            DblTreeNode node = (DblTreeNode) value;

            if (node.getParent() == null) {
                // maybe the same as row == 0
                setText(node.toString());

            } else if (node.getUserObject() instanceof GroupTreeNode) {
                GroupTreeNode groupsdef = (GroupTreeNode) node.getUserObject();
                setText(groupsdef.toString());

                if (selected) {
                    if (node.isEnabled()) {
                        cr.setTextSelectionColor(SystemColor.textText);
                    } else {
                        cr.setTextSelectionColor(
			    SystemColor.inactiveCaptionText);
		    }

                } else {
                    if (node.isEnabled()) {
                        cr.setTextNonSelectionColor(SystemColor.textText);
                    } else {

                        cr.setTextNonSelectionColor(
                        SystemColor.inactiveCaptionText);
                    }
                }
            }

            super.getTreeCellRendererComponent(tree, value, selected, expanded,
                leaf, row, hasFocus);

            return this;

        } // end getTreeCellRendererComponent

    } // GroupRenderer

} // GroupsPanel
