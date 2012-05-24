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

public abstract class AbstractTableConstraint<S extends AbstractTableConstraint>
    implements Cloneable {

    //
    // Static data
    //

    protected static final int DEFAULT_GAP = 0;
    protected static final float DEFAULT_WEIGHT = 0;
    protected static final boolean DEFAULT_IGNORE_FIRST_GAP = true;
    protected static final boolean DEFAULT_LAYOUT_IF_INVISIBLE = false;

    //
    // Instance data
    //

    private int gap;
    private float weight;
    private boolean ignoreFirstGap = DEFAULT_IGNORE_FIRST_GAP;
    private boolean layoutIfInvisible = DEFAULT_LAYOUT_IF_INVISIBLE;

    //
    // Constructors
    //

    public AbstractTableConstraint(int gap, float weight) {
	this.gap = gap;
	this.weight = weight;
    }

    public AbstractTableConstraint(int gap) {
	this(gap, DEFAULT_WEIGHT);
    }

    public AbstractTableConstraint() {
	this(DEFAULT_GAP);
    }

    //
    // Cloneable methods
    //

    @Override
    public abstract S clone();

    //
    // AbstractTableConstraint methods
    //

    /**
     * Sets all known attributes of this {@code AbstractTableConstraint} on the
     * given {@code AbstractTableConstraint}.
     */
    public void cloneAttributes(AbstractTableConstraint c) {
	c.setGap(getGap());
	c.setWeight(getWeight());
	c.setIgnoreFirstGap(getIgnoreFirstGap());
	c.setLayoutIfInvisible(getLayoutIfInvisible());
    }

    public int getGap() {
	return gap;
    }

    public boolean getIgnoreFirstGap() {
	return ignoreFirstGap;
    }

    public boolean getLayoutIfInvisible() {
	return layoutIfInvisible;
    }

    public float getWeight() {
	return weight;
    }

    @SuppressWarnings({"unchecked"})
    public S setGap(int gap) {
	if (gap < 0) {
	    gap = 0;
	}
	this.gap = gap;
	return (S)this;
    }

    @SuppressWarnings({"unchecked"})
    public S setWeight(float weight) {
	if (weight < 0) {
	    weight = 0;
	}
	this.weight = weight;
	return (S)this;
    }

    @SuppressWarnings({"unchecked"})
    public S setIgnoreFirstGap(boolean ignoreFirstGap) {
	this.ignoreFirstGap = ignoreFirstGap;
	return (S)this;
    }

    @SuppressWarnings({"unchecked"})
    public S setLayoutIfInvisible(boolean layoutIfInvisible) {
	this.layoutIfInvisible = layoutIfInvisible;
	return (S)this;
    }
}
