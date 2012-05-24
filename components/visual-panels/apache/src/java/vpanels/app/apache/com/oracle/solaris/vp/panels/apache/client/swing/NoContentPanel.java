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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.awt.BorderLayout;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.TextUtil;
import com.oracle.solaris.vp.util.swing.GUIUtil;

@SuppressWarnings({"serial"})
public class NoContentPanel extends JPanel {
    //
    // Static data
    //

    public static final int WIDTH = 40;

    //
    // Constructors
    //

    public NoContentPanel(String messageText) {
	setOpaque(false);
	messageText = formatAsHTML(messageText, WIDTH);

	Icon icon = GUIUtil.getIcon(JOptionPane.INFORMATION_MESSAGE);
	JLabel label = new JLabel(messageText);
	label.setIcon(icon);
	label.setIconTextGap(icon.getIconWidth() / 3);
	label.setHorizontalAlignment(SwingConstants.CENTER);
	label.setVerticalAlignment(SwingConstants.CENTER);

	setLayout(new BorderLayout());
	add(label, BorderLayout.CENTER);
    }

    public static String formatAsHTML(String text, int width) {
	if (text != null && !text.matches("(?i)^<html\\b.*")) {
	    text = "<html>" + TextUtil.escapeHTMLChars(
		TextUtil.format(text, width, false)) + "</html>";
	}
	return text;
    }
}
