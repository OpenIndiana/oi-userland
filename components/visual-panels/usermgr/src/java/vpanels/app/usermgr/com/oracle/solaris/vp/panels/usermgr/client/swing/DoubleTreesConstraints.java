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

import java.awt.*;

/**
 * SMC code adapted for Visual Panels
 *
 * This class provides the <code>DoubleTreesLayout</code> manager constraints.
 *
 */
public class DoubleTreesConstraints implements Cloneable, java.io.Serializable {

    /**
     * Default <code>location</code> field value.
     * Used to determine if the location
     * field has not been set.
     */
    private static final int UNKNOWN = 0;

    /**
     * <code>location</code> field value for the left label
     * above the left scrollpane.
     */
    public static final int LEFT_LABEL = 1;

    /**
     * <code>location</code> field value for the left scrollpane.
     */
    public static final int LEFT_SCROLLPANE = 2;

    /**
     * <code>location</code> field value for the right label above the right
     * scrollpane.
     */
    public static final int RIGHT_LABEL = 3;

    /**
     * <code>location</code> field value for the right scrollpane.
     */
    public static final int RIGHT_SCROLLPANE = 4;

    /**
     * <code>location</code> field value for the central buttons between the
     * left and right scrollpane.
     */
    public static final int BUTTONS = 5;

    /**
     * This field identifies which component within the
     * <code>DoubleTreesLayout</code> the constraints belong to. If the
     * location has not been set the value is undefined but will not
     * default to any of the valid field values.
     * <br>
     * Valid field
     * values are
     * <code>LEFT_LABEL</code>,
     * <code>RIGHT_LABEL</code>,
     * <code>LEFT_SCROLLPANE</code>,
     * <code>RIGHT_SCROLLPANE</code> and
     * <code>BUTTONS</code>.
     */
    public int location;

    /**
     * This field specifies the external padding of the
     * component, the minimum amount of space between the component and the
     * edges of its display area.
     * <br>
     * The default value is
     * <code>new Insets(0, 0, 0, 0)</code>.
     */
    public Insets insets;

    /**
     * This field specifies the internal padding of the component,
     * how much space to add to the minimum width of the component.
     * The width of the component is at least its minimum width plus
     * (<code>ipadx</code> * 2) pixels.
     * <br>
     * The default value is 0.
     */
    public int ipadx;

    /**
     * This field specifies the internal padding of the component,
     * how much space to add to the minimum height of the component.
     * The height of the component is at least its minimum height plus
     * (<code>ipadx</code> * 2) pixels.
     * <br>
     * The default value is 0.
     */
    public int ipady;

    /**
     * Creates a <code>DoubleTreesConstraint</code> object with all of
     * the fields set to the default value.
     */
    public DoubleTreesConstraints() {
	location = UNKNOWN;
	insets = new Insets(0, 0, 0, 0);
	ipadx = 0;
	ipady = 0;
    }

    /**
     * Creates a <code>DoubleTreesConstraints</code> object with all of the
     * fields set to the passed-in arguments.
     *
     * @param location
     *	<code>location</code> field value.
     * @param insets
     *	<code>insets</code> field value.
     * @param ipadx
     *	<code>ipadx</code> field value.
     * @param ipady
     *	<code>ipady</code> field value.
     */
    public DoubleTreesConstraints(
	    int location,
	    Insets insets,
	    int ipadx, int ipady) {
	this.location = location;
	this.insets = insets;
	this.ipadx = ipadx;
	this.ipady = ipady;
    }

// ----------------------------------------------------------------------

    public Object clone() {
	try {
	    return ((DoubleTreesConstraints)super.clone());
	} catch (CloneNotSupportedException e) {
	    // this shouldn't happen, since we are Cloneable
	    throw new InternalError();
	}
    }
}
