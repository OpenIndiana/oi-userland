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
 * Roles Panels for Roles settings
 *
 */
public class RolesPanel extends JPanel {

    public static SelPanel rolePanel;
    private static DblTreeNode srcRoot;
    private static DblTreeNode dstRoot;
    private DefaultTreeModel srcModel, dstModel;
    private DblTreeNode[] roleNodes;
    private RoleTreeNode[] roleTreeNodes;

    private UserManagedObject userObj = null;
    private UserMgrPanelDescriptor panelDesc = null;

    private boolean isRoleListOK = true;

    /**
     * Creates the Role Tab for the User.
     */
    public RolesPanel(UserMgrPanelDescriptor panelDesc,
		UserManagedObject userObj) {

	super();
	this.panelDesc = panelDesc;
	this.userObj = userObj;

	createGui();
	loadRoleTrees();

    } // end constructor

    private void createGui() {

	GridBagLayout gbl = new GridBagLayout();
	GridBagConstraints gbc = new GridBagConstraints();
	setLayout(gbl);

        // Excluded and Included rights panel
        rolePanel = new SelPanel("usermgr.advanced.roles.available",
		"usermgr.advanced.roles.assigned");

        rolePanel.srcTree.setCellRenderer(new RoleRenderer(this));
        rolePanel.dstTree.setCellRenderer(new RoleRenderer(this));

        Constraints.constrain(this, rolePanel,
            0, 0, 1, 1, gbc.BOTH, gbc.CENTER, 1.0, 1.0, 10, 10, 10, 10);

    } // end of CreateGui

    /**
     * Load the Source and Destination trees for rights excluded and
     * included lists.
     */
    private void loadRoleTrees() {

    	Vector<String> vAllRoleObjs = getAvailableRoles();

	rolePanel.resetModels();
	// For modifying a user:
	// Initialize the excluded rights list with all roles

	srcModel = (DefaultTreeModel) rolePanel.srcTree.getModel();
	srcRoot = (DblTreeNode) srcModel.getRoot();

	dstModel = (DefaultTreeModel) rolePanel.dstTree.getModel();
	dstRoot = (DblTreeNode) dstModel.getRoot();

	roleNodes = new DblTreeNode[vAllRoleObjs.size()];
	roleTreeNodes = new RoleTreeNode[vAllRoleObjs.size()];

	int n = 0;
	Enumeration e = vAllRoleObjs.elements();

	// Build an array of tree nodes that can be used for sorting.
	while (e.hasMoreElements()) {
	    String roleObj =  (String)e.nextElement();
	    String roleName = roleObj;
	    roleTreeNodes[n] = new RoleTreeNode(roleObj);
	    n++;
	}

	// Sort the list of RoleTreeNode objects.

	if (roleTreeNodes.length > 1) {
	    NodeCompare comp = new NodeCompare();
	    Sort.sort(roleTreeNodes, comp);
	}

	// With the sorted tree nodes, now we build the src tree.
	for (int i = 0; i < roleTreeNodes.length; i++) {

	    roleNodes[i] = new DblTreeNode((Object) roleTreeNodes[i]);

	    srcModel.insertNodeInto(roleNodes[i], srcRoot, i);
	    TreePath nodepath = new TreePath(roleNodes[i].getPath());

	    // Make initial display of excluded list
	    rolePanel.srcTree.scrollPathToVisible(nodepath);
	}

        String rolesStr = userObj.getRoles();
	if (rolesStr == null)
		return;

        String[] assignedRoles = userObj.getRoles().split(",");
        if (assignedRoles.length == 0) {
            return;
        }

        // Move roles of current user from excluded list
        // to included list.
        // Note that a dimmed role will stay dimmed after the move.
        // Therefore, a user can not "unassign" a dimmed role on the
        // included list.

        for (int i = 0; i < roleNodes.length; i++) {
            boolean foundRole = false;
            String roleString = roleNodes[i].toString();

            for (int j = 0; j < assignedRoles.length; j++) {
                if (roleString.equals(assignedRoles[j])) {
                    foundRole = true;
                    break;
                }
            }

            if (foundRole) {
                rolePanel.initLeaf(rolePanel.srcTree,
                    rolePanel.dstTree, roleNodes[i]);
            }
        }

    } // end loadRoleTrees

    private Vector<String> getAvailableRoles() {
        Vector<String> roles = new Vector<String>();
	for (String s : panelDesc.getRoles()) {
	    roles.add(s);

	}
    	return (roles);
    }

    public void setUser(UserManagedObject userObj) {
    	this.userObj = userObj;
	loadRoleTrees();
    }

    public UserManagedObject updateUser() {
        Vector<String> vRoles = getAssignedRoles();
	String rolesStr;

	if (vRoles.size() > 0) {
		rolesStr = vRoles.elementAt(0);
	} else {
		rolesStr = "";
	}

	for (int i = 1; i < vRoles.size(); i++) {
	    rolesStr = rolesStr.concat(",");
	    rolesStr = rolesStr.concat(vRoles.elementAt(i));
        }
	userObj.getRolesProperty().setValue(rolesStr);

	return (userObj);
    }

    /**
     * Get list of roles assigned to a user
     */
    public Vector<String> getAssignedRoles() {
	Vector<String> newRoles = new Vector<String>();

	if (isRoleListOK == false) {
	    return newRoles;
	}

        DblTreeNode root = (DblTreeNode) dstModel.getRoot();
        Enumeration kids;
        kids = root.children();

        while (kids.hasMoreElements()) {
            DblTreeNode childNode;
            childNode = (DblTreeNode)kids.nextElement();
            newRoles.addElement(childNode.toString());
        }

	return newRoles;
    }


    class RoleTreeNode {

        String name;
        String roleObj = null;

        public RoleTreeNode(String roleObj) {
            this.roleObj = roleObj;
            this.name = roleObj;
        }

        public String getRoleObj() {
            return roleObj;
        }

        public String toString() {
            return name;
        }
    }


    class NodeCompare implements Compare {

	/**
	 * The compare method compares two RoleTreeNode objects by comparing
	 * their role names.  The parameters are specified as Object class
	 * objects for QuickSort.
	 *
	 * @param a - The first Node.
	 * @param b - The second Node.
	 *
	 */
        public final int doCompare(Object a, Object b) {

            RoleTreeNode e1, e2;
            String e1Name, e2Name;

            e1 = (RoleTreeNode) a;
            e2 = (RoleTreeNode)b;
            e1Name = e1.toString();
            e2Name = e2.toString();
            return (e1Name.compareTo(e2Name));

        }

    }


    class RoleRenderer extends DefaultTreeCellRenderer {

        private boolean selected;
        RolesPanel rightSubProps;

        public RoleRenderer(RolesPanel rightSubProps) {

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

            } else if (node.getUserObject() instanceof RoleTreeNode) {
                RoleTreeNode rolesdef = (RoleTreeNode) node.getUserObject();
                setText(rolesdef.toString());

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

    } // RoleRenderer

} // RolesPanel
