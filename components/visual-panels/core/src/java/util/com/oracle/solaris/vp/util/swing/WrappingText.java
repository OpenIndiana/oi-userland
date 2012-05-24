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
import java.util.ArrayList;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.TextUtil;

/**
 * The {@code WrappingText} class displays multi-line text, wrapping words
 * at whitespace.
 */
@SuppressWarnings({"serial"})
public class WrappingText extends JComponent {
    //
    // Instance data
    //

    private String text;
    private int prefWidth = -1;
    private boolean prefWidthIsStatic;

    //
    // Constructors
    //

    public WrappingText(String text, int columns) {
	setText(text);
	setFont(UIManager.getFont("TextField.font"));
	setForeground(UIManager.getColor("Label.foreground"));
	setBackground(UIManager.getColor("Label.background"));
	setPreferredWidthInColumns(columns);

	setOpaque(false);
    }

    public WrappingText(String text) {
	this(text, -1);
    }

    public WrappingText() {
	this("");
    }

    public WrappingText(int columns) {
	this("", -1);
    }

    //
    // Component methods
    //

    @Override
    public void setBounds(int x, int y, int width, int height) {
	super.setBounds(x, y, width, height);
	setPreferredWidth(width);
    }

    @Override
    public void setBounds(Rectangle r) {
	super.setBounds(r);
	setPreferredWidth(r.width);
    }

    @Override
    public Dimension getMinimumSize() {
	return getPreferredSize();
    }

    @Override
    public Dimension getPreferredSize() {
	if (isPreferredSizeSet()) {
	    return super.getPreferredSize();
	}

	Insets insets = getInsets();
	FontMetrics metrics = getFontMetrics(getFont());

	String[] lines = getLines(prefWidth < 0 ?
	    Integer.MAX_VALUE : prefWidth - insets.left - insets.right);

	// Get length of longest line
	int width = 0;
	for (int i = 0; i < lines.length; i++) {
	    width = Math.max(width, metrics.stringWidth(lines[i]));
	}

	width += insets.left + insets.right;

	// Set preferred width
	if (prefWidth < 0) {
	    prefWidth = width;
	}

	int height = lines.length * metrics.getHeight() + insets.top +
	    insets.bottom;

	return new Dimension(width, height);
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g) {

	// Turn on anti-aliasing if appropriate
	GUIUtil.setAARendering((Graphics2D)g);

	if (isOpaque()) {
	    g.setColor(getBackground());
	    g.fillRect(0, 0, getWidth(), getHeight());
	}

	Font font = getFont();
	FontMetrics metrics = getFontMetrics(font);
	int rowHeight = metrics.getHeight();

	Insets insets = getInsets();
	int y = insets.top + metrics.getAscent();
	String[] lines = getLines(getWidth() - insets.left - insets.right);

	g.setColor(getForeground());
	g.setFont(font);

	for (int i = 0; i < lines.length; i++) {
	    g.drawString(lines[i], insets.left, y);
	    y += rowHeight;
	}
    }

    //
    // WrappingText methods
    //

    /**
     * Gets the initial preferred width of this {@code WrappingText}.
     * Called by {@code getPreferredSize}.  The width here is determined by
     * the number of columns, the column width, and the insets of this
     * {@code Component}.
     *
     * @return	    the preferred width in pixels, or -1 if
     *		    {@code getPreferredSize} should determine it based on
     *		    the longest line in the text
     */
    public int getPreferredWidth() {
	return prefWidth;
    }

    public boolean getPreferredWidthIsStatic() {
	return prefWidthIsStatic;
    }

    /**
     * Sets the preferred width of this {@code WrappingText}, based on the given
     * number of columns.  This value ultimately determines the preferred
     * height.
     * <p>
     * If not specified, the initial preferred width is determined by the length
     * of the longest line of text.
     *
     * @param	    prefWidth
     *		    the preferred width, in pixels
     */
    public void setPreferredWidth(int prefWidth) {
	if (this.prefWidth != prefWidth && !prefWidthIsStatic) {
	    this.prefWidth = prefWidth;
	    revalidateLater();
	}
    }

    /**
     * Sets the preferred width of this {@code WrappingText}, based on the given
     * number of columns.  Column width is the width of the character 'm' in the
     * current font.
     *
     * @param	    columns
     *		    the preferred width, in columns
     */
    public void setPreferredWidthInColumns(int columns) {
	int prefWidth = 0;

	if (columns < 0) {
	    prefWidth = -1;
	} else {
	    int columnWidth = getFontMetrics(getFont()).charWidth('m');
	    Insets insets = getInsets();
	    prefWidth = columns * columnWidth + insets.left + insets.right;
	}

	setPreferredWidth(prefWidth);
    }

    public String getText() {
	return text;
    }

    public void setPreferredWidthIsStatic(boolean prefWidthIsStatic) {
	this.prefWidthIsStatic = prefWidthIsStatic;
    }

    public void setText(String text) {
	if (text == null) {
	    text = "";
	}
	this.text = text;
	revalidateLater();
	repaint();
    }

    //
    // Private methods
    //

    private String[] getLines(int width) {
	ArrayList<String> lines = new ArrayList<String>();
	FontMetrics metrics = getFontMetrics(getFont());
	String text = getText();

	// The current line
	StringBuilder line = new StringBuilder();

	// Space that will be added to current line as long as it's not the last
	// token in the line
	String pendingSpace = "";
	int pendingSpaceWidth = 0;

	String[] groups;
	int x = 0;
	while ((groups = TextUtil.match(text,
	    "^((\\r?\\n)|(\\s+)|(\\S+))((?s).*)")) != null) {

	    String newline = groups[2];
	    String space = groups[3];
	    String word = groups[4];
	    text = groups[5];

	    if (newline != null) {
		lines.add(line.toString());
		line.setLength(0);
		pendingSpace = "";
		pendingSpaceWidth = 0;
		x = 0;
	    } else

	    if (space != null) {
		pendingSpace = space;
		pendingSpaceWidth = metrics.stringWidth(pendingSpace);
	    } else

	    if (word != null) {
		int wordWidth = metrics.stringWidth(word);
		int newX = x + pendingSpaceWidth + wordWidth;

		// Will the pending space and this word fit on this line?
		if (newX <= width) {
		    line.append(pendingSpace).append(word);
		    x = newX;
		} else {
		    if (line.length() != 0) {
			lines.add(line.toString());
			line.setLength(0);
		    }

		    // Does this word fit on a line of its own?
		    if (wordWidth <= width) {
			line.append(word);
			x = wordWidth;
		    } else {
			// Split word
			char[] chars = word.toCharArray();
			x = 0;
			for (int i = 0; i < chars.length; i++) {
			    char c = chars[i];
			    int charWidth = metrics.charWidth(c);
			    x += charWidth;

			    // Has this line exceeded the maximum width?
			    if (x > width && line.length() != 0) {
				lines.add(line.toString());
				line.setLength(0);
				x = charWidth;
			    }

			    line.append(c);
			}
		    }
		}

		pendingSpace = "";
		pendingSpaceWidth = 0;
	    }
	}

	if (line.length() > 0) {
	    lines.add(line.toString());
	}

	return lines.toArray(new String[lines.size()]);
    }

    private void revalidateLater() {
	SwingUtilities.invokeLater(
	    new Runnable() {
		@Override
		public void run() {
		    revalidate();
		}
	    });
    }
}
