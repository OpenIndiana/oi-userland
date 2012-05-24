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

package com.oracle.solaris.vp.util.swing;

import javax.swing.*;
import com.oracle.solaris.vp.util.misc.DialogMessage;
import com.oracle.solaris.vp.util.swing.layout.*;

/**
 * The {@code DialogMessagePanel} class displays a {@link DialogMessage} message
 * and icon.
 */
@SuppressWarnings({"serial"})
public class DialogMessagePanel extends JPanel {
    //
    // Instance data
    //

    private DialogMessage message;
    private JLabel iconLabel;
    private WrappingText messageLabel;

    //
    // Constructors
    //

    public DialogMessagePanel() {
	iconLabel = new AutoHideLabel();
	messageLabel = new WrappingText();
	messageLabel.setPreferredWidthInColumns(25);

	setLayout(new RowLayout(HorizontalAnchor.FILL));

	int gap = GUIUtil.getHalfGap();

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, gap);

	add(iconLabel, r);

	add(messageLabel, r.setWeight(1).setVerticalAnchor(
	    VerticalAnchor.CENTER));
    }

    public DialogMessagePanel(DialogMessage message) {
	this();
	setMessage(message);
    }

    //
    // DialogMessagePanel methods
    //

    public DialogMessage getMessage() {
	return message;
    }

    public WrappingText getMessageLabel() {
	return messageLabel;
    }

    public void setMessage(DialogMessage message) {
	iconLabel.setIcon(message == null ?
	    null : GUIUtil.getIcon(message.getType()));
	messageLabel.setText(message == null ?
	    null : message.getText());
    }
}
