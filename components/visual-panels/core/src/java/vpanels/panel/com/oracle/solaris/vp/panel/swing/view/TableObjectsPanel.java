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
 * Copyright (c) 2008, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.swing.view;

import java.util.List;
import com.oracle.solaris.vp.panel.common.action.StructuredAction;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.util.common.propinfo.PropInfo;

/**
 * The {@code TableObjectsPanel} class displays the children of a {@code
 * ManagedObject} in a {@code JTable}.
 */
@SuppressWarnings({"serial"})
public class TableObjectsPanel<C extends ManagedObject>
    extends ObjectsPanel<C> {

    //
    // Instance data
    //

    private TableObjectsView<C> view;

    //
    // Constructors
    //

    public TableObjectsPanel(ManagedObject<C> pObject,
	StructuredAction<List<C>, ?, ?>[] mActions,
	StructuredAction<List<C>, ?, ?> dmAction, String title, String help,
	PropInfo<C, ?>[] props) {

	super(pObject, mActions, dmAction, title, help);

	FilterManagedObject<C> fObject = getFilterManagedObject();
	view = new TableObjectsView<C>(fObject, mActions, dmAction, props);
	addView(view);
    }

    //
    // TableObjectsPanel methods
    //

    public TableObjectsView<C> getTableObjectsView() {
	return view;
    }
}
