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

import javax.swing.tree.TreeNode;

class ModelRowData {
    //
    // Instance data
    //

    private TreeNode node;
    private int level;
    private boolean expanded = true;

    //
    // Constructors
    //

    public ModelRowData(TreeNode node, int level) {
	this.node = node;
	this.level = level;
    }

    //
    // ModelRowData methods
    //

    public boolean isExpanded() {
	return expanded;
    }

    public TreeNode getTreeNode() {
	return node;
    }

    public int getLevel() {
	return level;
    }

    public void setExpanded(boolean expanded) {
	this.expanded = expanded;
    }
}
