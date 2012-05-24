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

package com.oracle.solaris.vp.panel.swing.view;

import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class ListSelectorPanel extends SelectorPanel<ExtList> {
    //
    // Instance data
    //

    private ListCellOverlay overlay;

    //
    // Constructors
    //

    public ListSelectorPanel() {
	ExtList list = new ExtList();

	list.setVisibleWidth(SELECTION_VIEWPORT_WIDTH);
	list.setVisibleRowCount(8);
	list.setScrollableTracksViewportWidth(true);

	overlay = new ListCellOverlay(list);

	setSelectionComponent(list);
    }

    //
    // ListSelectorPanel methods
    //

    public ListCellOverlay getListCellOverlay() {
	return overlay;
    }
}
