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

package com.oracle.solaris.vp.panel.swing.action;

import java.util.List;
import javax.swing.ImageIcon;
import com.oracle.solaris.vp.panel.common.control.Navigable;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings({"serial"})
public abstract class PropertiesManagedObjectAction<C extends ManagedObject>
    extends SwingManagedObjectAction<C, Navigable[], Object> {

    //
    // Static data
    //

    protected static final List<ImageIcon> ICONS = Finder.getIcons(
	"images/action-properties-16.png",
	"images/action-properties-22.png",
	"images/action-properties-24.png",
	"images/action-properties-32.png");

    protected static final String TEXT =
	Finder.getString("objects.action.properties");

    //
    // Constructors
    //

    public PropertiesManagedObjectAction(SwingControl control) {
	super(TEXT, ICONS, control);
    }

    //
    // StructuredAction methods
    //

    /**
     * Enables this {@code Action} if the selection consists of a single
     * element.
     */
    @Override
    public void refresh() {
	setEnabled(getPresetInput().size() == 1);
    }
}
