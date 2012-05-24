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

import java.awt.*;
import javax.swing.Icon;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.Changeable;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.InfoLabel;

@SuppressWarnings({"serial"})
public class ChangeIndicator extends InfoLabel implements ChangeListener {
    //
    // Static data
    //

    public static final Icon ICON_CHANGED =
	Finder.getIcon("images/general/change.png");

    public static final Icon ICON_UNCHANGED =
	new Icon() {
	    @Override
	    public int getIconHeight() {
		return ICON_CHANGED.getIconHeight();
	    }

	    @Override
	    public int getIconWidth() {
		return ICON_CHANGED.getIconWidth();
	    }

	    @Override
	    public void paintIcon(Component c, Graphics g, int x, int y) {
	    }
	};

    public static final String TEXT =
	Finder.getString("settings.changed.field");

    //
    // Constructors
    //

    public ChangeIndicator(boolean changed) {
	super(TEXT);
	setChanged(changed);
    }

    public ChangeIndicator() {
	this(false);
    }

    //
    // ChangeListener methods
    //

    @Override
    public void stateChanged(ChangeEvent e) {
	Changeable source = (Changeable)e.getSource();
	setChanged(source.isChanged());
    }

    //
    // ChangeIndicator methods
    //

    public void setChanged(boolean changed) {
	setIcon(changed ? ICON_CHANGED : ICON_UNCHANGED);
	setToolTipText(changed ? TEXT : null);
    }
}
