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
import javax.swing.tree.*;
import javax.swing.border.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * SMC code adapted for Visual Panels
 *
 * Rights Profiles Panel for Rights Settings
 */
public class RightsPanel extends JPanel {


    public static Arranger profPanel;
    private static DblTreeNode srcRoot;
    private static DblTreeNode dstRoot;
    private DefaultTreeModel srcModel, dstModel;

    private DblTreeNode [] profNodes;
    private ProfTreeNode [] profTreeNodes;

    private ProfTreeNode currProfTreeNode;
    private DblTreeNode currDblTreeNode;

    private String targetRightName;
    private String targetRight;
    private JPanel securityPanel;

    private UserManagedObject userObj = null;
    private UserMgrPanelDescriptor panelDesc = null;

    private Vector vAllRightObjs = null;

    private boolean isProfListOK = true;

    /**
     * Constructs a panel to contain supplementary rights properties for
     * the right object.
     */
    public RightsPanel(UserMgrPanelDescriptor panelDesc,
        UserManagedObject userObj) {

	super();
	this.panelDesc = panelDesc;
	this.userObj = userObj;

	createGui();
	loadProfiles();
    } // constructor


    /**
     * Method for creating GUI
     */
    private void createGui() {

	// Set the panel layout
	GridBagConstraints gbc = new GridBagConstraints();
	this.setLayout(new GridBagLayout());

	// Excluded and Included rights panel
   	securityPanel = null;

	profPanel = new Arranger("usermgr.advanced.rights.available",
		"usermgr.advanced.rights.granted");

	Dimension dimension = new Dimension(200, 300);
	profPanel.srcTree.setCellRenderer(new ProfileRenderer(this));
	profPanel.srcTree.setVisibleRowCount(10);
	profPanel.srcTree.setSize(dimension);

	profPanel.dstTree.setCellRenderer(new ProfileRenderer(this));
	profPanel.dstTree.setVisibleRowCount(10);
	profPanel.dstTree.setSize(dimension);

	Constraints.constrain(this, profPanel,
		0, 0, 1, 1,
		gbc.BOTH, gbc.CENTER,
		1.0, 1.0, 10, 10, 10, 10);

    } // end createGui


    /**
     * Load the Source and Destination trees for rights excluded and
     * included lists.
     */
    private void loadProfiles() {

	// Reset the data models. So old data is discarded
	profPanel.resetModels();


	// Initialize the excluded rights list with all profiles
	// except for the current one, since a profile can not be
	// assigned to itself. Note that all profiles are created
	// as top-level profiles.

	vAllRightObjs = getAvailableProfs();

	srcModel = (DefaultTreeModel) profPanel.srcTree.getModel();
	srcRoot = (DblTreeNode) srcModel.getRoot();

	dstModel = (DefaultTreeModel) profPanel.dstTree.getModel();
	dstRoot = (DblTreeNode) dstModel.getRoot();

	profNodes = new DblTreeNode[vAllRightObjs.size()];
	profTreeNodes = new ProfTreeNode[vAllRightObjs.size()];

	int n = 0;
	Enumeration e = vAllRightObjs.elements();

	// Build an array of tree nodes that can be used for sorting.

	while (e.hasMoreElements()) {
	    String rightObj = (String)e.nextElement();
	    String rightName = rightObj;

	    profTreeNodes[n] = new ProfTreeNode(rightObj);

	    n++;
	}

	// Sort the list of ProfTreeNode objects.

	if (profTreeNodes.length > 1) {
	    NodeCompare comp = new NodeCompare();
	    Sort.sort(profTreeNodes, comp);
	}

	// With the sorted tree nodes, now we build the src tree.
	for (int i = 0; i < profTreeNodes.length; i++) {
	    profNodes[i] = new DblTreeNode((Object)profTreeNodes[i]);

	    srcModel.insertNodeInto(profNodes[i], srcRoot, i);
	    TreePath nodepath = new TreePath(profNodes[i].getPath());
	    // Make initial display of excluded list
	    profPanel.srcTree.scrollPathToVisible(nodepath);
	}


	// Set TreeModel listeners
	srcModel.addTreeModelListener(new TreeModelListener() {

	    public void treeNodesInserted(TreeModelEvent e) {
		enableProfileChoices(e);
	    }

	    public void treeNodesRemoved(TreeModelEvent e) {
		disableProfileChoices(e);
	    }

	    public void treeNodesChanged(TreeModelEvent e) {}

	    public void treeStructureChanged(TreeModelEvent e) {}

	});

	dstModel.addTreeModelListener(new TreeModelListener() {

	    public void treeNodesInserted(TreeModelEvent e) {
		updateDstTree(e);
	    }

	    public void treeNodesRemoved(TreeModelEvent e) {
		updateDstTree(e);
	    }

	    public void treeNodesChanged(TreeModelEvent e) {}

	    public void treeStructureChanged(TreeModelEvent e) {}

	});

	// Build subprofiles recursively
	for (int i = 0; i < profNodes.length; i++) {
	    rebuildSubProfiles(profNodes[i], profNodes[i]);
	}

	String [] subProfList = null;

	// Get the list of profiles that are assigned to current user/role
	// (in user_attr entry).
	String rights = userObj.getRights();
	if (rights != null) {
	    subProfList = userObj.getRights().split(",");
	}

	profPanel.setInitSelection();
	if (rights == null || subProfList == null) {
	    return;
	}

	// Move subprofiles of current profile from excluded list
	// to included list.
	// Note that a dimmed profile will stay dimmed after the move.
	// Therefore, a user can not "unassign" a dimmed profile on the
	// included list.


	for (int j = 0; j < subProfList.length; j++) {
	    boolean foundSubProf = false;

	    int count = 0;
	    for (int i = 0; i < profNodes.length; i++) {
		String profString = profNodes[i].toString();

		if (profString.equals(subProfList[j])) {
		    foundSubProf = true;
		    count = i;
		    break;
		}

	    }

	    if (foundSubProf) {
		profPanel.initLeaf(profPanel.srcTree,
		    profPanel.dstTree, profNodes[count]);
	    }
	}

	profPanel.setInitSelection();

    } // end loadProfiles


