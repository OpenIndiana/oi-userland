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
import java.awt.geom.Rectangle2D;
import java.awt.geom.Rectangle2D.Float;
import java.awt.image.BufferedImage;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.swing.*;

public class ObjectsHeader extends JPanel {
    //
    // Static data
    //

    static final int arc = 18;

    //
    // Instance data
    //

    private JLabel titleLabel;
    private ManagedObject pObject;
    private InfoLabel info;

    //
    // Constructors
    //

    public ObjectsHeader() {
	setOpaque(false);

	titleLabel = new JLabel();
	titleLabel.setForeground(Color.white);
	Font font = titleLabel.getFont();
	font = font.deriveFont(Font.BOLD);
	titleLabel.setFont(font);

	info = new InfoLabel() {
	    @Override
	    public void setToolTipText(String text) {
		super.setToolTipText(text);
		setVisible(text != null);
	    }
	};


	int gap = GUIUtil.getHalfGap();
	setLayout(new BorderLayout(gap, gap));
	add(titleLabel, BorderLayout.WEST);
	add(info, BorderLayout.EAST);

	int hGap = arc >> 1;
	int vGap = arc >> 2;
	setBorder(BorderFactory.createEmptyBorder(vGap, hGap, vGap, hGap));
    }

    //
    // JComponent methods
    //

    @Override
    public void paintComponent(Graphics g) {
	int w = getWidth();
	int h = getHeight();

	BufferedImage bImage = new BufferedImage(
	    w, h, BufferedImage.TYPE_INT_ARGB);

	Graphics2D g2 = bImage.createGraphics();
	g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
	    RenderingHints.VALUE_ANTIALIAS_ON);

	// Make all pixels in the BufferedImage transparent initially
	g2.setComposite(AlphaComposite.getInstance(AlphaComposite.CLEAR, 0.0f));
	g2.fill(new Rectangle2D.Float(0, 0, w, h));

	// Reset alpha
	g2.setPaintMode();

	GradientPaint gradient = new GradientPaint(0, 0,
	    ObjectsPanel.COLOR_HEADER_START, 0, h,
	    ObjectsPanel.COLOR_HEADER_END, true);

	g2.setPaint(gradient);
	g2.fillRoundRect(0, 0, w, h * 2, arc, arc);

	// Release resources
	g2.dispose();

	// Render image
	g.drawImage(bImage, 0, 0, null);

	super.paintComponent(g);
    }

    //
    // ObjectsHeader methods
    //

    public InfoLabel getInfoLabel() {
	return info;
    }

    public JLabel getTitleLabel() {
	return titleLabel;
    }

    public void setTitle(String title) {
	titleLabel.setText(title);
    }

    public void setHelp(String help) {
	info.setToolTipText(help);
    }
}
