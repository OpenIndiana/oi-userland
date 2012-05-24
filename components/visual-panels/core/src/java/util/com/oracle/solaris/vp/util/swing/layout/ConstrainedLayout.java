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

import java.awt.*;
import java.util.HashMap;

public abstract class ConstrainedLayout<C> extends AbstractLayout
    implements LayoutManager2 {

    //
    // Instance data
    //

    // Mapping from Component to constraint
    protected HashMap<Component, C> compToConst = new HashMap<Component, C>();
    private C _constraint;

    //
    // Constructors
    //

    /**
     * Constructs a {@code ConstrainedLayout}.
     *
     * @param	    _constraint
     *		    the default constraint, if none is specified when a
     *		    {@code Component} is added
     */
    public ConstrainedLayout(C _constraint) {
	setDefaultConstraint(_constraint);
    }

    //
    // LayoutManager methods
    //

    @Override
    public void addLayoutComponent(String name, Component comp) {
	addLayoutComponent(comp, getDefaultConstraint());
    }

    @Override
    public void removeLayoutComponent(Component comp) {
	synchronized (comp.getTreeLock()) {
	    compToConst.remove(comp);
	}
    }

    //
    // LayoutManager2 methods
    //

    @Override
    @SuppressWarnings({"unchecked"})
    public void addLayoutComponent(Component comp, Object constraint) {
	synchronized (comp.getTreeLock()) {
	    if (constraint == null) {
		constraint = getDefaultConstraint();
	    }

	    Class<? extends Object> objClass = constraint.getClass();
	    Class<? extends C> reqClass = getConstraintClass();

	    if (reqClass.isAssignableFrom(objClass)) {
		C clone = cloneConstraint((C)constraint);
		compToConst.put(comp, clone);
	    } else {
		throw new IllegalArgumentException(String.format(
		    "invalid constraint (must be %s or null): %s",
		    reqClass.getName(), objClass.getName()));
	    }
	}
    }

    @Override
    public float getLayoutAlignmentX(Container parent) {
	return 0.5f;
    }

    @Override
    public float getLayoutAlignmentY(Container parent) {
	return 0.5f;
    }

    @Override
    public void invalidateLayout(Container container) {
    }

    @Override
    public Dimension maximumLayoutSize(Container container) {
	return new Dimension(Integer.MAX_VALUE, Integer.MAX_VALUE);
    }

    //
    // ConstrainedLayout methods
    //

    public abstract C cloneConstraint(C constraint);

    public C getConstraint(Component c) {
	return compToConst.get(c);
    }

    public C getDefaultConstraint() {
	return _constraint;
    }

    public void setDefaultConstraint(C _constraint) {
	this._constraint = cloneConstraint(_constraint);
    }

    @SuppressWarnings({"unchecked"})
    public Class<? extends C> getConstraintClass() {
	return (Class<? extends C>)getDefaultConstraint().getClass();
    }
}
