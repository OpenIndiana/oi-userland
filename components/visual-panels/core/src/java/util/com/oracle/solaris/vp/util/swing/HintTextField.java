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

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.Document;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class HintTextField extends JTextField implements FocusListener {
    //
    // Static data
    //

    public static final ImageIcon ICON_FIND =
	Finder.getIcon("images/textfield/find.png");

    //
    // Instance data
    //

    private String hint;
    private Icon icon;
    private int iconTextGap;
    private int horizontalAlignment;

    private Rectangle iconR = new Rectangle();
    private Rectangle textR = new Rectangle();
    private Rectangle viewR = new Rectangle();

    //
    // Constructors
    //

    public HintTextField() {
	init();
    }

    public HintTextField(Document doc, String text, int columns) {
	super(doc, text, columns);
	init();
    }

    public HintTextField(int columns) {
	super(columns);
	init();
    }

    public HintTextField(String text) {
	super(text);
	init();
    }

    public HintTextField(String text, int columns) {
	super(text, columns);
	init();
    }

    //
    // FocusListener methods
    //

    @Override
    public synchronized void focusGained(FocusEvent e) {
	repaint();
    }

    @Override
    public synchronized void focusLost(FocusEvent e) {
	repaint();
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g) {
	super.paintComponent(g);

	Icon icon = getHintIcon();
	String hint = getHintText();

	// Display hint only if...
	if (!isFocusOwner() && getText().isEmpty() &&
	    (icon != null || (hint != null && !hint.isEmpty()))) {

	    Insets insets = getInsets();
	    FontMetrics metrics = getFontMetrics(getFont());

	    int gap = getIconTextGap();
	    if (gap < 0) {
		gap = metrics.charWidth('e');
	    }

	    int horizontalAlignment = getHintHorizontalAlignment();

	    viewR.x = insets.left;
	    viewR.y = insets.top;
	    viewR.width = getWidth() - (insets.left + insets.right);
	    viewR.height = getHeight() - (insets.top + insets.bottom);
	    iconR.x = iconR.y = iconR.width = iconR.height = 0;
	    textR.x = textR.y = textR.width = textR.height = 0;

	    String clippedHint = SwingUtilities.layoutCompoundLabel(
		this, metrics, hint, icon, SwingConstants.CENTER,
		horizontalAlignment, SwingConstants.CENTER,
		SwingConstants.RIGHT, viewR, iconR, textR, gap);

	    if (clippedHint != null) {
		// Turn on anti-aliasing if appropriate
		GUIUtil.setAARendering((Graphics2D)g);

		g.setColor(UIManager.getColor("TextField.inactiveForeground"));
		g.drawString(clippedHint, textR.x,
		    textR.y + metrics.getAscent());
	    }

	    if (icon != null) {
		icon.paintIcon(this, g, iconR.x, iconR.y);
	    }
	}
    }

    //
    // HintTextField methods
    //

    public String getHintText() {
	return hint;
    }

    public void setHintText(String hint) {
	this.hint = hint;
	repaint();
    }

    public Icon getHintIcon() {
	return icon;
    }

    public void setHintIcon(Icon icon) {
	this.icon = icon;
	repaint();
    }

    public int getIconTextGap() {
	return iconTextGap;
    }

    public void setIconTextGap(int iconTextGap) {
	this.iconTextGap = iconTextGap;
	repaint();
    }

    public int getHintHorizontalAlignment() {
	return horizontalAlignment;
    }

    public void setHintHorizontalAlignment(int horizontalAlignment) {
	this.horizontalAlignment = horizontalAlignment;
	repaint();
    }

    //
    // Private methods
    //

    private void init() {
	setIconTextGap(4);
	setHintHorizontalAlignment(getHorizontalAlignment());
	setBackground(Color.white);
	addFocusListener(this);
    }

    //
    // Static methods
    //

    public static void main(String[] args) {
        HintTextField field = new HintTextField();
	field.setHintText("icon and text");
	field.setHintIcon(ICON_FIND);

        HintTextField field2 = new HintTextField();
	field2.setHintText("text only");
	field2.setHintIcon(null);
	field2.setColumns(12);

        HintTextField field3 = new HintTextField();
	field3.setHintText("opaque");
	field3.setHintIcon(null);
	field3.setColumns(12);
	field3.setOpaque(false);

        HintTextField field4 = new HintTextField();
	field4.setHintText("centered");
	field4.setHintIcon(null);
	field4.setColumns(12);
	field4.setHintHorizontalAlignment(SwingConstants.CENTER);

        HintTextField field5 = new HintTextField();
	field5.setHintText("right");
	field5.setHintIcon(null);
	field5.setColumns(12);
	field5.setHintHorizontalAlignment(SwingConstants.RIGHT);

	JPanel panel = new JPanel(new ColumnLayout(VerticalAnchor.FILL));
	panel.setBorder(GUIUtil.getEmptyBorder());

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, GUIUtil.getGap(), 1);
	panel.add(field, c);
	panel.add(field2, c);
	panel.add(field3, c);
	panel.add(field4, c);
	panel.add(field5, c);

        JFrame frame = new JFrame();
        frame.getContentPane().add(panel);
        frame.pack();
        frame.setVisible(true);
    }
}
