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

package com.oracle.solaris.vp.panel.swing.view;

import javax.swing.tree.TreeNode;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.common.propinfo.PropInfo;
import com.oracle.solaris.vp.util.swing.tree.AbstractTreeTableModel;

@SuppressWarnings({"serial"})
public class ManagedObjectTreeTableModel extends AbstractTreeTableModel {
    //
    // Instance data
    //

    private ManagedObject<?> pObject;

    //
    // Constructors
    //

    public ManagedObjectTreeTableModel(ManagedObject<?> pObject,
	PropInfo<ManagedObject, ?>[] props) {

	super(new ManagedObjectTreeNode(pObject), props);

	this.pObject = pObject;

	((ManagedObjectTreeNode)getRoot()).addTreeModelListener(this);
    }

    //
    // AbstractTreeTableModel methods
    //

    @Override
    protected ManagedObject getUserObject(TreeNode node) {
	return ((ManagedObjectTreeNode)node).getUserObject();
    }

    //
    // ManagedObjectTreeTableModel methods
    //

    public ManagedObject getParentObject() {
	return pObject;
    }

    @SuppressWarnings({"unchecked"})
    public boolean isCellEnabled(TreeNode node, int column) {
	Object o = getUserObject(node);
	PropInfo prop = getPropInfos()[column];
	return prop.isEnabled(o);
    }
}
