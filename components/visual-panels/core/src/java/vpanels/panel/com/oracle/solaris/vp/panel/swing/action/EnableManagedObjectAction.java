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

package com.oracle.solaris.vp.panel.swing.action;

import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.Enableable;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasComponent;

@SuppressWarnings({"serial"})
public class EnableManagedObjectAction<S extends ManagedObject, I, O>
    extends SwingManagedObjectAction<S, I, O> {

    //
    // Static data
    //

    protected static final List<ImageIcon> ICONS_ENABLE =
	Finder.getIcons("images/action-enable-16.png");

    protected static final List<ImageIcon> ICONS_DISABLE =
	Finder.getIcons("images/action-disable-16.png");

    protected static final String TEXT_ENABLE =
	Finder.getString("objects.action.enable");

    protected static final String TEXT_DISABLE =
	Finder.getString("objects.action.disable");

    //
    // Instance data
    //

    private boolean enable_;

    //
    // Constructors
    //

    public EnableManagedObjectAction(String text,
	Collection<? extends Icon> icons, ClientContext context,
	HasComponent hasComponent, boolean enable) {

	super(text, icons, context, hasComponent);
	enable_ = enable;
    }

    public EnableManagedObjectAction(String text,
	Collection<? extends Icon> icons, SwingControl control, boolean enable)
    {
	this(text, icons, control.getClientContext(), control, enable);
    }

    //
    // StructuredAction methods
    //

    /**
     * Enables this {@code Action} iff the selection contains at least one
     * {@link Enableable} that is disabled.
     */
    @Override
    public void refresh() {
	List<S> selection = getPresetInput();
	for (S o : selection) {
	    if (o instanceof Enableable &&
		((Enableable)o).isEnabled() != enable_) {
		setEnabled(true);
		return;
	    }
	}
	setEnabled(false);
    }

    //
    // EnableManagedObjectAction methods
    //

    protected boolean getEnable() {
	return (enable_);
    }
}
