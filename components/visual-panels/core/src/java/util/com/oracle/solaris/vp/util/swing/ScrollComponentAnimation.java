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
import java.awt.image.BufferedImage;
import javax.swing.*;
import org.jdesktop.animation.timing.*;

public class ScrollComponentAnimation
    extends AbstractComponentAnimation<JViewport> {

    //
    // Enums
    //

    public enum Direction {
	NORTH, SOUTH, EAST, WEST
    }

    //
    // Instance data
    //

    private Direction direction;
    private Animator animator = new Animator(300, this);

    private JViewport viewport;
    private JLabel beforeLabel;
    private JLabel afterLabel;
    private JPanel view;

    //
    // Constructors
    //

    public ScrollComponentAnimation(String id, Direction direction) {
	super(id);
	beforeLabel = new JLabel();
	afterLabel = new JLabel();
	view = new JPanel(new BorderLayout());
	view.setOpaque(false);

	setDirection(direction);

	viewport = new JViewport() {
	    @Override
	    public Dimension getPreferredSize() {
		return beforeLabel.getPreferredSize();
	    }
	};
	viewport.setOpaque(false);
	viewport.setView(view);
	scroll(0);
    }

    public ScrollComponentAnimation(String id) {
	this(id, Direction.WEST);
    }

    //
    // HasComponent methods
    //

    @Override
    public JViewport getComponent() {
	return viewport;
    }

    //
    // TimingTarget methods
    //

    @Override
    public void end() {
	super.end();
	animationStopped();
    }

    @Override
    public void timingEvent(float fraction) {
	scroll(fraction);
    }

    //
    // ComponentAnimation methods
    //

    @Override
    public void init(BufferedImage before) {
	beforeLabel.setIcon(toImageIcon(before));
    }

    @Override
    public void start(BufferedImage after) {
	afterLabel.setIcon(toImageIcon(after));
	scroll(0);
	animator.start();
    }

    @Override
    public void stop() {
	animator.stop();
	animationStopped();
    }

    //
    // ScrollComponentAnimation methods
    //

    public Animator getAnimator() {
	return animator;
    }

    public Direction getDirection() {
	return direction;
    }

    public void setDirection(Direction direction) {
	this.direction = direction;

	view.removeAll();
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
    }

    //
    // Private methods
    //

    private void animationStopped() {
	beforeLabel.setIcon(null);
	afterLabel.setIcon(null);
    }

    private void scroll(float fraction) {
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

    private ImageIcon toImageIcon(BufferedImage image) {
	return image == null ? null : new ImageIcon(image);
    }
}
