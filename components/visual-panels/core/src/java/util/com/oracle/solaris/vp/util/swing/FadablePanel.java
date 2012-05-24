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

import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import javax.swing.*;
import javax.swing.border.*;
import org.jdesktop.animation.timing.*;

@SuppressWarnings({"serial"})
public class FadablePanel extends JPanel implements TimingTarget {
    //
    // Instance data
    //

    private AlphaComposite composite;
    private BufferedImage image;
    private boolean useImageBuffer;

    private AnimatedBooleanProperty faded =
	new AnimatedBooleanProperty(500, this);

    private ShowingListener showListener =
	new ShowingListener() {
	    @Override
	    public void componentHidden() {
		setFaded(true, false);
	    }

	    public void componentShown() {
		setFaded(false);
	    }
	};

    //
    // Constructors
    //

    public FadablePanel(LayoutManager layout) {
	setLayout(layout == null ? new BorderLayout() : layout);
	setOpaque(false);
    }

    public FadablePanel() {
	this((LayoutManager)null);
    }

    public FadablePanel(JComponent c) {
	this();
	add(c, BorderLayout.CENTER);
    }

    //
    // TimingTarget methods
    //

    @Override
    public void begin() {
	// No implementation here -- setup should occur before the animator is
	// started since the clock is ticking at this point.  A design flaw in
	// the timing framework?  Perhaps.
    }

    @Override
    public void end() {
	image = null;
    }

    @Override
    public void repeat() {
    }

    @Override
    public void timingEvent(float alpha) {
	setAlpha(1f - alpha);
	repaint();
    }

    //
    // Component methods
    //

    @Override
    public void paint(Graphics g) {
	Composite composite = this.composite;
	if (composite == null) {
	    super.paint(g);
	    return;
	}

	Graphics2D g2 = (Graphics2D)g;
	Composite old = g2.getComposite();
	g2.setComposite(composite);

	if (useImageBuffer) {
	    if (image == null) {
		// We have just begun animating -- paint initially to an image
		image = new BufferedImage(getWidth(), getHeight(),
		    BufferedImage.TYPE_INT_ARGB);
		Graphics2D iG = image.createGraphics();
		super.paint(iG);
	    }

	    g2.drawImage(image, 0, 0, null);
	} else {
	    super.paint(g2);
	}

	g2.setComposite(old);
    }

    //
    // FadablePanel methods
    //

    public float getAlpha() {
	return composite == null ? 1f : composite.getAlpha();
    }

    public Animator getAnimator() {
	return faded.getAnimator();
    }

    public boolean getUseImageBuffer() {
	return useImageBuffer;
    }

    public boolean isFaded() {
	return faded.getValue();
    }

    public void setAlpha(float alpha) {
	this.composite = alpha == 1f ? null : AlphaComposite.getInstance(
	    AlphaComposite.SRC_OVER, alpha);
    }

    public void setFaded(boolean value) {
	setFaded(value, isShowing());
    }

    public void setFaded(boolean value, boolean animated) {
	faded.setValue(value, animated);
    }

    /**
     * Synchronizes the fade of this component with its visibility.  When this
     * {@code FadePanel} becomes both visible and displayable, it fades in.
     * When this {@code FadePanel} loses either visibility or displayability, it
     * fades out.
     * <p>
     * This synchronization may facilitate using a {@code FadePanel} as a glass
     * pane.
     *
     * @param	    synch
     *		    {@code true} to establish this link, {@code false} to remove
     *		    this link if set up previously
     */
    public void setSyncFadeWithVisibility(boolean synch) {
	if (synch) {
	    // Make sure listener is only added once
	    removeListener();

	    addHierarchyListener(showListener);
	    showListener.updateShowing(this);
	} else {
	    removeListener();
	}
    }

    public void setUseImageBuffer(boolean useImageBuffer) {
	this.useImageBuffer = useImageBuffer;
    }

    //
    // Private methods
    //

    private void removeListener() {
	removeHierarchyListener(showListener);
    }

    //
    // Static methods
    //

    // XXX Unit test - remove
    public static void main(String args[]) {
	JButton b1 = new JButton("Hello");
	JLabel b2 = new JLabel("There");

	Border border = new CompoundBorder(
	    new EmptyBorder(5, 5, 5, 5),
	    new LineBorder(ColorUtil.getRandomColor(), 5));

	JPanel p = new JPanel(new GridLayout());
	p.setBackground(ColorUtil.getRandomColor());
	p.setBorder(border);
	p.add(b1);
	p.add(b2);

	final FadablePanel fadePanel = new FadablePanel(p);
	fadePanel.setBorder(border);

	JButton fadeButton = new JButton("fade");
	fadeButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    boolean faded = fadePanel.isFaded();
		    fadePanel.setFaded(!faded);
		}
	    });

	JButton fadeNowButton = new JButton("fade immediately");
	fadeNowButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    boolean faded = fadePanel.isFaded();
		    fadePanel.setFaded(!faded, false);
		}
	    });

	JButton stopButton = new JButton("stop");
	stopButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    fadePanel.getAnimator().stop();
		}
	    });

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setBackground(Color.red);
	c.setLayout(new GridLayout());
	c.add(fadePanel);
	c.add(fadeButton);
	c.add(fadeNowButton);
	c.add(stopButton);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	Dimension d = frame.getSize();
	frame.setSize(d.width * 2, d.height * 2);
	frame.setVisible(true);
    }
}
