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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.*;
import java.awt.image.BufferedImage;
import javax.swing.*;
import org.jdesktop.animation.timing.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.util.swing.GraphicsUtil;
import com.oracle.solaris.vp.util.swing.glass.ImageCaptureGlassPane;

public class ScrollingTransitionHandler
    implements NavigationListener, TimingTarget {

    //
    // Enums
    //

    public enum Direction {
	NORTH, SOUTH, EAST, WEST
    }

    //
    // Inner classes
    //

    @SuppressWarnings({"serial"})
    public static class ImageScrollGlassPane extends ImageCaptureGlassPane {
	//
	// Instance data
	//

	private Direction direction;
	private JViewport viewport = new JViewport();
	private JLabel beforeLabel = new JLabel();
	private JLabel afterLabel = new JLabel();
	private JPanel view = new JPanel(new BorderLayout());

	//
	// Constructors
	//

	public ImageScrollGlassPane(Direction direction) {
	    this.direction = direction;

	    switch (direction) {
		case NORTH:
		    view.add(beforeLabel, BorderLayout.NORTH);
		    view.add(afterLabel, BorderLayout.SOUTH);
		    break;

		case SOUTH:
		    view.add(beforeLabel, BorderLayout.SOUTH);
		    view.add(afterLabel, BorderLayout.NORTH);
		    break;

		case WEST:
		    view.add(beforeLabel, BorderLayout.WEST);
		    view.add(afterLabel, BorderLayout.EAST);
		    break;

		case EAST:
		    view.add(beforeLabel, BorderLayout.EAST);
		    view.add(afterLabel, BorderLayout.WEST);
		    break;
	    }

	    viewport.setView(view);
	    scroll(0);

	    JLabel label = getLabel();
	    label.setLayout(null);
	    label.add(viewport);
	}

	//
	// ImageScrollGlassPane methods
	//

	public void scroll(float fraction) {
	    if (fraction < 0) {
		fraction = 0f;
	    } else if (fraction > 1) {
		fraction = 1f;
	    }

	    Rectangle r = viewport.getViewRect();

	    switch (direction) {
		case NORTH:
		    r.y = (int)(fraction * r.height);
		    break;

		case SOUTH:
		    r.y = (int)((1f - fraction) * r.height);
		    break;

		case WEST:
		    r.x = (int)(fraction * r.width);
		    break;

		case EAST:
		    r.x = (int)((1f - fraction) * r.width);
		    break;
	    }

	    view.scrollRectToVisible(r);
	}

	public void setAfterImage(BufferedImage image) {
	    afterLabel.setIcon(image == null ? null : new ImageIcon(image));
	}

	public void setBeforeImage(BufferedImage image) {
	    beforeLabel.setIcon(image == null ? null : new ImageIcon(image));
	}

	public void setViewBounds(Rectangle rectangle) {
	    viewport.setBounds(rectangle);
	}
    };

    //
    // Instance data
    //

    private JComponent component;
    private ImageScrollGlassPane glass;
    private Animator animator = new Animator(500, this);
    private boolean running;

    //
    // Constructors
    //

    public ScrollingTransitionHandler(
	JComponent component, Direction direction) {

	this.component = component;

	glass = new ImageScrollGlassPane(direction);
    }

    //
    // NavigationListener methods
    //

    @Override
    public void navigationStarted(NavigationStartEvent event) {
	if (!running) {
	    running = true;
	    Rectangle bounds = SwingUtilities.convertRectangle(
		component.getParent(), component.getBounds(),
		component.getRootPane());

	    glass.setViewBounds(bounds);
	    glass.setBeforeImage(GraphicsUtil.paintToImage(component));

	    // Hide component, then take a snapshot of the resulting root pane
	    component.setVisible(false);
	    component.getRootPane().setGlassPane(glass);

	    // Display the snapshot in the glass pane, then reshow the component
	    glass.setVisible(true);
	    component.setVisible(true);
	}
    }

    @Override
    public void navigationStopped(NavigationStopEvent event) {
	// We are presumably on the event queue thread.  So, let navigation
	// complete so that the new component is shown before we try to paint it
	// to an image.  Once done, start the animation.
	EventQueue.invokeLater(
	    new Runnable() {
		@Override
		public void run() {
		    glass.setAfterImage(GraphicsUtil.paintToImage(component));
		    glass.scroll(0);
		    animator.start();
		}
	    });
	running = false;
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
	glass.setVisible(false);
	glass.setBeforeImage(null);
	glass.setAfterImage(null);
    }

    @Override
    public void repeat() {
    }

    @Override
    public void timingEvent(float fraction) {
	glass.scroll(fraction);
    }

    //
    // ScrollingTransitionHandler methods
    //

    public Animator getAnimator() {
	return animator;
    }
}
