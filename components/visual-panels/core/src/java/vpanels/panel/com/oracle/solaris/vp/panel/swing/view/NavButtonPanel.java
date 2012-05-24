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

import java.awt.EventQueue;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class NavButtonPanel extends JPanel {
    //
    // Static data
    //

    private static final Icon ICON_BACK;
    private static final Icon ICON_FORWARD;

    static {
	int height = GUIUtil.getButtonIconHeight();
	Icon icon = GnomeUtil.getIcon("back", height, true);
	if (icon == null) {
	    icon = Finder.getIcon("images/navigation/back.png");
	}
	ICON_BACK = icon;

	icon = GnomeUtil.getIcon("forward", height, true);
	if (icon == null) {
	    icon = Finder.getIcon("images/navigation/forward.png");
	}
	ICON_FORWARD = icon;
    }

    private static final String TOOLTIP_BACK =
	Finder.getString("navigation.back.long");

    private static final String TOOLTIP_FORWARD =
	Finder.getString("navigation.forward.long");

    //
    // Instance data
    //

    private Navigator navigator;
    private JButton backButton;
    private JButton forwardButton;

    private NavigationListener navListener =
	new NavigationListener() {
	    @Override
	    public void navigationStarted(NavigationStartEvent e) {
	    }

	    @Override
	    public void navigationStopped(NavigationStopEvent e) {
		addCurrentToHistory(e.getSource());
	    }
	};

    private HistoryList<List<Navigable>> history =
	new HistoryList<List<Navigable>>();

    private boolean goingBack;

    //
    // Constructors
    //

    public NavButtonPanel() {
	createNavButtons();

	setLayout(new RowLayout(HorizontalAnchor.FILL));

	int gap = GUIUtil.getHalfGap();

	RowLayoutConstraint r =
	    new RowLayoutConstraint(VerticalAnchor.CENTER);

	add(backButton, r);
	add(forwardButton, r);
    }

    public NavButtonPanel(Navigator navigator) {
	this();
	setNavigator(navigator);
    }

    //
    // NavButtonPanel methods
    //

    public JButton getBackButton() {
	return backButton;
    }

    public JButton getForwardButton() {
	return forwardButton;
    }

    public Navigator getNavigator() {
	return navigator;
    }

    /**
     * Navigates backward through the navigation history.
     *
     * @exception   NoSuchElementException
     *		    if there is no previous entry in the history
     */
    public void goBack() {
	List<Navigable> target = history.peekOrErr(1);
	goingBack = true;

	try {
	    Navigable[] path = target.toArray(new Navigable[target.size()]);
	    navigator.goTo(false, null, path);
	} catch (NavigationException ignore) {

	} finally {
	    goingBack = false;
	}
    }

    /**
     * Navigates forward through the navigation history.
     *
     * @exception   NoSuchElementException
     *		    if there is no following entry in the history
     */
    public void goForward() {
	List<Navigable> target = history.peekForward();

	try {
	    Navigable[] path = target.toArray(new Navigable[target.size()]);
	    navigator.goTo(false, null, path);
	} catch (NavigationException ignore) {
	}
    }

    public void setNavigator(Navigator navigator) {
	Navigator oldNav = getNavigator();
	if (!ObjectUtil.equals(oldNav, navigator)) {
	    if (oldNav != null) {
		oldNav.removeNavigationListener(navListener);
	    }

	    if (navigator != null) {
		navigator.addNavigationListener(navListener);
	    }

	    this.navigator = navigator;
	}
    }

    //
    // Private methods
    //

    private void addCurrentToHistory(Navigator navigator) {
	List<Control> path = navigator.getPath();

	if (!isCurrent(path)) {
	    boolean addPath = true;
	    if (goingBack) {
		try {
		    history.goBack();
		    if (isCurrent(path)) {
			addPath = false;
		    }
		} catch (NoSuchElementException ignore) {
		}
	    }

	    if (addPath) {
		List<Navigable> savedPath =
		    new ArrayList<Navigable>(path.size());

		for (int i = 0, n = path.size(); i < n; i++) {
		    Control control = path.get(i);

		    // First element of Navigable array must be a Control -- see
		    // Navigator.goTo
		    Navigable navigable = i == 0 ? control :
			new SimpleNavigable(control.getId(), control.getName(),
			control.getParameters());

		    savedPath.add(navigable);
		}

		if (isNext(path)) {
		    history.goForward();
		} else {
		    history.push(savedPath);
		}
	    }

	    EventQueue.invokeLater(
		new Runnable() {
		    @Override
		    public void run() {
			setButtonsEnabledState();
		    }
		});
	}
    }

    private void createNavButtons() {
	backButton = new JButton(ICON_BACK);
	backButton.setToolTipText(TOOLTIP_BACK);
	backButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    // Launch navigation on non-event thread
		    navigator.asyncExec(
			new Runnable() {
			    @Override
			    public void run() {
				goBack();
			    }
			});
		}
	    });

        int bMargin = GUIUtil.getToolBarButtonMargin();
	GUIUtil.setHorizontalMargin(backButton, bMargin);

	new RolloverHandler(backButton);

	forwardButton = new JButton(ICON_FORWARD);
	forwardButton.setToolTipText(TOOLTIP_FORWARD);
	forwardButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    // Launch navigation on non-event thread
		    navigator.asyncExec(
			new Runnable() {
			    @Override
			    public void run() {
				goForward();
			    }
			});
		}
	    });

	GUIUtil.setHorizontalMargin(forwardButton, bMargin);

	new RolloverHandler(forwardButton);

	setButtonsEnabledState();
    }

    private boolean equals(List<? extends Navigable> pathA,
	List<? extends Navigable> pathB) {

	boolean retVal = false;

	if (pathA.size() == pathB.size()) {
	    retVal = true;
	    for (int i = 0, n = pathA.size(); i < n; i++) {
		if (!Navigable.Util.equals(pathA.get(i), pathB.get(i))) {
		    retVal = false;
		    break;
		}
	    }
	}

	return retVal;
    }

    private boolean isCurrent(List<? extends Navigable> path) {
	try {
	    return equals(path, history.peekOrErr());
	} catch (NoSuchElementException e) {
	    return false;
	}
    }

    private boolean isNext(List<? extends Navigable> path) {
	try {
	    return equals(path, history.peekForward());
	} catch (NoSuchElementException e) {
	    return false;
	}
    }

    private void setButtonsEnabledState() {
	backButton.setEnabled(history.getPointer() > 1);
	forwardButton.setEnabled(history.getPointer() !=
	    history.getFullCount());
    }
}
