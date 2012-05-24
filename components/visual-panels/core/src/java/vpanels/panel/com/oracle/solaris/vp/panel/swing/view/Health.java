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

package com.oracle.solaris.vp.panel.swing.view;

import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObjectStatus;
import com.oracle.solaris.vp.util.misc.IconUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

public enum Health implements HasIcons, HasIcon {
    //
    // Values
    //

    HEALTHY, WARNING, ERROR, DISABLED;

    //
    // Instance data
    //

    private List<ImageIcon> icons;
    private List<ImageIcon> roIcons;

    //
    // Constructors
    //

    Health() {
	String name = toString().toLowerCase();
	icons = Finder.getIcons(
	    "images/health/" + name + "-16.png",
	    "images/health/" + name + "-24.png",
	    "images/health/" + name + "-32.png");
	roIcons = Collections.unmodifiableList(icons);
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return IconUtil.getClosestIcon(getIcons(), height);
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return roIcons;
    }

    //
    // Static methods
    //

    public static Health fromManagedObjectStatus(ManagedObjectStatus status,
	boolean enabled) {

	switch (status) {
	case HEALTHY:
	    return (enabled ? HEALTHY : DISABLED);
	case WARNING:
	    return (WARNING);
	case ERROR:
	    return (ERROR);
	}
	/* Shouldn't happen */
	return (ERROR);
    }
}
