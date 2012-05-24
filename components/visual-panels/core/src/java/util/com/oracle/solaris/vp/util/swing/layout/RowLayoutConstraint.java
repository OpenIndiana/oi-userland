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

public class RowLayoutConstraint extends
    AbstractTableConstraint<RowLayoutConstraint> implements HasAnchors {

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

    public RowLayoutConstraint(HorizontalAnchor hAnchor, VerticalAnchor vAnchor,
	int gap, float weight) {

	super(gap, weight);
	setHorizontalAnchor(hAnchor);
	setVerticalAnchor(vAnchor);
    }

    public RowLayoutConstraint(VerticalAnchor vAnchor, int gap, float weight) {
	this(DEFAULT_H_ANCHOR, vAnchor, gap, weight);
    }

    public RowLayoutConstraint(VerticalAnchor vAnchor, int gap) {
	this(vAnchor, gap, DEFAULT_WEIGHT);
    }

    public RowLayoutConstraint(VerticalAnchor vAnchor) {
	this(vAnchor, DEFAULT_GAP);
    }

    public RowLayoutConstraint() {
	this(DEFAULT_V_ANCHOR);
    }

    //
    // Cloneable methods
    //

    @Override
    public RowLayoutConstraint clone() {
	RowLayoutConstraint r = new RowLayoutConstraint();
	cloneAttributes(r);
	return r;
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
	if (constraint instanceof RowLayoutConstraint) {
	    RowLayoutConstraint r = (RowLayoutConstraint)constraint;
	    r.setHorizontalAnchor(getHorizontalAnchor());
	    r.setVerticalAnchor(getVerticalAnchor());
	}
    }

    //
    // RowLayoutConstraint methods
    //

    public RowLayoutConstraint setHorizontalAnchor(HorizontalAnchor hAnchor) {
	this.hAnchor = hAnchor;
	return this;
    }

    public RowLayoutConstraint setVerticalAnchor(VerticalAnchor vAnchor) {
	this.vAnchor = vAnchor;
	return this;
    }
}
