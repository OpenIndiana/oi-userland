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
import javax.swing.border.*;
import javax.swing.tree.*;

import java.util.List;
import java.util.*;
import java.io.*;
import java.net.*;

import java.awt.*;
import java.awt.event.*;

import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * SMC code adapted for Visual Panels
 *
 * Authorization Settings Panel
 */

public class AuthsPanel extends JPanel {

    private UserManagedObject userObj = null;
    private UserMgrPanelDescriptor panelDesc = null;

    private AuthAttrMgmt authAttrMgmt;
    private AuthAttrModelEntry[] authArr;
    private DblTreeNode root;

    public static SelPanel authPanel;
    private DblTreeNode [] authNode;

    private boolean isNew;
    private boolean viewNames = false;

    /**
     * Constructs a panel to contain authorizations properties for the
     * right object.
     *
     */
    public AuthsPanel(UserMgrPanelDescriptor panelDesc,
		UserManagedObject userObj) {
	super();
	this.panelDesc = panelDesc;
        this.userObj = userObj;
	isNew = userObj.isNewUser();

	createGui();
	loadAuths();

    } // constructor

    /**
     * Method for creating GUI
     */
    private void createGui() {

	// set the panel layout
	GridBagLayout gridbag = new GridBagLayout();
	GridBagConstraints gbc = new GridBagConstraints();
	this.setLayout(gridbag);

	authPanel = new SelPanel("usermgr.advanced.auths.available",
		"usermgr.advanced.auths.granted");

	authPanel.srcTree.setCellRenderer(new AuthRenderer(this));
	authPanel.dstTree.setCellRenderer(new AuthRenderer(this));

	Constraints.constrain(this, authPanel,
	    0, 0, 1, 1, gbc.BOTH, gbc.CENTER, 1.0, 1, 10, 10, 10, 10);
    } // end createGui

    public void loadUserAuths() {
	authPanel.resetAll();

	if (isNew == false) {
	    authAttrMgmt = new AuthAttrMgmt(panelDesc, userObj);
	    authArr = authAttrMgmt.getAuthEntries();
	    setAuthArr(authArr);
        }

	if (authArr == null) {
	    return;
	}


	// At this point, everything is in the left tree, with
	// all of the branches collaped.

	for (int i = 0; i < authArr.length; i++) {
	    if (authArr[i].isHeader()) {

		// Expand all the headers

		TreePath nodepath = new TreePath(authNode[i].getPath());
		authPanel.srcTree.expandPath(nodepath);
	    } else {

		// Move all the granted auths leaves to the right
		if (isNew == false && authArr[i].isGranted()) {
		    authPanel.initLeaf(authPanel.srcTree, authPanel.dstTree,
		    authNode[i]);
		}
	    }
	}

	authPanel.srcTree.setRootVisible(false);
	authPanel.setInitSelection();
    }

    /**
     * Load the Source and Destination trees for authorizations excluded and
     * included lists.
     */
    private void loadAuths() {

	// Reset the data models. So old data is discarded
	authPanel.resetModels();

	DefaultTreeModel srcModel =
	    (DefaultTreeModel)authPanel.srcTree.getModel();
	root = (DblTreeNode)srcModel.getRoot();
	int topCount = 0;
	int headerCount = 0;

	// First time through use a dummy profile
	authAttrMgmt = new AuthAttrMgmt(panelDesc, userObj);

	authArr = authAttrMgmt.getAuthEntries();

	int [] headerList = new int[authArr.length];
	authNode = new DblTreeNode[authArr.length];

	for (int i = 0; i < authArr.length; i++) {
	    AuthTreeNode authObject = new AuthTreeNode(authArr[i], i);
	    authNode[i] = new DblTreeNode((Object)authObject);

	    String nodeName = authArr[i].getAuthName();
	    if (authArr[i].isHeader()) {
		// Add subheaders to headers

		boolean foundHeader = false;
		int	headerIndex = 0;

		for (int j = 0; j < headerCount; j++) {
		    int k = headerList[j];
		    AuthTreeNode  headerNode =
			(AuthTreeNode)authNode[k].getUserObject();
		    String headerName = headerNode.toString();
		    if (nodeName.startsWith(headerName)) {
			foundHeader = true;
			headerIndex = k;
			// loop for closest match
		    }
		}

		if (foundHeader) {
		    authNode[headerIndex].add(authNode[i]);
		} else {
		    srcModel.insertNodeInto(authNode[i], root, topCount++);
		    TreePath nodepath = new TreePath(authNode[i].getPath());
		    authPanel.srcTree.scrollPathToVisible(nodepath);
		}
		// add header to header list
		headerList[headerCount++] = i;

	    } else { // Add the leaves to the headers

		// Set auth's treenode disabled to
		// indicate the auth "can not be granted" to another user
		// (No auths leaves could ever have child nodes)

		if (authArr[i].canBeGranted() == false) {
		    authNode[i].setEnabled(false);
		}
		if (headerCount > 0) {
		    for (int j = headerCount - 1; j >= 0; j--) {
			AuthTreeNode  headerNode = (AuthTreeNode)
			    authNode[headerList[j]].getUserObject();
			String headerName = headerNode.toString();
			if (nodeName.startsWith(headerName)) {
			    authNode[headerList[j]].add(authNode[i]);
			    break;
			}
		    }
		} else {
		    srcModel.insertNodeInto(authNode[i], root, topCount++);
		}
	    }
	}

	loadUserAuths();

    } // end loadAuths


