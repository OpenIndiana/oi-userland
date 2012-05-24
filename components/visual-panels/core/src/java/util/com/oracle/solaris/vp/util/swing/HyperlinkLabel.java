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
import java.awt.font.TextAttribute;
import java.util.HashMap;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.util.swing.event.ActionListeners;

@SuppressWarnings({"serial"})
public class HyperlinkLabel extends JLabel {
    //
    // Enums
    //

    public enum UnderlinePolicy {
	ALWAYS,
	NEVER,

	// Underline only when hovering over link
	HOVER,

	// Underline only when not hovering over link
	NOHOVER,
    };

    //
    // Static data
    //

    public static final String KEY_UNVISITED = "HyperlinkLabel.unvisited";
    public static final String KEY_VISITED = "HyperlinkLabel.visited";
    public static final String KEY_UNDERLINE_POLICY = "HyperlinkLabel.upolicy";

    static {
	if (UIManager.getColor(KEY_UNVISITED) == null) {
	    UIManager.put(KEY_UNVISITED, new Color(0, 0, 204));
	}
	if (UIManager.getColor(KEY_VISITED) == null) {
	    UIManager.put(KEY_VISITED, new Color(128, 0, 128));
	}
	if (UIManager.get(KEY_UNDERLINE_POLICY) == null) {
	    UIManager.put(KEY_UNDERLINE_POLICY, UnderlinePolicy.HOVER);
	}
    }

    //
    // Instance data
    //

    private ActionListeners listeners = new ActionListeners();
    private boolean visited;
    private boolean underline;
    private boolean active;
    private Color unvisitedColor = UIManager.getColor(KEY_UNVISITED);
    private Color visitedColor = UIManager.getColor(KEY_VISITED);
    private UnderlinePolicy policy;

    private FocusListener focusListener =
	new FocusListener() {
	    @Override
	    public void focusGained(FocusEvent e) {
		repaint();
	    }

	    public void focusLost(FocusEvent e) {
		repaint();
	    }
	};

    private MouseListener mouseFocusListener =
	new MouseAdapter() {
	    public void mousePressed(MouseEvent e) {
		requestFocusInWindow();
	    }
	};

    private Border focusBorder;

    //
    // Constructors
    //

    public HyperlinkLabel(String title, UnderlinePolicy policy) {
	super(title);

	setUnderlinePolicy(policy);
	setVisited(false);
	setFocusable(true);
	setActive(true);

	Action clickAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    click();
		}
	    };

	GUIUtil.installKeyBinding(this, JComponent.WHEN_FOCUSED,
	    "clicked", clickAction, KeyEvent.VK_ENTER, KeyEvent.VK_SPACE);

	final MouseListener mListener = new MouseAdapter() {
	    @Override
	    public void mouseClicked(MouseEvent e) {
		click();
	    }

	    @Override
	    public void mouseEntered(MouseEvent e) {
		// Set underlining depending on policy
		underline = true;
		switch (getUnderlinePolicy()) {
		    case NEVER:
		    case NOHOVER:
			underline = false;
		}
		setFont(getFont());
	    }

	    @Override
	    public void mouseExited(MouseEvent e) {
		// Set underlining depending on policy
		underline = false;
		switch (getUnderlinePolicy()) {
		    case ALWAYS:
		    case NOHOVER:
			underline = true;
		}
		setFont(getFont());
	    }
	};
	addMouseListener(mListener);

	// Set initial underline state
	mListener.mouseExited(null);

	addHierarchyListener(
	    new HierarchyListener() {
		@Override
		public void hierarchyChanged(HierarchyEvent e) {
		    if ((e.getChangeFlags() & HierarchyEvent.SHOWING_CHANGED)
			!= 0 && !isShowing()) {
			mListener.mouseExited(null);
		    }
		}
	    });
    }

    public HyperlinkLabel(String title) {
	this(title, (UnderlinePolicy)UIManager.get(KEY_UNDERLINE_POLICY));
    }

    public HyperlinkLabel() {
	this("");
    }

    //
    // Component methods
    //

    @Override
    public void setFocusable(boolean focusable) {
	removeFocusListener(focusListener);
	removeMouseListener(mouseFocusListener);
	if (focusable) {
	    addFocusListener(focusListener);
	    addMouseListener(mouseFocusListener);
	}

	super.setFocusable(focusable);
    }

    @Override
    public void setFont(Font font) {
	if (font != null) {
	    HashMap<TextAttribute, Object> attrs =
		new HashMap<TextAttribute, Object>();
	    attrs.put(TextAttribute.UNDERLINE, underline && active ?
		TextAttribute.UNDERLINE_ON : -1);

	    font = font.deriveFont(attrs);
	}

	super.setFont(font);
    }

    //
    // JComponent methods
    //

    @Override
    public void setBorder(Border border) {
	if (focusBorder == null) {
	    focusBorder = new FocusBorder();
	}

	Border compound = border == null ? focusBorder :
	    BorderFactory.createCompoundBorder(border, focusBorder);

	super.setBorder(compound);
    }

    //
    // HyperlinkLabel methods
    //

    public void addActionListener(ActionListener listener) {
	listeners.add(listener);
    }

    protected void fireActionPerformed(ActionEvent e) {
	listeners.actionPerformed(e);
    }

    public boolean getActive() {
	return active;
    }

    public UnderlinePolicy getUnderlinePolicy() {
	return policy;
    }

    public Color getUnvisitedColor() {
	return unvisitedColor;
    }

    public boolean getVisited() {
	return visited;
    }

    public Color getVisitedColor() {
	return visitedColor;
    }

    public boolean removeActionListener(ActionListener listener) {
	return listeners.remove(listener);
    }

    public void setActive(boolean active) {
	this.active = active;
	setCursor(active ? Cursor.getPredefinedCursor(Cursor.HAND_CURSOR) :
	    null);
	setFocusable(active);
	setFont(getFont());
	setForeground();
    }

    public void setColor(Color color) {
	unvisitedColor = visitedColor = color;
	setForeground();
    }

    public void setUnderlinePolicy(UnderlinePolicy policy) {
	this.policy = policy;
    }

    public void setUnvisitedColor(Color unvisitedColor) {
	this.unvisitedColor = unvisitedColor;
	setForeground();
    }

    public void setVisited(boolean visited) {
	this.visited = visited;
	setForeground();
    }

    public void setVisitedColor(Color visitedColor) {
	this.visitedColor = visitedColor;
	setForeground();
    }

    //
    // Private methods
    //

    private void click() {
	if (active) {
	    ActionEvent e = new ActionEvent(HyperlinkLabel.this,
		ActionEvent.ACTION_PERFORMED, null);
	    fireActionPerformed(e);
	    setVisited(true);
	}
    }

    private void setForeground() {
	setForeground(visited ? getVisitedColor() : getUnvisitedColor());
    }
}
