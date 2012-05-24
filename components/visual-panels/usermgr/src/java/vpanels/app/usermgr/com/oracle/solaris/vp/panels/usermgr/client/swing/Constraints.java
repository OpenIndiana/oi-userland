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
 * Copyright (c) 1998, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.applet.*;
import java.awt.*;
import java.lang.*;


/**
 * SMC code adapted for Visual Panels
 *
 * A general utility class to make it easy to apply GridBagConstraints
 * to GridBagLayout.
 * Code lifted from "Java in a Nutshell", O'Reilly & Associated, Inc.
 * and wrapped in a final class.
 */
public final class Constraints {

    /**
     * This is the main constrain() method.  It has arguments for
     * all constraints.
     */
    public static void constrain(
	    Container	container,
	    Component	component,
	    int 	gridx,
	    int 	gridy,
	    int 	gridwidth,
	    int 	gridheight,
	    int 	fill,
	    int 	anchor,
	    double	weightx,
	    double	weighty,
	    int 	top,
	    int 	left,
	    int 	bottom,
	    int 	right)
    {
	GridBagConstraints gbc = new GridBagConstraints();
	gbc.gridx = gridx;
	gbc.gridy = gridy;
	gbc.gridwidth = gridwidth;
	gbc.gridheight = gridheight;
	gbc.fill = fill;
	gbc.anchor = anchor;
	gbc.weightx = weightx;
	gbc.weighty = weighty;

	if (top+bottom+left+right > 0)
	    gbc.insets = new Insets(top, left, bottom, right);

	((GridBagLayout)container.getLayout()).setConstraints(component, gbc);
	container.add(component);
    }


    /**
     * This version of constrain() specifies the position of a component
     * that does not grow and does not have margins.
     */
    public static void constrain(
	    Container	container,
	    Component	component,
	    int 	gridx,
	    int 	gridy,
	    int 	gridwidth,
	    int 	gridheight)
    {
	constrain(container, component,
	    gridx, gridy, gridwidth, gridheight,
	    GridBagConstraints.NONE, GridBagConstraints.NORTHWEST,
	    0.0, 0.0, 0, 0, 0, 0);
    }


    /**
     * This version of constrain() specifies the position of a component
     * that does not grow but does have margins.
     */
    public static void constrain(
	    Container	container,
	    Component	component,
	    int 	gridx,
	    int 	gridy,
	    int 	gridwidth,
	    int 	gridheight,
	    int 	top,
	    int 	left,
	    int 	bottom,
	    int 	right)
    {
	constrain(container, component,
	    gridx, gridy, gridwidth, gridheight,
	    GridBagConstraints.NONE, GridBagConstraints.NORTHWEST,
	    0.0, 0.0, top, left, bottom, right);
    }
}