    public void setAuthArr(AuthAttrModelEntry[] arr) {
	authArr = arr;
    }

    public AuthAttrModelEntry[] getAuthArr() {
	return authArr;
    }

    public boolean getViewNames() {
	return viewNames;
    }


    public void getChecks() {

	AuthAttrModelEntry[] authEntryArr = getAuthArr();

	if (authNode == null) {
	    return;
        }

	for (int i = 0; i < authNode.length; i++) {
	    if (authEntryArr[i].isHeader()) {
		authEntryArr[i].grant();
		continue;
	    }

	    // root is in the excluded tree.
	    if (authNode[i].getRoot().equals(root))
		authEntryArr[i].revoke();
	    else
		authEntryArr[i].grant();
	}

	DblTreeNode node;
	Enumeration inclAuths = root.depthFirstEnumeration();
	while (inclAuths.hasMoreElements()) {
	    node = (DblTreeNode)inclAuths.nextElement();
	    if (node.isRoot())
		continue;

	    AuthTreeNode authtreenode = (AuthTreeNode)node.getUserObject();
	    int i = authtreenode.getSubscript();
	    if (authEntryArr[i].isHeader())
		authEntryArr[i].revoke();
	}

	setAuthArr(authEntryArr);

    } // end getChecks

    /**
     * Get the authorizations assigned to the selected user/role.
     */
    public Vector<String> getAssignedAuths() {
	getChecks();
        Vector<String> vAuths = authAttrMgmt.setAuthEntries(getAuthArr());

	return vAuths;
    }

    /**
     * Get a list of available authorizations that can be assigned
     * to selected user/role.
     */
    private String[] getAvailableAuths() {
	List<String> auths = panelDesc.getAuths();
        int authsize =  auths.size();
	String[] authList = new String[authsize];

	for (int i = 0; i < authsize; i++) {
	    authList[i] = auths.get(i);
	}
    	return (authList);
    }

    /**
     * Refresh authorizations for the new user.
     */
    public void setUser(UserManagedObject userObj) {
    	this.userObj = userObj;
	loadAuths();
    }

    public UserManagedObject updateUser() {
        Vector<String> vAuths = getAssignedAuths();
	String authStr;

	if (vAuths.size() > 0) {
		authStr = vAuths.elementAt(0);
	} else {
		authStr = "";
	}

	for (int i = 1; i < vAuths.size(); i++) {
	    authStr = authStr.concat(",");
	    authStr = authStr.concat(vAuths.elementAt(i));
        }

	userObj.getAuthsProperty().setValue(authStr);

	return (userObj);
    }

} // end AuthsPanel

class AuthTreeNode {

    String name = null;
    AuthAttrModelEntry authModel = null;
    boolean enabled = true;
    int subscript;

    public AuthTreeNode(AuthAttrModelEntry authModel, int subscript) {
	name = authModel.getName();
	enabled = authModel.canBeGranted();
	this.authModel = authModel;
	this.subscript = subscript;
    }

    public String getDesc() {
	return authModel.getDesc();
    }

    public String toString() {
	return name;
    }

    public AuthAttrModelEntry getAuthModel() {
	return authModel;
    }

    public boolean isEnabled() {
	return enabled;
    }

    public int getSubscript() {
	return this.subscript;
    }

}

class AuthRenderer extends DefaultTreeCellRenderer {

    private boolean selected;
    static AuthsPanel authsPanel;

    public AuthRenderer(AuthsPanel authsPanel) {
	this.authsPanel = authsPanel;
	setClosedIcon(null);
	setOpenIcon(null);
    }

    public Component getTreeCellRendererComponent(
	JTree tree,
	Object value,
	boolean selected,
	boolean expanded,
	boolean leaf,
	int row,
	boolean hasFocus) {

	AuthTreeNode authdef = null;
	FocusEvent e = null;

	this.selected = selected;

	DefaultTreeCellRenderer cr =
	    (DefaultTreeCellRenderer)tree.getCellRenderer();

	DblTreeNode node = (DblTreeNode)value;
	// authdef = (AuthTreeNode)node.getUserObject();

	if (node.getParent() == null) {
	    setText("All Authorizations");
	} else  if (node.getUserObject() instanceof AuthTreeNode) {
	    authdef = (AuthTreeNode)node.getUserObject();
	    setText(authdef.toString());

	}

	super.getTreeCellRendererComponent(tree, value,
		selected, expanded, leaf, row, hasFocus);

	return this;

    }
}
