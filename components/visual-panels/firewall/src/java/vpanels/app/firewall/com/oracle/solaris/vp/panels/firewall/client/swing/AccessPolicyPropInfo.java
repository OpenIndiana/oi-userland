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
import java.util.Comparator;
import javax.swing.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.InfoLabel;
import com.oracle.solaris.vp.util.swing.propinfo.AbstractSwingPropInfo;

public class AccessPolicyPropInfo<M extends ManagedObject>
    extends AbstractSwingPropInfo<M, AccessPolicy> {

    //
    // Static data
    //

    private static final Comparator<AccessPolicy> comparator =
	new Comparator<AccessPolicy>() {
	    @Override
	    public int compare(AccessPolicy a1, AccessPolicy a2) {
		if (a1 == null) {
		    if (a2 == null) {
			return 0;
		    }
		    return -1;
		}

		if (a2 == null) {
		    return 1;
		}

		return ObjectUtil.compare(a1.getType(), a2.getType());
	    }
	};

    //
    // Instance data
    //

    private FirewallPanelDescriptor descriptor;

    @SuppressWarnings({"serial"})
    private TableCellRenderer renderer =
	new DefaultTableCellRenderer() {
	    @Override
	    public Component getTableCellRendererComponent(
		JTable table, Object value, boolean isSelected,
		boolean hasFocus, int row, int column) {

		AccessPolicy policy = (AccessPolicy)value;
		String message = AccessPolicyUtil.toString(policy, false);

		JLabel label = (JLabel)super.getTableCellRendererComponent(
		    table, message, isSelected, hasFocus, row, column);

		label.setIcon(policy == null ? InfoLabel.ICON : null);
		label.setHorizontalTextPosition(SwingConstants.LEFT);

		String tooltip = null;
		if (policy == null) {
		    String defaultPolicyText = AccessPolicyUtil.toString(
			descriptor.getAccessPolicy(), true);

		    tooltip = Finder.getString(
			"service.objects.access.option.default.tooltip",
			defaultPolicyText);
		}

		label.setToolTipText(tooltip);

		return label;
	    }
	};

    //
    // Constructors
    //

    public AccessPolicyPropInfo(FirewallPanelDescriptor descriptor) {
	super(Finder.getString("property.label.access"),
	    Finder.getString("property.description.access"), true, false);

	this.descriptor = descriptor;
    }

    //
    // PropInfo methods
    //

    @Override
    public Comparator<AccessPolicy> getComparator() {
	return comparator;
    }

    @Override
    public AccessPolicy getValue(M o) {
	return ((HasAccessPolicy)o).getAccessPolicy();
    }

    /**
     * Default implementation that does nothing.
     */
    @Override
    public void setValue(M o, AccessPolicy value) {
    }

    //
    // SwingPropInfo methods
    //

    @Override
    public TableCellRenderer getTableCellRenderer() {
	return renderer;
    }
}
