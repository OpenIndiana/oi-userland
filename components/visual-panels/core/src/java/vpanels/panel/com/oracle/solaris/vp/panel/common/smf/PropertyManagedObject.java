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

package com.oracle.solaris.vp.panel.common.smf;

import java.util.List;
import javax.swing.*;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.util.misc.IconUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasIcon;

public class PropertyManagedObject extends AbstractManagedObject<ManagedObject>
    implements HasIcon {

    //
    // Static data
    //

    protected static final List<ImageIcon> icons = Finder.getIcons(
	"images/property-16.png",
	"images/property-22.png",
	"images/property-24.png",
	"images/property-32.png",
	"images/property-48.png",
	"images/property-256.png");

    //
    // Instance data
    //

    private PropertyGroupManagedObject parent;
    private BasicSmfMutableProperty property;

    //
    // Constructors
    //

    PropertyManagedObject(PropertyGroupManagedObject parent,
	BasicSmfMutableProperty property) throws ScfException {

	super(property.getPropertyName());

	this.parent = parent;
	this.property = property;
	refresh(true);
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return IconUtil.getClosestIcon(icons, height);
    }

    //
    // PropertyManagedObject methods
    //

    public BasicSmfMutableProperty getProperty() {
	return property;
    }

    public void refresh(boolean force) throws ScfException {
	property.updateFromRepo(force);
    }
}
