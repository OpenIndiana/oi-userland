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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.Component;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.view.ManagedObjectCellRenderer;
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings({"serial"})
public class MainListCellRenderer
    extends ManagedObjectCellRenderer<ManagedObject> {

    //
    // Static data
    //

    static final String TEXT_GLOBAL = Finder.getString("global.name");

    //
    // SimpleCellRenderer methods
    //

    //
    // Don't need status text
    //
    @Override
    public String getStatusText(Component comp, ManagedObject obj,
	boolean isSelected, boolean hasFocus) {
	return obj instanceof FirewallPanelDescriptor ? null :
	    super.getStatusText(comp, obj, isSelected, hasFocus);
    }

    @Override
    public String getText(Component comp, ManagedObject obj, boolean isSelected,
	boolean hasFocus) {

	return obj instanceof FirewallPanelDescriptor ?  TEXT_GLOBAL :
	    super.getText(comp, obj, isSelected, hasFocus);
    }
}
