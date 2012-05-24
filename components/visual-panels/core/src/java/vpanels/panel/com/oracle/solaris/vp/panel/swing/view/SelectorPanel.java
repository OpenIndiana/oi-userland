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
import java.awt.event.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class SelectorPanel<C extends Component> extends SettingsPanel {
    //
    // Static data
    //

    public static final int SELECTION_VIEWPORT_WIDTH = 175;

    //
    // Instance data
    //

    private C comp;
    private JScrollPane scroll;
    private JPopupMenu popup;
    private JLabel titleLabel;
    private JPanel buttonPanel;
    private JPanel contentCardPane;
    private boolean showButtonIcons = true;

    //
    // Constructors
    //

    public SelectorPanel() {
	popup = new JPopupMenu();

	scroll = new ExtScrollPane();
	scroll.getViewport().setOpaque(true);

	titleLabel = new AutoHideLabel();
	setSelectionTitle(null);

	RowLayout rLayout = new RowLayout(HorizontalAnchor.FILL);
	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, GUIUtil.getButtonGap());
	rLayout.setDefaultConstraint(r);

	buttonPanel = new AutoHidePanel();
	buttonPanel.setOpaque(false);
	buttonPanel.setLayout(rLayout);

	JPanel selectionPanel = new JPanel();
	selectionPanel.setOpaque(false);

	int gap = GUIUtil.getGap();
	int lGap = GUIUtil.getVerticalLabelGap();

	ColumnLayout cLayout = new ColumnLayout(VerticalAnchor.FILL);
	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, lGap);

	selectionPanel.setLayout(cLayout);
	selectionPanel.add(titleLabel, c);
	selectionPanel.add(scroll, c.clone().setWeight(1));
	selectionPanel.add(buttonPanel, c.setGap(gap).setHorizontalAnchor(
	    HorizontalAnchor.RIGHT));

	contentCardPane = new JPanel(new CardLayout());
	contentCardPane.setOpaque(false);

	JPanel panel = getContentPane();
	panel.setLayout(new BorderLayout(gap, gap));

	panel.add(selectionPanel, BorderLayout.WEST);
	panel.add(contentCardPane, BorderLayout.CENTER);
    }

    //
    // SelectorPanel methods
    //

    public void addButtonActions(Action... actions) {
	for (Action action : actions) {
	    JButton button = new JButton(action);

	    if (!showButtonIcons) {
		button.setDisabledIcon(null);
		button.setDisabledSelectedIcon(null);
		button.setIcon(null);
		button.setPressedIcon(null);
		button.setRolloverIcon(null);
		button.setRolloverSelectedIcon(null);
		button.setSelectedIcon(null);
	    }

	    buttonPanel.add(button);
	}
    }

    public void addPopupMenuActions(Action... actions) {
	for (Action action : actions) {
	    popup.add(action);
	}
    }

    public JPanel getContentCardPane() {
	return contentCardPane;
    }

    public JPopupMenu getPopupMenu() {
	return popup;
    }

    public C getSelectionComponent() {
	return comp;
    }

    /**
     * Gets whether buttons created via {@link #addButtonActions} should show
     * icons.
     *
     * @see	    #setShowButtonIcons
     */
    public boolean getShowButtonIcons() {
	return showButtonIcons;
    }

    protected void setSelectionComponent(C comp) {
	this.comp = comp;
	scroll.setViewportView(comp);
	scroll.getViewport().setBackground(comp.getBackground());

	comp.addMouseListener(
	    new MouseAdapter() {
		@Override
		public void mouseReleased(final MouseEvent e) {
		    showPopup(e);
		}

		@Override
		public void mousePressed(final MouseEvent e) {
		    showPopup(e);
		}
	    });

	titleLabel.setLabelFor(comp);
    }

    public void setSelectionIcon(Icon icon) {
	titleLabel.setIcon(icon);
    }

    public void setSelectionTitle(String title) {
	titleLabel.setText(title);
    }

    /**
     * Sets whether buttons created via {@link #addButtonActions} should show
     * icons.  The default value is {@code true}.
     *
     * @see	    #getShowButtonIcons
     */
    public void setShowButtonIcons(boolean showButtonIcons) {
	this.showButtonIcons = showButtonIcons;
    }

    public void showPopup(int x, int y) {
	if (popup.getSubElements().length != 0) {
	    popup.show(comp, x, y);
	}
    }

    //
    // Private methods
    //

    private void showPopup(MouseEvent e) {
	if (e.isPopupTrigger()) {
	    showPopup(e.getX(), e.getY());
	}
    }
}
