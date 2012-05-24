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
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class AddressPanel extends JPanel {
    //
    // Static data
    //

    private static final String CARD_BREADCRUMBS = "breadcrumbs";
    private static final String CARD_ADDRFIELD = "addrfield";
    private static final int RESERVED_CLICKABLE_WHITESPACE_WIDTH = 50;

    //
    // Instance data
    //

    private Navigator navigator;
    private ControlBreadCrumbs breadCrumbs;
    private JTextField textField;
    private JTextField bgField;
    private String address;

    private MouseListener showAddressListener =
	new MouseAdapter() {
	    @Override
	    public void mouseClicked(MouseEvent e) {
		showTextField(true);
	    }
	};

    private NavigationListener navListener =
	new NavigationListener() {
	    @Override
	    public void navigationStarted(NavigationStartEvent e) {
	    }

	    @Override
	    public void navigationStopped(final NavigationStopEvent e) {
		GUIUtil.invokeAndWait(
		    new Runnable() {
			@Override
			public void run() {
			    // getPath is safe here because invokeAndWait is
			    // (presumably) being run by the navigation thread
			    setAddress(e.getSource().getPath());
			}
		    });
	    }
	};

    //
    // Constructors
    //

    public AddressPanel() {
	createTextField();
	createBreadCrumbs();

	bgField = new JTextField();
	bgField.setEditable(false);

	// Automatically show and transfer focus to the real text field
	bgField.addFocusListener(
	    new FocusListener() {
		@Override
		public void focusGained(FocusEvent e) {
		    if (!e.isTemporary()) {
			showTextField(true);
		    }
		}

		@Override
		public void focusLost(FocusEvent e) {
		}
	    });

	// Reserve some whitespace following the bread crumbs in the layout, so
	// that there is always something the user can click on to switch to
	// address view, even when the AddressPanel is shrunk.
	Spacer whiteSpace = new Spacer(RESERVED_CLICKABLE_WHITESPACE_WIDTH, 1);
	whiteSpace.addMouseListener(showAddressListener);

	JPanel breadCrumbPanel = new JPanel(new BorderLayout());
	breadCrumbPanel.setOpaque(false);
	breadCrumbPanel.add(breadCrumbs, BorderLayout.CENTER);
	breadCrumbPanel.add(whiteSpace, BorderLayout.EAST);

	OverlayStackPanel sPanel = new OverlayStackPanel();
	sPanel.push(bgField);
	sPanel.push(breadCrumbPanel);

	CardLayout cards = new CardLayout();
	setLayout(cards);
	add(sPanel, CARD_BREADCRUMBS);
	add(textField, CARD_ADDRFIELD);
    }

    public AddressPanel(Navigator navigator) {
	this();
	setNavigator(navigator);
    }

    //
    // AddressPanel methods
    //

    public ControlBreadCrumbs getBreadCrumbs() {
	return breadCrumbs;
    }

    public Navigator getNavigator() {
	return navigator;
    }

    public JTextField getTextField() {
	return textField;
    }

    protected boolean isTextFieldChanged() {
	return textField.getText().equals(address);
    }

    public void setAddress(Collection<Control> path) {
	// If the breadcrumbs have focus when they are cleared, the focus will
	// be given to the faux text field, which automatically shows the real
	// text field and then forwards the focus to it (see its FocusListener).
	// To avoid this, make it temporarily unfocusable.
	bgField.setFocusable(false);
	breadCrumbs.setAddress(path);
	bgField.setFocusable(true);

	address = path == null ? null : Navigator.getPathString(path);
	textField.setText(address);
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

    protected void showBreadCrumbs(boolean requestFocus) {
	((CardLayout)getLayout()).show(this, CARD_BREADCRUMBS);

	if (requestFocus) {
	    FocusTraversalPolicy policy = breadCrumbs.
		getFocusCycleRootAncestor().getFocusTraversalPolicy();

	    if (policy != null) {
		Component last = policy.getLastComponent(breadCrumbs);
		if (last != null) {
		    last.requestFocusInWindow();
		}
	    }
	}
    }

    protected void showTextField(boolean requestFocus) {
	((CardLayout)getLayout()).show(this, CARD_ADDRFIELD);
	textField.setText(address);

	if (requestFocus) {
	    textField.selectAll();
	    textField.requestFocusInWindow();
	}
    }

    //
    // Private methods
    //

    private void createTextField() {
	textField = new JTextField(GUIUtil.getTextFieldWidth());
	textField.setVisible(false);

	// Remove shit-TAB as a backward focus traversal key
	KeyStroke shiftTab = KeyStroke.getKeyStroke(
	    KeyEvent.VK_TAB, InputEvent.SHIFT_DOWN_MASK);

	Set<AWTKeyStroke> backKeys = new HashSet<AWTKeyStroke>(
	    textField.getFocusTraversalKeys(
	    KeyboardFocusManager.BACKWARD_TRAVERSAL_KEYS));

	backKeys.remove(shiftTab);

	textField.setFocusTraversalKeys(
	    KeyboardFocusManager.BACKWARD_TRAVERSAL_KEYS, backKeys);

	// Make shift-TAB a) switch to breadcrumbs view if the text has not been
	// changed by the user, or b) follow normal backwards focus traversal
	// otherwise
	Action shiftTabAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    if (isTextFieldChanged()) {
			showBreadCrumbs(true);
		    } else {
			textField.transferFocusBackward();
		    }
		}
	    };

	GUIUtil.installKeyBinding(textField, JComponent.WHEN_FOCUSED,
	    "showbreadcrumbsorfocusback", shiftTabAction, shiftTab);

	// Make Esc switch to breadcrumbs view unconditionally
	Action escAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    showBreadCrumbs(true);
		}
	    };

	GUIUtil.installKeyBinding(textField, JComponent.WHEN_FOCUSED,
	    "showbreadcrumbs", escAction, KeyEvent.VK_ESCAPE);

	textField.addFocusListener(
	    new FocusListener() {
		@Override
		public void focusGained(FocusEvent e) {
		}

		@Override
		public void focusLost(FocusEvent e) {
		    // Switch to breadcrumbs view unless the text has been
		    // changed by the user
		    if (!e.isTemporary() && isTextFieldChanged()) {
			showBreadCrumbs(false);
		    }
		}
	    });

	textField.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    String address = getTextField().getText();
		    final SimpleNavigable[] pArray = Navigator.toArray(address);
		    final Navigator navigator = getNavigator();

		    // Launch navigation on non-event thread
		    navigator.asyncExec(
			new Runnable() {
			    @Override
			    public void run() {
				try {
				    navigator.goTo(false, null, pArray);
				} catch (Exception e) {
				    // Jump back onto event thread for UI work
				    EventQueue.invokeLater(
					new Runnable() {
					    @Override
					    public void run() {
						showTextField(true);
					    }
					});
				}
			    }
			});
		}
	    });
    }

    private void createBreadCrumbs() {
	// Make bread crumb components use text field font
	final Font font = UIManager.getFont("TextField.font");

	breadCrumbs = new ControlBreadCrumbs() {
	    @Override
	    protected Component createBreadCrumb(int index) {
		Component c = super.createBreadCrumb(index);
		c.setFont(font);
		return c;
	    }

	    @Override
	    protected Component createSeparator(int index) {
		Component c = super.createSeparator(index);
		c.setFont(font);
		return c;
	    }
	};

	breadCrumbs.addMouseListener(showAddressListener);
    }
}
