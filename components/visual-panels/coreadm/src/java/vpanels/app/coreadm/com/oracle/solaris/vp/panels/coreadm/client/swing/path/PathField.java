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

package com.oracle.solaris.vp.panels.coreadm.client.swing.path;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;

@SuppressWarnings({"serial"})
public class PathField extends JTextPane implements TokenAttributeSetFactory {
    //
    // Constructors
    //

    public PathField() {
	setStyledDocument(new PathDocument(this));

	setFocusTraversalKeys(
	    KeyboardFocusManager.FORWARD_TRAVERSAL_KEYS, null);
	setFocusTraversalKeys(
	    KeyboardFocusManager.BACKWARD_TRAVERSAL_KEYS, null);

	// Synth doesn't set values in UIManager, so we're forced into this hack
	setBackground(new JTextField().getBackground());
	// setBackground(UIManager.getColor("TextField.background"));
    }

    //
    // TokenAttributeSetFactory methods
    //

    @Override
    public AttributeSet getAttributeSet(String token) {
	MutableAttributeSet attrs = new SimpleAttributeSet();
	Component renderer = new TokenLabel(token);
	renderer.setFont(getFont());
	StyleConstants.setComponent(attrs, renderer);

	return attrs;
    }

    //
    // Component methods
    //

    @Override
    public Dimension getPreferredSize() {
	Dimension d = super.getPreferredSize();

	for (int i = 0, n = getDocument().getLength(); i < n; i++) {
	    Element element = getStyledDocument().getCharacterElement(i);

	    // Is a TokenLabel showing?
	    if (PathDocument.isToken(element)) {
		// Calculated size already accounts for TokenLabel
		return d;
	    }

	    i = element.getEndOffset();
	}

	// No TokenLabel found, so account for its eventual arrival
	Insets insets = TokenLabel.BORDER.getBorderInsets(null);
	d.height += insets.top + insets.bottom;

	return d;
    }

    //
    // JTextComponent methods
    //

    @Override
    public String getText() {
	return ((PathDocument)getDocument()).getText();
    }

    //
    // Static methods
    //

    // XXX - Test, remove
    public static void main(String args[]) {
	final PathField textPane = new PathField();
//	textPane.setFont(new Font("Serif", Font.ITALIC, 36));
	StringBuilder buffer = new StringBuilder();
	for (String token : PathDocument.TOKENS) {
	    buffer.append(token).append('/');
	}
	textPane.setText(buffer.toString());

	JButton b = new JButton("Print tokens");
	b.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    System.out.printf("%s\n", textPane.getText());
		}
	    });

	JScrollPane scroll = new TextPaneScrollPane(textPane);

	JPanel p = new JPanel(new BorderLayout());
	p.add(scroll);
	p.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(p, BorderLayout.CENTER);
	c.add(b, BorderLayout.SOUTH);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
