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

import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.util.misc.IconUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasIcon;

@SuppressWarnings({"serial"})
public class CoreManagedObject
    extends AbstractManagedObject<ManagedObject>
    implements HasIcon {

    //
    // Static data
    //

    protected static final List<ImageIcon> icons = Finder.getIcons(
	"images/core-24.png",
	"images/core-32.png",
	"images/core-36.png",
	"images/core-48.png",
	"images/core-72.png",
	"images/core-96.png");

    //
    // Instance data
    //

    private CoreAdmPanelDescriptor descriptor;
    private String name;
    private long size;

    //
    // Constructors
    //

    public CoreManagedObject(CoreAdmPanelDescriptor descriptor, String name,
	long size) {

	this.descriptor = descriptor;
	this.name = name;
	this.size = size;
    }

    //
    // ManagedObject methods
    //

    @Override
    public String getId() {
	return getName();
    }

    @Override
    public String getName() {
	return name;
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return IconUtil.getClosestIcon(icons, height);
    }

    //
    // CoreManagedObject methods
    //

    public CoreAdmPanelDescriptor getPanelDescriptor() {
	return descriptor;
    }

    public long getSize() {
	return size;
    }

    protected void setSize(long size) {
	this.size = size;
    }
}
