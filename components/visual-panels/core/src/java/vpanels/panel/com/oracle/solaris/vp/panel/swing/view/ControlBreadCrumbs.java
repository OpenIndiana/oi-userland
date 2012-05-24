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
import java.util.List;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.util.misc.finder.MessageFinder;
import com.oracle.solaris.vp.util.misc.NameValue;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class ControlBreadCrumbs extends BreadCrumbs<List<Control>> {
    //
    // Static data
    //

    public static final int BUTTON_MARGIN = 4;

    //
    // Instance data
    //

    private JLabel lastBreadCrumb = createLabel(true);
    private PopupList iPopup;

    //
    // BreadCrumbs methods
    //

    @Override
    protected Component createBreadCrumb(int index) {
	List<Control> list = getElementAt(index);
	final Control control = list.get(0);
	String text = toString(list);

	if (index == getModel().getSize() - 1) {
	    lastBreadCrumb.setText(text);
	    return lastBreadCrumb;
	}

	JButton b = createButton();
	b.setText(text);

	b.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    // Launch navigation on non-event thread
		    control.getNavigator().goToAsync(false, control);
		}
	    });

	return b;
    }

    @Override
    protected Component createHiddenBreadCrumbIndicator() {
	String pkg = BreadCrumbs.class.getPackage().getName();
	String ellipsis = new MessageFinder().getStringFromPackage(
	    pkg, "breadcrumb.hidden.text");

	JButton b = createButton();
	b.setText(ellipsis);
	b.setIcon(ArrowIcon.LEFT);
	b.setHorizontalTextPosition(SwingConstants.LEFT);

	iPopup = new PopupList(b);
	iPopup.showOnDownArrowKey();
	iPopup.showOnMousePress();

	// Navigate to Navigable selected in list
	iPopup.addItemListener(
	    new ItemListener() {
		@Override
		public void itemStateChanged(ItemEvent e) {
		    if (e.getStateChange() == ItemEvent.SELECTED) {
			@SuppressWarnings({"unchecked"})
			NameValue<Control> nv = (NameValue<Control>)e.getItem();

			final Control control = nv.getValue();

			// Launch navigation on non-event thread
			control.getNavigator().goToAsync(false, control);
		    }
		}
	    });

	return b;
    }

    @Override
    protected Component createSeparator(int index) {
	class Tuple {
	    public Control control;
	    public Navigable navigable;

	    public Tuple(Control control, Navigable navigable) {
		this.control = control;
		this.navigable = navigable;
	    }
	}

	Control nextControl = getElementAt(index).get(0);
	NameValue<Tuple> nextNav = null;

	NameValueComboBoxModel<Tuple> model =
	    new NameValueComboBoxModel<Tuple>();

	List<Control> previous = getElementAt(index - 1);
	for (Control control : previous) {
	    for (Navigable navigable : control.getBrowsable()) {
		String name = navigable.getName();
		if (name != null) {
		    NameValue<Tuple> nv = new NameValue<Tuple>(
			name, new Tuple(control, navigable));

		    model.addElement(nv);

		    if (nextNav == null &&
			Navigable.Util.equals(navigable, nextControl)) {
			nextNav = nv;
		    }
		}
	    }
	}

	if (model.getSize() <= 1) {
	    JLabel l = createLabel(false);
	    l.setIcon(ArrowIcon.RIGHT);
	    return l;
	}

	JButton b = createButton();
	b.setIcon(ArrowIcon.RIGHT);

	final NameValue<Tuple> fNextNav = nextNav;
	PopupList popup = new PopupList(b, model);
	popup.showOnDownArrowKey();
	popup.showOnMousePress();

	final JList list = popup.getPopup().getList();

	// Select the current Control in list when it is shown
	popup.getPopup().addPopupMenuListener(
	    new PopupMenuListener() {
		@Override
		public void popupMenuCanceled(PopupMenuEvent e) {
		}

		@Override
		public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
		}

		@Override
		public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
		    list.setSelectedValue(fNextNav, true);
		}
	    });

	// Embolden the current Control in list
	final ListCellRenderer renderer = list.getCellRenderer();
	list.setCellRenderer(
	    new ListCellRenderer() {
		 @Override
		 public Component getListCellRendererComponent(
		    JList list, Object value, int index, boolean isSelected,
		    boolean cellHasFocus) {

		    Component c = renderer.getListCellRendererComponent(
			list, value, index, isSelected, cellHasFocus);

		    if (value == fNextNav) {
			Font f = c.getFont().deriveFont(Font.BOLD);
			c.setFont(f);
		    }

		    return c;
		 }
	    });

	// Navigate to Navigable selected in list
	popup.addItemListener(
	    new ItemListener() {
		@Override
		public void itemStateChanged(ItemEvent e) {
		    if (e.getStateChange() == ItemEvent.SELECTED) {
			@SuppressWarnings({"unchecked"})
			NameValue<Tuple> nv = (NameValue<Tuple>)e.getItem();
			Tuple tuple = nv.getValue();

			// Launch navigation on non-event thread
			tuple.control.getNavigator().goToAsync(false,
			    tuple.control, tuple.navigable);
		    }
		}
	    });

	return b;
    }

    @Override
    protected void setFirstVisibleIndex(int index) {
	if (index != getFirstVisibleIndex()) {
	    super.setFirstVisibleIndex(index);

	    if (index != 0) {
		NameValueComboBoxModel<Control> model =
		    new NameValueComboBoxModel<Control>();

		for (int i = index - 1; i >= 0; i--) {
		    Control control = getElementAt(i).get(0);

		    NameValue<Control> nv =
			new NameValue<Control>(control.getName(), control);

		    model.addElement(nv);
		}

		iPopup.setModel(model);
	    }
	}
    }

    @Override
    public String toString(List<Control> list) {
	return list.get(0).getName();
    }

    //
    // ControlBreadCrumbs methods
    //

    /**
     * Collate the given address into {@code List}s (stacking {@link Control}s
     * with {@code null} names into the previous {@link Control}'s {@code
     * List}), as expected by the model.
     *
     * @param	    path
     *		    an active navigation path
     */
    public void setAddress(Collection<Control> path) {
	List<List<Control>> collated;
	if (path == null) {
	    collated = Collections.emptyList();
	} else {
	    collated = new LinkedList<List<Control>>();
	    List<Control> list = null;
	    for (Control control : path) {
		if (control.getName() != null) {
		    list = new LinkedList<Control>();
		    collated.add(list);
		}
		if (list != null) {
		    list.add(control);
		}
	    }
	}

	clear();

	for (List<Control> list : collated) {
	    push(list);
	}
    }

    //
    // Private methods
    //

    private JButton createButton() {
	JButton b = new JButton();
	GUIUtil.setHorizontalMargin(b, BUTTON_MARGIN);

	new RolloverHandler(b);
	return b;
    }

    private JLabel createLabel(boolean last) {
	JLabel label = new JLabel();

	// Yes, this is hackish, but
	// UIManager.getBorder("Button.border").getBorderInsets(...) is not
	// reliable
	Insets insets = createButton().getInsets();

	Border border = BorderFactory.createEmptyBorder(
	    0, insets.left, 0, last ? 0 : insets.right);

	label.setBorder(border);

	// Prevent clicks from passing through to text field
	label.addMouseListener(new MouseAdapter() {});

	return label;
    }
}
