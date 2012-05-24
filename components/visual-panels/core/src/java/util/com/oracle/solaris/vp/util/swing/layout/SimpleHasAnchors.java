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

public class SimpleHasAnchors implements HasAnchors, Cloneable {
    //
    // Instance data
    //

    private HorizontalAnchor hAnchor;
    private VerticalAnchor vAnchor;

    //
    // Constructors
    //

    public SimpleHasAnchors() {
    }

    public SimpleHasAnchors(HorizontalAnchor hAnchor, VerticalAnchor vAnchor) {
	this.hAnchor = hAnchor;
	this.vAnchor = vAnchor;
    }

    //
    // Object methods
    //

    @Override
    public SimpleHasAnchors clone() {
	return new SimpleHasAnchors(hAnchor, vAnchor);
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
    // SimpleHasAnchors methods
    //

    public SimpleHasAnchors setHorizontalAnchor(HorizontalAnchor hAnchor) {
	this.hAnchor = hAnchor;
	return this;
    }

    public SimpleHasAnchors setVerticalAnchor(VerticalAnchor vAnchor) {
	this.vAnchor = vAnchor;
	return this;
    }
}
