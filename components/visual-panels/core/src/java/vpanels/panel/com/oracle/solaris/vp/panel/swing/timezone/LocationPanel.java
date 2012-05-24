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

package com.oracle.solaris.vp.panel.swing.timezone;

import java.awt.Dimension;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.NameValue;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

public class LocationPanel<C> extends JPanel {

    //
    // Instance data
    //

    private LocationPicker<C> picker_;
    private ExtScrollPane scroll_;
    private MutableProperty<C> locationProperty_ =
	new BasicMutableProperty<C>();
    private JLabel auxField_;

    private List<CriteriaState<?>> critlist_;
    private CriteriaState<C> lastCriteria_;
    private List<C> choices_;

    //
    // Inner classes
    //

    private class CriteriaState<U> {

	private LocationCriteria<C, U> criteria_;
	private JLabel label_;
	private JComboBox box_;
	private FilteredComboBoxModel<NameValue<U>> model_;
	private NameValue<U> unselected_;
	private Map<U, NameValue<U>> values_;

	CriteriaState(LocationCriteria<C, U> crit) {
	    criteria_ = crit;
	    label_ = new JLabel(crit.getLabel());
	    unselected_ = new NameValue<U>(crit.getUnselectedText(), null);
	    box_ = new JComboBox();

	    Comparator<? super U> comp = criteria_.getComparator();
	    if (comp == null) {
		comp = new Comparator<U>() {
		    public int compare(U o1, U o2) {
			return (criteria_.toDescription(o1).compareTo(
			    criteria_.toDescription(o2)));
		    }
		};
	    }
	    values_ = new TreeMap<U, NameValue<U>>(comp);

	    constrainModel(null, null);
	}

	void constrainModel(LocationCriteria<C, ?> crit, Object selection) {
	    /*
	     * Find the criteria that correspond to the choices matched by
	     * the previous criterion.
	     */
	    values_.clear();
	    for (C c : choices_) {
		if (crit == null || crit.toCriterion(c).equals(selection)) {
		    U v = criteria_.toCriterion(c);
		    if (!values_.containsKey(v))
			values_.put(v,
			    new NameValue<U>(criteria_.toDescription(v), v));
		}
	    }

	    /*
	     * Create model, assign, and initialize.
	     */
	    model_ = new FilteredComboBoxModel<NameValue<U>>(values_.values());
	    box_.setModel(model_);
	    if (values_.size() != 1)
		model_.setSelectedItem(unselected_);
	    else
		model_.setSelectedItem(values_.values().iterator().next());
	}
    }

    //
    // Constructor
    //

    public LocationPanel(Icon background, Dimension size,
	LocationMapper<C> mapper) {
	// Create picker widget
	picker_ = new LocationPicker<C>(background, mapper);
	picker_.setPreferredSize(size);
	scroll_ = new ExtScrollPane(picker_);

	new LocationPickerPropertySynchronizer<C, LocationPicker<C>>(
	    locationProperty_, picker_);
    }

    //
    // LocationPanel methods
    //

    /*
     * Auxiliary function to circumvent the inability to instantiate
     * wildcarded classes.
     */
    private <U> CriteriaState<U> makeState(LocationCriteria<C, U> crit) {
	return (new CriteriaState<U>(crit));
    }

    /**
     * Sets the criteria to select from.  The final criteria must be the
     * same type as the choices; we enforce this by making it a separate
     * argument.
     */
    public void setCriteria(List<? extends LocationCriteria<C, ?>> criteria,
        LocationCriteria<C, C> lastcrit, List<C> choices, String auxText) {

	removeAll();

	picker_.setObjects(new HashSet<C>(choices));

	int count = criteria.size() + 1;
	critlist_ = new ArrayList<CriteriaState<?>>(count);
	choices_ = choices;

	for (LocationCriteria<C, ?> crit : criteria)
	    critlist_.add(makeState(crit));
	critlist_.add(lastCriteria_ = makeState(lastcrit));

	/*
	 * Configure each combobox to constrain the choices available in
	 * the next combo box.  In the case of the last combo box, set the
	 * picker's selection.
	 */
	for (int i = 0; i < count; i++) {
	    final CriteriaState<?> s = critlist_.get(i);
	    final boolean last = s == lastCriteria_;
	    final CriteriaState<?> nexts = last ? null : critlist_.get(i + 1);

	    s.box_.addItemListener(
		new ItemListener() {
		    @Override
		    public void itemStateChanged(ItemEvent e) {
			if (s == lastCriteria_) {
			    C item = lastCriteria_.model_.getSelectedItem().
				getValue();
			    picker_.setSelection(item);
			} else {
			    Object item = s.model_.getSelectedItem().getValue();
			    nexts.constrainModel(s.criteria_, item);
			}
		    }
		});
	}

	/*
	 * When an item is selected from the picker, update the combo boxes
	 * with the criteria that match that selection.
	 */
	picker_.addSelectionListener(
	    new LocationSelectionListener<C>() {
		@Override
		public void locationChanged(LocationSelectionEvent<C> event) {
		    C location = event.getLocation();

		    if (location != null) {
			NameValue<C> selection =
			    lastCriteria_.model_.getSelectedItem();
			if (selection == null ||
			    !location.equals(selection.getValue()))
			    for (CriteriaState<?> s : critlist_)
				s.box_.setSelectedItem(s.values_.get(
				    s.criteria_.toCriterion(location)));
		    } else {
			CriteriaState<?> first = critlist_.get(0);
			first.box_.setSelectedItem(first.unselected_);
		    }
		}
	    });

	CriteriaState<?> first = critlist_.get(0);
	first.box_.setSelectedItem(first.unselected_);

	/*
	 * Assemble UI pieces
	 */
	auxField_ = new JLabel();
	setOpaque(false);
	Form form = new Form(this, VerticalAnchor.CENTER);

	int gap = GUIUtil.getGap();

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap, 1f);

	SimpleHasAnchors labelAnchor = new SimpleHasAnchors(
	    HorizontalAnchor.RIGHT, VerticalAnchor.CENTER);

	SimpleHasAnchors fieldAnchor = new SimpleHasAnchors(
	    HorizontalAnchor.FILL, VerticalAnchor.CENTER);

	form.addRow(HorizontalAnchor.CENTER, c);
	form.add(scroll_);

	form.addTable(2, gap, gap / 2, HorizontalAnchor.CENTER, c.setWeight(0));

	if (auxText != null) {
	    form.add(new JLabel(auxText), labelAnchor);
	    form.add(auxField_, fieldAnchor);
	}

	for (CriteriaState cs : critlist_) {
	    form.add(cs.label_, labelAnchor);
	    form.add(cs.box_, fieldAnchor);
	}
    }

    public MutableProperty<C> getLocationProperty() {
	return locationProperty_;
    }

    public JLabel getAuxField() {
	return (auxField_);
    }
}
