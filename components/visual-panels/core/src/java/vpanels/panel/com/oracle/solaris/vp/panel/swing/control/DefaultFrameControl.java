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

import java.awt.*;
import javax.swing.WindowConstants;
import javax.swing.border.Border;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.util.swing.*;

public class DefaultFrameControl<P extends PanelDescriptor>
    extends FrameControl<P, ExtFrame> {

    //
    // Constructors
    //

    public DefaultFrameControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    public DefaultFrameControl(P descriptor) {
	super(descriptor);
    }

    //
    // SwingControl methods
    //

    @Override
    protected ExtFrame createComponent() {
        ExtFrame frame = new ExtFrame();
	frame.getRootPane().setAutoMinSizeEnabled(true);
	ReplacingStackPanel stack = new ReplacingStackPanel();
	stack.setBorder(getDefaultBorder());

	Container cont = frame.getContentPane();
	cont.setLayout(new BorderLayout());
	cont.add(stack, BorderLayout.CENTER);

	frame.setTitle(getName());
	frame.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

	setComponentStack(stack);
	return frame;
    }

    //
    // WindowControl methods
    //

    @Override
    protected String getWindowTitle() {
	return getComponent().getTitle();
    }

    @Override
    protected void setWindowTitle(String title) {
	getComponent().setTitle(title);
    }

    //
    // DefaultFrameControl methods
    //

    /**
     * Returns a {@code Border} to use on the outermost {@code Containter}
     * within the {@code ExtFrame}, or null to use no {@code Border}.
     * </p>
     * This default implementation returns {@link GUIUtil#getEmptyBorder}.
     */
    protected Border getDefaultBorder() {
	return GUIUtil.getEmptyBorder();
    }
}
