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

package com.oracle.solaris.vp.util.swing;

import javax.swing.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.*;

@SuppressWarnings({"serial"})
public class InfoLabel extends JLabel {
    //
    // Static data
    //

    public static final Icon ICON;
    static {
	 Icon icon = GnomeUtil.getIcon("info", 12, true);
	 if (icon == null) {
	    icon = Finder.getIcon("images/general/info.png");
	 }
	 ICON = icon;
    }
    public static final int DEFAULT_WIDTH = 65;

    //
    // Instance data
    //

    private int width;

    //
    // Constructors
    //

    public InfoLabel(String text, int width) {
	super(ICON);

	setToolTipText(text);
	setToolTipWidth(width);
	addMouseListener(ToolTipDelayOverrider.IMMEDIATE);
    }

    public InfoLabel(String text) {
	this(text, DEFAULT_WIDTH);
    }

    public InfoLabel() {
	this(null);
    }

    //
    // JComponent methods
    //

    @Override
    public void setToolTipText(String text) {
	super.setToolTipText(text);
	reformat();
    }

    //
    // InfoLabel methods
    //

    public int getToolTipWidth() {
	return width;
    }

    public void setToolTipWidth(int width) {
	this.width = width;
	reformat();
    }

    //
    // Private methods
    //

    private void reformat() {
	String text = getToolTipText();

	if (text != null && !text.matches("(?i)^<html\\b.*")) {
	    int width = getToolTipWidth();
	    if (width > 0) {
		text = "<html>" + TextUtil.escapeHTMLChars(
		    TextUtil.format(text, width, false)) + "</html>";

		super.setToolTipText(text);
	    }
	}
    }
}
