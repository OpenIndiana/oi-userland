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
import javax.swing.*;
import javax.swing.plaf.basic.BasicComboPopup;
import com.oracle.solaris.vp.util.swing.event.ItemListeners;

@SuppressWarnings({"serial"})
public class PopupList implements ItemSelectable {
    //
    // Static data
    //

    // Taken from the JList API
    private static final int MAX_VISIBLE_ROW_COUNT = 8;

    //
    // Instance data
    //

    private JComponent component;
    private BasicComboPopup popup;
    private JComboBox combo;
    private ItemListeners listeners = new ItemListeners();

    //
    // Constructors
    //

    public PopupList(JComponent component) {
	this.component = component;

	configureComboBox();
	configurePopup();
	configureList();
    }

    public PopupList(JButton button) {
	this((JComponent)button);

	button.addActionListener(
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    show();
		}
	    });
    }

    public PopupList(JComponent component, ComboBoxModel model) {
	this(component);
	setModel(model);
    }

    public PopupList(JButton button, ComboBoxModel model) {
	this(button);
	setModel(model);
    }

    //
    // ItemSelectable methods
    //

    @Override
    public void addItemListener(ItemListener l) {
	listeners.add(l);
    }

    @Override
    public Object[] getSelectedObjects() {
	return popup.getList().getSelectedValues();
    }

    @Override
    public void removeItemListener(ItemListener l) {
	listeners.remove(l);
    }

    //
    // PopupList methods
    //

    public ComboBoxModel getModel() {
	return combo.getModel();
    }

    public JComponent getComponent() {
	return component;
    }

    public BasicComboPopup getPopup() {
	return popup;
    }

    public void hide() {
	popup.setVisible(false);

	// Window change -- prefer requestFocus to requestFocusInWindow
	component.requestFocus();
    }

    protected void itemSelected() {
	hide();

	Object item = popup.getList().getSelectedValue();
	ItemEvent e = new ItemEvent(
	    this, ItemEvent.ITEM_STATE_CHANGED, item, ItemEvent.SELECTED);

	listeners.itemStateChanged(e);
    }

    public void setModel(ComboBoxModel model) {
	combo.setModel(model);
    }

    public void show() {
	JList list = popup.getList();
	int size = list.getModel().getSize();
	list.setVisibleRowCount(size < MAX_VISIBLE_ROW_COUNT ?
	    size : MAX_VISIBLE_ROW_COUNT);

	combo.setSelectedIndex(-1);
	popup.show(component, 0, component.getHeight());

	Window window = SwingUtilities.windowForComponent(popup);
	if (window != null) {
	    window.setFocusableWindowState(true);
	}

	// Window change -- prefer requestFocus to requestFocusInWindow
	list.requestFocus();
    }

    public void showOnDownArrowKey() {
	Action showAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    show();
		}
	    };

	GUIUtil.installKeyBinding(component, JComponent.WHEN_FOCUSED,
	    "showPopup", showAction, KeyEvent.VK_DOWN, KeyEvent.VK_KP_DOWN);
    }

    public void showOnMousePress() {
	component.addMouseListener(
	    new MouseAdapter() {
		@Override
		public void mousePressed(MouseEvent e) {
		    if (e.getModifiersEx() == InputEvent.BUTTON1_DOWN_MASK) {
			show();
		    }
		}
	    });
    }

    //
    // Private methods
    //

    private void configureComboBox() {
	combo = new JComboBox();
	combo.addItemListener(
	    new ItemListener() {
		@Override
		public void itemStateChanged(ItemEvent e) {
		    if (e.getStateChange() == ItemEvent.SELECTED) {
			itemSelected();
		    }
		}
	    });
    }

    private void configureList() {
	JList list = popup.getList();
	list.setBackground(Color.white);
	list.setOpaque(true);
	list.setFocusable(true);
    }

    private void configurePopup() {
	popup = new BasicComboPopup(combo);
	popup.setFocusable(true);

	Action commitAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    itemSelected();
		}
	    };

	GUIUtil.installKeyBinding(popup,
	    JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT, "commitPopup",
	    commitAction, KeyEvent.VK_ENTER);

	Action cancelAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    hide();
		}
	    };

	GUIUtil.installKeyBinding(popup,
	    JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT, "cancelPopup",
	    cancelAction, KeyEvent.VK_ESCAPE);
    }

    //
    // Static methods
    //

    public static void main(String s[]) {
	String[] data = {
	    "Bee", "Skunk"
	};
	ComboBoxModel model = new DefaultComboBoxModel(data);

	JButton b = new JButton("Hello");

	PopupList popup = new PopupList(b, model);
	popup.showOnDownArrowKey();

	popup.addItemListener(
	    new ItemListener() {
		@Override
		public void itemStateChanged(ItemEvent e) {
		    System.out.printf("%s\n", e.getItem());
		}
	    });

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(b, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
