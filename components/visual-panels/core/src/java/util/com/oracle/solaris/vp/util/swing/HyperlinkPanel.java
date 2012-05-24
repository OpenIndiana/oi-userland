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

import java.awt.Component;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.TextUtil;

@SuppressWarnings({"serial"})
public class HyperlinkPanel extends JPanel {
    //
    // Instance data
    //

    private String text;

    //
    // Constructors
    //

    public HyperlinkPanel() {
	BoxLayout layout = new BoxLayout(this, BoxLayout.LINE_AXIS);
	setLayout(layout);
	setOpaque(false);
    }

    public HyperlinkPanel(String text) {
	this();
	setText(text);
    }

    //
    // HyperlinkPanel methods
    //

    protected Component createLabel(String text) {
	return new JLabel(text);
    }

    protected List<Component> createComponents(String text) {
	List<Component> components = new ArrayList<Component>();

	while (text != null && !text.isEmpty()) {
	    String[] groups = TextUtil.match(text,
		"(.*?)((?<!\\\\)(<a[^>]*>)(.*?)(</a>)(.*))?");

	    if (groups[1] != null) {
		Component comp = createLabel(groups[1]);
		if (comp != null) {
		    components.add(comp);
		}
	    }

	    if (groups[4] != null) {
		Component comp = createHyperlink(groups[4]);
		if (comp != null) {
		    components.add(comp);
		}
	    }

	    text = groups[6];
	}

	return components;
    }

    protected Component createHyperlink(String text) {
	return new HyperlinkLabel(text);
    }

    public String getText() {
	return text;
    }

    public void setText(String text) {
	this.text = text;
	removeAll();

	for (Component comp : createComponents(text)) {
	    add(comp);
	}
    }
}
