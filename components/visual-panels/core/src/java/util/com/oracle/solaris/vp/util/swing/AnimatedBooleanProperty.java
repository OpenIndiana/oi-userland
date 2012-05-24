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

import java.awt.EventQueue;
import org.jdesktop.animation.timing.*;
import org.jdesktop.animation.timing.Animator.Direction;

@SuppressWarnings({"serial"})
public class AnimatedBooleanProperty implements TimingTarget {
    //
    // Instance data
    //

    private boolean value;
    private Animator animator;
    private TimingTarget target;

    //
    // Constructors
    //

    public AnimatedBooleanProperty(int duration, TimingTarget target) {
	this.target = target;
	animator = new Animator(duration, this);
    }

    public AnimatedBooleanProperty(int duration) {
	this(duration, null);
    }

    //
    // TimingTarget methods
    //

    @Override
    public void begin() {
	if (target != null) {
	    target.begin();
	}
    }

    @Override
    public void end() {
	if (target != null) {
	    target.end();
	}
    }

    @Override
    public void repeat() {
	if (target != null) {
	    target.repeat();
	}
    }

    @Override
    public void timingEvent(float fraction) {
	if (target != null) {
	    target.timingEvent(fraction);
	}
    }

    //
    // AnimatedBooleanProperty methods
    //

    public Animator getAnimator() {
	return animator;
    }

    public boolean getValue() {
	return value;
    }

    public void setValue(final boolean value, boolean animated) {
	if (this.value != value) {
	    if (animated) {
		float start;
		if (animator.isRunning()) {
		    start = animator.getTimingFraction();
		    animator.stop();
		} else {
		    start = value ? 0f : 1f;
		}
		animator.setStartFraction(start);

		animator.setStartDirection(value ?
		    Animator.Direction.FORWARD : Animator.Direction.BACKWARD);

		this.value = value;

		animator.start();
	    } else {
		animator.stop();
		this.value = value;
		EventQueue.invokeLater(
		    new Runnable() {
			@Override
			public void run() {
			    timingEvent(value ? 1f : 0f);
			}
		    });
	    }
	}
    }

    public void setValue(boolean value) {
	setValue(value, true);
    }
}
