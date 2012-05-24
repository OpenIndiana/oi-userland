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

package com.oracle.solaris.vp.util.swing.event;

import java.util.EventObject;
import com.oracle.solaris.vp.util.swing.ExtListSelectionModel;

@SuppressWarnings({"serial"})
public class ExtListSelectionEvent extends EventObject {
    //
    // Enums
    //

    public enum Type {
	ADD, REMOVE, SET, CLEAR
    }

    //
    // Instance data
    //

    private Type type;
    private int anchorIndex;
    private int leadIndex;
    private boolean isAdjusting;

    //
    // Constructors
    //

    public ExtListSelectionEvent(ExtListSelectionModel source,
	Type type, int anchorIndex, int leadIndex, boolean isAdjusting) {

	super(source);

	this.type = type;
	this.anchorIndex = anchorIndex;
	this.leadIndex = leadIndex;
	this.isAdjusting = isAdjusting;
    }

    //
    // EventObject methods
    //

    public ExtListSelectionModel getSource() {
	return (ExtListSelectionModel)super.getSource();
    }

    //
    // ExtListSelectionEvent methods
    //

    public Type getType() {
	return type;
    }

    public int getAnchorIndex() {
	return anchorIndex;
    }

    public int getLeadIndex() {
	return leadIndex;
    }

    public boolean getIsAdjusting() {
	return isAdjusting;
    }
}
