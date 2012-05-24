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

import java.awt.CardLayout;
import java.awt.image.BufferedImage;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;

public class AnimationPanel extends JPanel implements ChangeListener {
    //
    // Static data
    //

    private static final String CARD_COMPONENT = "comp";

    //
    // Instance data
    //

    private JComponent comp;
    private ComponentAnimation current;
    private Map<String, ComponentAnimation> map =
	new HashMap<String, ComponentAnimation>();
    private boolean running;

    //
    // Constructors
    //

    public AnimationPanel(JComponent comp) {
	this.comp = comp;
	setLayout(new CardLayout());
	add(comp, CARD_COMPONENT);
    }

    //
    // ChangeListener methods
    //

    @Override
    public void stateChanged(ChangeEvent e) {
	if (e.getSource() == current) {
	    animationStopped();
	}
    }

    //
    // AnimationPanel methods
    //

    public void addAnimation(ComponentAnimation anim) {
	String id = anim.getId();
	if (!map.containsKey(id)) {
	    map.put(id, anim);
	    add(anim.getComponent(), id);
	    anim.addChangeListener(this);
	}
    }

    public void init(String id) {
	ComponentAnimation anim = map.get(id);
	BufferedImage before = GraphicsUtil.paintToImage(comp);
	anim.init(before);
	((CardLayout)getLayout()).show(this, id);
	current = anim;
	running = true;
    }

    public boolean isRunning() {
	return running;
    }

    public void removeAnimation(ComponentAnimation anim) {
	String id = anim.getId();
	if (map.containsKey(id)) {
	    map.remove(id);
	    remove(anim.getComponent());
	    anim.removeChangeListener(this);
	}
    }

    public void start() {
	BufferedImage after = GraphicsUtil.paintToImage(comp);
	current.start(after);
    }

    public void stop() {
	if (isRunning()) {
	    current.stop();
	    animationStopped();
	}
    }

    //
    // Private methods
    //

    private void animationStopped() {
	((CardLayout)getLayout()).show(this, CARD_COMPONENT);
	running = false;
    }
}
