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
import javax.swing.tree.*;

/**
 * SMC code adapted for Visual Panels
 */
public class DblTreeNode extends DefaultMutableTreeNode implements Comparable {

    boolean enabled = true;
    boolean cyclic = false;
    boolean conflict = false;

    /**
     * The comparableObject is used when comparing two
     * DblTreeNode objects. By default the String
     * representation (toString()) is used when comparing
     * DblTreeNode objects. This may not always give the
     * desired ordering when displaying nodes in a list. To overcome this
     * when the comparableObject is not null
     * the String representation of the
     * comparableObject is used. This could be as simple as an
     * Integer.
     */
    private Object comparableObject;

    public DblTreeNode() {
	super();
    }

    public DblTreeNode(Object object) {
	super(object);
    }

    public DblTreeNode(String string) {
	super(string);
    }

    public boolean isEnabled() {
	return enabled;
    }

    public void setEnabled(boolean flag) {
	enabled = flag;
    }

    public boolean isCyclic() {
	return cyclic;
    }

    public void setCyclic(boolean flag) {
	cyclic = flag;
    }

    public boolean isConflict() {
	return conflict;
    }

    public void setConflict(boolean flag) {
	conflict = flag;
    }

    /**
     * Set the <code>comparableObject</code> which will be used by
     * the <code>compareTo()</code> method. Use <code>null</code> to
     * use <code>this</code> object (default).
     *
     * @param comparableObject
     *	Object used by <code>compareTo()</code>
     */
    public void setComparableObject(Object comparableObject) {
	this.comparableObject = comparableObject;
    }

    /**
     * Get the <code>comparableObject</code> which will be used by
     * the <code>compareTo()</code> method. This method never returns
     * <code>null</code>. If the <code>comparableObject</code> is set to
     * <code>null</code> by <code>setComparableObject(null)</code> this
     * method returns <code>this</code>.
     *
     * @return
     *	Object used by <code>compareTo()</code>
     */
    public Object getComparableObject() {
	if (comparableObject == null) {
	    return this;
	} else {
	    return comparableObject;
	}
    }

    public int compareTo(Object object) {
	String string = getComparableObject().toString();

	if (object instanceof DblTreeNode) {
	    DblTreeNode other = (DblTreeNode) object;
	    return string.compareTo(other.getComparableObject().toString());
	} else {
	    return string.compareTo(object.toString());
	}
    }
}
