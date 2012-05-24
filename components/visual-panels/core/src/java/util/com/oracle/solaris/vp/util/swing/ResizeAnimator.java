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
import org.jdesktop.animation.timing.*;

/**
 * The {@code ResizeAnimator} class animates the resize of a {@code Component}.
 * <p>
 * See {@link #setTargetSize} for details on how this resize is configured.
 */
@SuppressWarnings({"serial"})
public class ResizeAnimator implements TimingTarget {
    //
    // Static data
    //

    public static final int _SPEED = 1000;
    public static final int _MAX_DURATION = 300;
    public static final int _MIN_DURATION = 0;

    //
    // Instance data
    //

    private Animator animator;
    private Component component;
    private Dimension startSize;
    private Dimension targetSize;
    private int speed = _SPEED;
    private int minDuration = _MIN_DURATION;
    private int maxDuration = _MAX_DURATION;

    //
    // Constructors
    //

    /**
     * Constructs a {@code ResizeAnimator}.
     *
     * @param	    component
     *		    the {@code Component} to resize
     */
    public ResizeAnimator(Component component) {
	this.component = component;
	animator = new Animator(1, this);
    }

    /**
     * Constructs a {@code ResizeAnimator}, immediately resizing the given
     * {@code Component}.
     *
     * @param	    component
     *		    the {@code Component} to resize
     *
     * @param	    size
     *		    the new size of the {@code Component}
     */
    public ResizeAnimator(Component component, Dimension size) {
	this(component);
	setTargetSize(size);
    }

    /**
     * Constructs a {@code ResizeAnimator}.
     *
     * @param	    component
     *		    the {@code Component} to resize
     *
     * @param	    speed
     *		    the speed of the resize, in pixels per second
     */
    public ResizeAnimator(Component component, int speed) {
	this(component);
	setSpeed(speed);
    }

    /**
     * Constructs a {@code ResizeAnimator}, immediately resizing the given
     * {@code Component}.
     *
     * @param	    component
     *		    the {@code Component} to resize
     *
     * @param	    speed
     *		    the speed of the resize, in pixels per second
     *
     * @param	    size
     *		    the new size of the {@code Component}
     */
    public ResizeAnimator(Component component, int speed, Dimension size) {
	this(component, speed);
	setTargetSize(size);
    }

    //
    // TimingTarget methods
    //

    @Override
    public void begin() {
    }

    @Override
    public void end() {
    }

    @Override
    public void repeat() {
    }

    @Override
    public void timingEvent(float fraction) {
	int width = startSize.width +
	    (int)(fraction * (targetSize.width - startSize.width));

	int height = startSize.height +
	    (int)(fraction * (targetSize.height - startSize.height));

	component.setSize(width, height);
    }

    //
    // ResizeAnimator methods
    //

    /**
     * Gets the {@code Animator} responsible for the animation.
     */
    public Animator getAnimator() {
	return animator;
    }

    /**
     * Gets the maximum time (in milliseconds) that the resize animation should
     * take.  The default is 300.
     */
    public int getMaxDuration() {
	return maxDuration;
    }

    /**
     * Gets the minimum time (in milliseconds) that the resize animation should
     * take.  The default is 0.
     */
    public int getMinDuration() {
	return minDuration;
    }

    /**
     * Gets the speed of the resize, in pixels per second.
     */
    public int getSpeed() {
	return speed;
    }

    /**
     * Gets the {@code Dimension} passed to the most recent call to {@link
     * #setTargetSize}.
     */
    public Dimension getTargetSize() {
	return targetSize;
    }

    /**
     * Sets the maximum time (in milliseconds) that the resize animation should
     * take.
     */
    public void setMaxDuration(int maxDuration) {
	this.maxDuration = maxDuration;
    }

    /**
     * Sets the minimum time (in milliseconds) that the resize animation should
     * take.
     */
    public void setMinDuration(int minDuration) {
	this.minDuration = minDuration;
    }

    /**
     * Sets the speed of the resize, in pixels per second.
     */
    public void setSpeed(int speed) {
	this.speed = speed;
    }

    /**
     * Animates the resize of the {@code Component} to the given size.	The
     * duration of the animation is calculated based on the size of the change
     * and the {@link #getSpeed speed} property.  This value is adjusted to be
     * no less than the {@link #getMinDuration minimum duration}, and no greater
     * than the {@link #getMaxDuration maximum duration}.
     */
    public void setTargetSize(Dimension targetSize) {
	if (animator.isRunning()) {
	    animator.stop();
	}

	this.targetSize = targetSize;
	Dimension currentSize = component.getSize();

	if (!currentSize.equals(targetSize)) {
	    int deltaWidth = Math.abs(targetSize.width - currentSize.width);
	    int deltaHeight = Math.abs(targetSize.height - currentSize.height);
	    int maxDelta = Math.max(deltaWidth, deltaHeight);

	    int duration = (1000 * maxDelta) / speed;
	    int maxDuration = getMaxDuration();

	    if (maxDuration != 0 && duration > maxDuration) {
		duration = maxDuration;
	    } else

	    if (minDuration != 0 && duration < minDuration) {
		duration = minDuration;
	    }

	    animator.setDuration(duration);

	    startSize = currentSize;
	    animator.start();
	}
    }
}