    private void updateDstTree(TreeModelEvent e) {

	Vector<DblTreeNode> inclProfsVec = new Vector<DblTreeNode>();
	Enumeration inclProfsEnum = dstRoot.breadthFirstEnumeration();

	while (inclProfsEnum.hasMoreElements()) {
	    DblTreeNode node = (DblTreeNode)inclProfsEnum.nextElement();
	    inclProfsVec.addElement(node);
	    node.setConflict(false);
	}

	// Maintain included names as array as optimization

	DblTreeNode [] inclProfs = new DblTreeNode[inclProfsVec.size()];
	inclProfsVec.copyInto(inclProfs);

	if (inclProfs.length < 2)
	    return;

	for (int i = 0; i < inclProfs.length; i++) {
	    String testString = inclProfs[i].toString();

	    for (int j = i + 1; j < inclProfs.length; j++) {
		if (testString.equals(inclProfs[j].toString())) {
		    inclProfs[j].setConflict(true);
		    inclProfs[i].setConflict(true);
		    TreeNode [] nodes = inclProfs[j].getPath();
		    DblTreeNode parentProf = (DblTreeNode)nodes[1];
		    parentProf.setConflict(true);
		}
	    }
	}

    } // end updateDstTree


    private void enableProfileChoices(TreeModelEvent e) {

	// Get names of currently included profiles
	if (e.getPath().length > 1)
	    return;

	Vector<String> inclProfsVec = new Vector<String>();
	Enumeration inclProfs = dstRoot.depthFirstEnumeration();

	while (inclProfs.hasMoreElements()) {
	    inclProfsVec.addElement(inclProfs.nextElement().toString());
	}

	// Maintain included names as array as optimization

	String [] inclProfNames = new String[inclProfsVec.size()];
	inclProfsVec.copyInto(inclProfNames);

	// Look for excluded list items needing updating

	Enumeration topProfs = srcRoot.children();
	while (topProfs.hasMoreElements()) {
	    DblTreeNode nextTop = (DblTreeNode)topProfs.nextElement();
	    boolean matchFound = false;
	    Enumeration exclProfs = nextTop.depthFirstEnumeration();

	    while (exclProfs.hasMoreElements()) {
		String testString = exclProfs.nextElement().toString();
		for (int i = 0; i < inclProfNames.length; i++) {
		    if (testString.equals(inclProfNames[i])) {
			matchFound = true;
			break;
		    }
		}
		if (matchFound)
		    break;
	    }

	    // A Profile hierarchy needs to be enabled

	    if (!matchFound) {
		exclProfs = nextTop.depthFirstEnumeration();
		while (exclProfs.hasMoreElements()) {
		    DblTreeNode onNode =
			(DblTreeNode) exclProfs.nextElement();
		    onNode.setConflict(false);
		}
		nextTop.setConflict(false);
	    }
	}

    } // end enableProfileChoices


