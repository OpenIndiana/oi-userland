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

package com.oracle.solaris.vp.util.swing.layout;

public class ColumnLayoutConstraint extends
    AbstractTableConstraint<ColumnLayoutConstraint> implements HasAnchors {

    //
    // Static data
    //

    protected static final HorizontalAnchor DEFAULT_H_ANCHOR =
	HorizontalAnchor.FILL;

    protected static final VerticalAnchor DEFAULT_V_ANCHOR =
	VerticalAnchor.FILL;

    //
    // Instance data
    //

    private HorizontalAnchor hAnchor;
    private VerticalAnchor vAnchor;

    //
    // Constructors
    //

    public ColumnLayoutConstraint(HorizontalAnchor hAnchor,
	VerticalAnchor vAnchor, int gap, float weight) {

	super(gap, weight);
	setHorizontalAnchor(hAnchor);
	setVerticalAnchor(vAnchor);
    }

    public ColumnLayoutConstraint(
	HorizontalAnchor hAnchor, int gap, float weight) {

	this(hAnchor, DEFAULT_V_ANCHOR, gap, weight);
    }

    public ColumnLayoutConstraint(HorizontalAnchor hAnchor, int gap) {
	this(hAnchor, gap, DEFAULT_WEIGHT);
    }

    public ColumnLayoutConstraint(HorizontalAnchor hAnchor) {
	this(hAnchor, DEFAULT_GAP);
    }

    public ColumnLayoutConstraint() {
	this(DEFAULT_H_ANCHOR);
    }

    //
    // Cloneable methods
    //

    @Override
    public ColumnLayoutConstraint clone() {
	ColumnLayoutConstraint c = new ColumnLayoutConstraint();
	cloneAttributes(c);
	return c;
    }

    //
    // HasAnchors methods
    //

    @Override
    public HorizontalAnchor getHorizontalAnchor() {
	return hAnchor;
    }

    @Override
    public VerticalAnchor getVerticalAnchor() {
	return vAnchor;
    }

    //
    // AbstractTableConstraint methods
    //

    @Override
    public void cloneAttributes(AbstractTableConstraint constraint) {
	super.cloneAttributes(constraint);
	if (constraint instanceof ColumnLayoutConstraint) {
	    ColumnLayoutConstraint c = (ColumnLayoutConstraint)constraint;
	    c.setHorizontalAnchor(getHorizontalAnchor());
	    c.setVerticalAnchor(getVerticalAnchor());
	}
    }

    //
    // ColumnLayoutConstraint methods
    //

    public ColumnLayoutConstraint setHorizontalAnchor(
	HorizontalAnchor hAnchor) {

	this.hAnchor = hAnchor;
	return this;
    }

    public ColumnLayoutConstraint setVerticalAnchor(VerticalAnchor vAnchor) {
	this.vAnchor = vAnchor;
	return this;
    }
}
