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

import java.awt.Component;
import java.util.HashMap;

public abstract class UniqueConstrainedLayout<C> extends ConstrainedLayout<C> {
    //
    // Instance data
    //

    /*
     * Mapping from constraint to Component
     */
    protected HashMap<C, Component> constToComp = new HashMap<C, Component>();

    //
    // Constructors
    //

    public UniqueConstrainedLayout(C _constraint) {
	super(_constraint);
    }

    //
    // LayoutManager methods
    //

    @Override
    public void removeLayoutComponent(Component comp) {
	synchronized (comp.getTreeLock()) {
	    C constraint = compToConst.get(comp);
	    if (constraint != null) {
		Component c = constToComp.get(constraint);
		if (c == comp) {
		    constToComp.remove(constraint);
		}
	    }

	    super.removeLayoutComponent(comp);
	}
    }

    //
    // LayoutManager2 methods
    //

    @Override
    public void addLayoutComponent(Component comp, Object constraint) {
	synchronized (comp.getTreeLock()) {
	    super.addLayoutComponent(comp, constraint);

	    @SuppressWarnings({"unchecked"})
	    C c = constraint == null ? getDefaultConstraint() : (C)constraint;
	    Component oldComp = constToComp.get(c);

	    if (oldComp != comp) {
		if (oldComp != null) {
		    removeLayoutComponent(oldComp);
		}
		constToComp.put(c, comp);
	    }
	}
    }

    //
    // ConstrainedLayout methods
    //

    public C cloneConstraint(C constraint) {
	return constraint;
    }

    //
    // UniqueConstrainedLayout methods
    //

    public Component getComponent(C c) {
	return constToComp.get(c);
    }
}