    private void disableProfileChoices(TreeModelEvent e) {

	if (e.getPath().length > 1)
	    return;

	Object[] children = e.getChildren();
	DblTreeNode node = (DblTreeNode)children[0];
	Enumeration kids = node.breadthFirstEnumeration();
	while (kids.hasMoreElements()) {
	    disableRecursively((DblTreeNode)kids.nextElement());
	}

    } // end disableProfileChoices


    private void disableRecursively(DblTreeNode node) {

	String testString = node.toString();
	Enumeration exclProfs = srcRoot.breadthFirstEnumeration();
	while (exclProfs.hasMoreElements()) {
	    DblTreeNode exclNode = (DblTreeNode)exclProfs.nextElement();
	    if (testString.equals(exclNode.toString())) {
		TreeNode [] nodes = exclNode.getPath();

		DblTreeNode parentProf = (DblTreeNode)nodes[1];
		if (!parentProf.isConflict()) {
		    parentProf.setConflict(true);
		    exclNode.setConflict(true);
    		}
	    }
	}

    } // end disableRecursively


    private void rebuildSubProfiles(DblTreeNode profNode, DblTreeNode topNode) {

	// First unlink the old children
	int childCount = profNode.getChildCount();
	for (int i = 0; i < childCount; i++) {
	    DblTreeNode child = (DblTreeNode) srcModel.getChild(profNode, 0);
	    srcModel.removeNodeFromParent(child);
	}

	// Then recursively construct new nodes for all the children
	DblTreeNode childNode;
	int i = 0;
	Enumeration topList = topNode.breadthFirstEnumeration();

	// Find sub-profile list in RightObj of cached tree node
	ProfTreeNode pTreeNode = (ProfTreeNode)profNode.getUserObject();
	String rObj = pTreeNode.getRightObj();
	// ProfAttrObj targetProfAttr = rObj.getProfAttr();

	String [] profList = null; // targetProfAttr.getProfNames();

	if (profList == null)
	    return;

	for (int k = 0; k < profList.length; k++) {
	    String name = profList[k];

	    // Prevent infinite recursive loops
	    boolean cyclic = false;
	    while (topList.hasMoreElements()) {
		if (name.equals(topList.nextElement().toString())) {
		    cyclic = true;
		    // Mark the parent as cyclic
		    topNode.setCyclic(true);
		    Enumeration dupNodes = topNode.breadthFirstEnumeration();
		    while (dupNodes.hasMoreElements()) {
			childNode = (DblTreeNode)dupNodes.nextElement();
			if (name.equals(childNode.toString())) {
			    childNode.setCyclic(true);
			}
		    }
		    break;
		}
	    }

	    for (int j = 0; j < profTreeNodes.length; j++) {
		if (name.equals(profTreeNodes[j].toString())) {
		    childNode = new DblTreeNode((Object)profTreeNodes[j]);

		    srcModel.insertNodeInto(childNode, profNode, i++);
		    childNode.setEnabled(false);
		    if (cyclic)
			childNode.setCyclic(true);
		    else
			rebuildSubProfiles(childNode, topNode);
		}
	    }
	}

    } // end rebuildSubProfiles


    public String updateRightSubProps(String rightObj) {

	if (isProfListOK) {
	    Vector<String> vAssignedProfs = new Vector<String>();

	    // Get the first generation children that are assigned to
	    // current profile.
	    DblTreeNode root = (DblTreeNode)dstModel.getRoot();
	    Enumeration kids;
	    kids = root.children();

	    while (kids.hasMoreElements()) {
		DblTreeNode childNode;
		childNode = (DblTreeNode)kids.nextElement();
		vAssignedProfs.addElement(childNode.toString());
	    }

	    // ProfAttrObj profAttr = rightObj.getProfAttr();
	    // profAttr.setProfNamesVector(vAssignedProfs);
	}
	return (rightObj);

    } // end updateRightSubProps

