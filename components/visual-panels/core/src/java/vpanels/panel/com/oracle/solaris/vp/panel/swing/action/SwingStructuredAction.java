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

import java.util.Collection;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.swing.*;

public abstract class SwingStructuredAction<P, I, O>
    extends DefaultStructuredAction<P, I, O> {

    //
    // Static data
    //

    public static final int SMALL_ICON_HEIGHT = 16;

    //
    // Instance data
    //

    private Collection<? extends Icon> icons;
    private HasComponent hasComponent;

    //
    // Constructors
    //

    public SwingStructuredAction(String text, P pInput,
	Collection<? extends Icon> icons, ClientContext context,
	HasComponent hasComponent) {

	super(text, pInput, context);

	setIcons(icons);
	this.hasComponent = hasComponent;
    }

    public SwingStructuredAction(String text, P pInput,
	Collection<? extends Icon> icons, SwingControl control) {

	this(text, pInput, icons, control.getClientContext(), control);
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    protected void showError(ActionFailedException e) {
	GUIUtil.showError(hasComponent.getComponent(), null,
	    ThrowableUtil.getTrueMessage(e));
    }

    //
    // SwingStructuredAction methods
    //

    public HasComponent getHasComponent() {
	return hasComponent;
    }

    public Collection<? extends Icon> getIcons() {
	return icons;
    }

    public void setIcons(Collection<? extends Icon> icons) {
	this.icons = icons;
	Icon icon = null;

	if (icons != null) {
	    icon = IconUtil.getClosestIcon(icons, SMALL_ICON_HEIGHT);
	    if (icon != null) {
		icon = IconUtil.ensureIconHeight(icon, SMALL_ICON_HEIGHT);
	    }
	}

	putValue(Action.SMALL_ICON, icon);
    }
}
