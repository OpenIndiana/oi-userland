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
import java.util.*;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class TokenLabel extends JLabel {
    //
    // Inner classes
    //

    protected static class TokenRenderInfo {
	//
	// Instance data
	//

	private String token;
	private String tooltip;
	private Color background;

	//
	// Constructors
	//

	public TokenRenderInfo(String token, String tooltip, Color background) {
	    this.token = token;
	    this.tooltip = tooltip;
	    this.background = background;
	}

	//
	// TokenRenderInfo methods
	//

	public String getToken() {
	    return token;
	}

	public String getToolTip() {
	    return tooltip;
	}

	public Color getBackground() {
	    return background;
	}
    }

    //
    // Static data
    //

    protected static final Border BORDER;
    static {
	Border line = BorderFactory.createLineBorder(Color.black, 1);
	Border space = BorderFactory.createEmptyBorder(0, 1, 0, 1);
	BORDER = BorderFactory.createCompoundBorder(space, line);
    }

    protected static final Map<String, TokenRenderInfo> RENDER_INFO =
	new HashMap<String, TokenRenderInfo>();

    static {
	for (int i = 0; i < PathDocument.TOKENS.length; i++) {
	    String token = PathDocument.TOKENS[i];
	    String toolTip = Finder.getString("path.token.label." + token);
	    Color bg;

	    switch (i) {
		case 0: bg = ColorUtil.lighter(Color.blue, .25f); break;
		case 1: bg = ColorUtil.lighter(Color.green, .25f); break;
		case 2: bg = ColorUtil.lighter(Color.red, .25f); break;
		case 3: bg = Color.yellow; break;
		case 4: bg = Color.gray; break;

		case 5: bg = ColorUtil.lighter(Color.blue, .5f); break;
		case 6: bg = ColorUtil.lighter(Color.green, .75f); break;
		case 7: bg = ColorUtil.lighter(Color.red, .5f); break;
		case 8: bg = ColorUtil.lighter(Color.yellow, .75f); break;
		default: bg = ColorUtil.lighter(Color.gray, .5f); break;
	    }

	    RENDER_INFO.put(token, new TokenRenderInfo(token, toolTip, bg));
	}
    }

    //
    // Instance data
    //

    private boolean initialized = false;

    //
    // Constructors
    //

    public TokenLabel() {
	addMouseListener(ToolTipDelayOverrider.IMMEDIATE);
	setBorder(BORDER);

	initialized = true;
	calculateAlignmentY();
    }

    public TokenLabel(String token) {
	this();
	setText(token);
    }

    //
    // Component methods
    //

    @Override
    public void setFont(Font font) {
	super.setFont(font);

	// getPreferredSize throws a NullPointerException under synth if called
	// before the superclass is initialized
	if (initialized) {
	    calculateAlignmentY();
	}
    }

    //
    // JComponent methods
    //

    @Override
    public void paintComponent(Graphics g) {
	Insets insets = getInsets();
	Dimension size = getSize();

	g.setColor(getBackground());
	g.fillRect(insets.left, insets.top,
	    size.width - insets.left - insets.right,
	    size.height - insets.top - insets.bottom);

	super.paintComponent(g);
    }

    //
    // JLabel methods
    //

    @Override
    public void setText(String token) {
	super.setText(token);

	TokenRenderInfo info = RENDER_INFO.get(token);
	if (info != null) {
	    setToolTipText(info.getToolTip());
	    setBackground(info.getBackground());
	}
    }

    //
    // TokenLabel methods
    //

    protected void calculateAlignmentY() {
	FontMetrics metrics = getFontMetrics(getFont());
	int ascent = metrics.getAscent();
	int top = getInsets().top;
	int height = getPreferredSize().height;
	float hAlign = (float)(ascent + top) / (float)height;
	setAlignmentY(hAlign);
    }
}
