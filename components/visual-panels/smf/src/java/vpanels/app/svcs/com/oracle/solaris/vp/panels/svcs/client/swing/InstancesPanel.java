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

package com.oracle.solaris.vp.panels.svcs.client.swing;

import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.action.StructuredAction;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.InstanceManagedObject;
import com.oracle.solaris.vp.panel.swing.model.ManagedObjectPropInfo;
import com.oracle.solaris.vp.panel.swing.view.TableObjectsPanel;
import com.oracle.solaris.vp.util.common.propinfo.PropInfo;
import com.oracle.solaris.vp.util.misc.event.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.SettingsPanel;

@SuppressWarnings({"serial"})
public class InstancesPanel extends SettingsPanel
{
    TableObjectsPanel<InstanceManagedObject> oPanel;

    //
    // Static data
    //

    @SuppressWarnings({"unchecked"})
    private static final PropInfo<InstanceManagedObject, ?>[]
	props = new PropInfo[] {
	    ManagedObjectPropInfo.instance,
	    StatePropInfo.instance,
	    STimePropInfo.instance,
	};

    //
    // Constructors
    //

    public InstancesPanel(SvcsPanelDescriptor descriptor,
	StructuredAction<List<InstanceManagedObject>, ?, ?>[] actions,
	StructuredAction<List<InstanceManagedObject>, ?, ?> dAction)
    {
	String title = Finder.getString("smf.instances.title");
	/* TableObjectsPanel<InstanceManagedObject> */ oPanel =
	    new TableObjectsPanel<InstanceManagedObject>(
	    new EmptyManagedObject<InstanceManagedObject>(),
	    actions, dAction, title, null, props);

	// Sort table by default
	List<RowSorter.SortKey> keys = new ArrayList<RowSorter.SortKey>();

	/* MAINT -> ONLINE */
	keys.add(new RowSorter.SortKey(1, SortOrder.ASCENDING));

	/* young -> old */
	keys.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));

	oPanel.getTableObjectsView().getTable().getRowSorter().
	    setSortKeys(keys);
	oPanel.setHeaderVisible(false);
	oPanel.setShowContentBorder(false);
	oPanel.getToolBar().setFilterVisible(true);
	oPanel.getToolBar().getFilterField().setFilterListener(
	    new FilterPredicate<InstanceManagedObject>(
	    oPanel.getFilterManagedObject()));
	setContent(oPanel, false, false);

	oPanel.getFilterManagedObject().addIntervalListener(
	    new IntervalListener() {

	    public void intervalAdded(IntervalEvent event) {
		oPanel.getToolBar().getFilterField().setUnmatched(
		    oPanel.getFilterManagedObject().getChildren().size() == 0);
	    }

	    public void intervalRemoved(IntervalEvent event) {
		oPanel.getToolBar().getFilterField().setUnmatched(
		    oPanel.getFilterManagedObject().getChildren().size() == 0);
	    }

	});
	setOpaque(false);
	setBorder(BorderFactory.createEmptyBorder());
    }

    public FilterManagedObject<InstanceManagedObject> getFmo()
    {
	return oPanel.getFilterManagedObject();
    }
}
