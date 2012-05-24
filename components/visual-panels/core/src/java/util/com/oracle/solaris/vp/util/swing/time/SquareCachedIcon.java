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

package com.oracle.solaris.vp.util.swing.time;

import com.oracle.solaris.vp.util.swing.CachedIcon;

@SuppressWarnings({"serial"})
public abstract class SquareCachedIcon extends CachedIcon {
    //
    // Instance data
    //

    private int diameter;

    //
    // Constructors
    //

    public SquareCachedIcon(int diameter) {
	setDiameter(diameter);
    }

    //
    // Icon methods
    //

    @Override
    public int getIconHeight() {
	return diameter;
    }

    @Override
    public int getIconWidth() {
	return diameter;
    }

    //
    // SquareCachedIcon methods
    //

    /**
     * Gets the width and height of this icon.
     */
    public int getDiameter() {
	return diameter;
    }

    /**
     * Sets the width and height of this icon.
     */
    public void setDiameter(int diameter) {
	if (this.diameter != diameter) {
	    this.diameter = diameter;
	    invalidateCachedImage();
	}
    }
}
