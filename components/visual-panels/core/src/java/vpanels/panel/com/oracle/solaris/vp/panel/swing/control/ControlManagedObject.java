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

package com.oracle.solaris.vp.panel.swing.control;

import javax.swing.Icon;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.util.swing.HasIcon;

/**
 * A simple wrapper around a {@code Control} that enhances its display
 * in a {@code ListSelectorControl}.
 */
public class ControlManagedObject<C extends SwingControl>
    extends AbstractManagedObject<ManagedObject> implements HasIcon {

    private C control_;
    private Icon icon_;

    protected ControlManagedObject(String id, Icon icon) {
	super(id);
	icon_ = icon;
    }

    public ControlManagedObject(C control, Icon icon) {
	super(control.getId());
	setName(control.getName());
	control_ = control;
	icon_ = icon;
    }

    @Override
    public Icon getIcon(int height) {
	return (icon_);
    }

    //
    // ControlManagedObject methods
    //

    public C getControl() {
	return (control_);
    }

    protected void setControl(C control) {
	setName(control.getName());
	control_ = control;
    }
}