    public Vector<String> getAssignedProfs() {
	Vector<String> vAssignedProfs = new Vector<String>();

	if (!isProfListOK) {
	    return vAssignedProfs;
	}

	// Get the first generation children that are assigned to
	// current profile.
	DblTreeNode root = (DblTreeNode)dstModel.getRoot();
	Enumeration kids;
	kids = root.children();
	while (kids.hasMoreElements()) {
	    DblTreeNode childNode;
	    childNode = (DblTreeNode)kids.nextElement();
	    vAssignedProfs.addElement(childNode.toString());
	}

	return vAssignedProfs;
    }

    private Vector<String> getAvailableProfs() {
        Vector<String> rights = new Vector<String>();
	for (String s : panelDesc.getProfiles()) {
	    rights.add(s);

	}
    	return (rights);
    }

    public void setUser(UserManagedObject userObj) {
    	this.userObj = userObj;
	loadProfiles();
    }

    public UserManagedObject updateUser() {
        Vector<String> vProfs = getAssignedProfs();
	String profStr;

	if (vProfs.size() > 0) {
		profStr = vProfs.elementAt(0);
	} else {
		profStr = "";
	}

	for (int i = 1; i < vProfs.size(); i++) {
	    profStr = profStr.concat(",");
	    profStr = profStr.concat(vProfs.elementAt(i));
        }

	userObj.getRightsProperty().setValue(profStr);

	return (userObj);
    }
}


class ProfileRenderer extends DefaultTreeCellRenderer {

    private boolean selected;
    Icon warningIcon;
    static RightsPanel rightsPanel;

    public ProfileRenderer(RightsPanel rightsPanel) {

	this.rightsPanel = rightsPanel;
	setClosedIcon(null);
	setOpenIcon(null);
	setLeafIcon(null);
    	warningIcon = Finder.getIcon("images/warning.gif");

    }


    public Component getTreeCellRendererComponent(
	JTree tree,
	Object value,
	boolean selected,
	boolean expanded,
	boolean leaf,
	int row,
	boolean hasFocus) {

	FocusEvent e = null;

	this.selected = selected;

	DefaultTreeCellRenderer cr =
	    (DefaultTreeCellRenderer)tree.getCellRenderer();
	cr.setLeafIcon(null);
	DblTreeNode node = (DblTreeNode)value;

	if (node.getParent() == null) {
	    // maybe the same as row == 0
	    setText(node.toString());

	} else if (node.getUserObject() instanceof ProfTreeNode) {
	    ProfTreeNode profsdef = (ProfTreeNode)node.getUserObject();
	    setText(profsdef.toString());
	    // setIcon(actionIcon);

	    if (node.isConflict())
		if (tree == rightsPanel.profPanel.dstTree)
		    cr.setLeafIcon(warningIcon);
	}

	super.getTreeCellRendererComponent(tree, value, selected, expanded,
	    leaf, row, hasFocus);

	return this;

    } // end getTreeCellRendererComponent

}

class ProfTreeNode {

    String name;
    String rightObj = null;

    public ProfTreeNode(String rightObj) {
	this.rightObj = rightObj;
	this.name = rightObj;
    }

    public String getRightObj() {
	return rightObj;
    }

    public String toString() {
	return name;
    }

}

class NodeCompare implements Compare {

    /**
     * The compare method compares two ProfTreeNode objects by comparing
     * their profile names.  The parameters are specified as Object class
     * objects for QuickSort.
     *
     * @param   a	The first Node.
     * @param   b	The second Node.
     *
     */
    public final int doCompare(Object a, Object b) {

	ProfTreeNode e1, e2;
	String e1Name, e2Name;

	e1 = (ProfTreeNode)a;
	e2 = (ProfTreeNode)b;
	e1Name = e1.toString();
	e2Name = e2.toString();
	return (e1Name.compareTo(e2Name));

    }

}
