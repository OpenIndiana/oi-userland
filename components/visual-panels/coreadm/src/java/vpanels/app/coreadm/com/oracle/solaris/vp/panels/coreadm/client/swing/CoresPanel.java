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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.action.StructuredAction;
import com.oracle.solaris.vp.panel.swing.model.ManagedObjectPropInfo;
import com.oracle.solaris.vp.panel.swing.view.TableObjectsPanel;
import com.oracle.solaris.vp.util.common.propinfo.PropInfo;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.SettingsPanel;
import com.oracle.solaris.vp.util.swing.propinfo.SizePropInfo;

@SuppressWarnings({"serial"})
public class CoresPanel extends SettingsPanel {
    //
    // Static data
    //

    @SuppressWarnings({"unchecked"})
    private static final PropInfo<CoreManagedObject, ?>[] props =
	new PropInfo[] {
	    ManagedObjectPropInfo.instance,
	    SizePropInfo.instance,
	};

    //
    // Constructors
    //

    public CoresPanel(CoreAdmPanelDescriptor descriptor,
	StructuredAction<List<CoreManagedObject>, ?, ?>[] actions,
	StructuredAction<List<CoreManagedObject>, ?, ?> dAction) {

	String title = Finder.getString("core.objects.title");
	TableObjectsPanel<CoreManagedObject> oPanel =
	    new TableObjectsPanel<CoreManagedObject>(
	    descriptor, actions, dAction, title, null, props);

	// Sort table by default
	List<RowSorter.SortKey> keys = new ArrayList<RowSorter.SortKey>();
	keys.add(new RowSorter.SortKey(0, SortOrder.ASCENDING));
	oPanel.getTableObjectsView().getTable().getRowSorter().setSortKeys(
	    keys);
	oPanel.setHeaderVisible(false);
	oPanel.setShowContentBorder(false);

	setContent(oPanel, false, false);
    }
}
