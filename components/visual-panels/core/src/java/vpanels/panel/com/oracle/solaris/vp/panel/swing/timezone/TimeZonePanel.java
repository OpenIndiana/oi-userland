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

import java.awt.*;
import java.awt.geom.Point2D;
import java.beans.*;
import java.text.DateFormat;
import java.util.*;
import java.util.List;
import javax.swing.event.*;
import javax.swing.Icon;
import com.oracle.solaris.vp.panel.common.model.View;
import com.oracle.solaris.vp.panels.time.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;
import com.oracle.solaris.vp.util.swing.layout.ColumnLayoutConstraint;
import com.oracle.solaris.vp.util.swing.SettingsPanel;
import com.oracle.solaris.vp.util.swing.time.*;

public class TimeZonePanel extends SettingsPanel
    implements View<TimeZoneModel> {

    //
    // Static data
    //

    private static TimeZoneMapper MAPPER = new TimeZoneMapper();

    private static final Icon BACKGROUND_ICON =
	Finder.getIcon("images/world_map-960.png");

    /**
     * Gets the {@code TimeZone} that corresponds to the given {@link
     * TimeZoneInfo}.
     *
     * @return	a {@code TimeZone}, or {@code null} if no {@code
     *		TimeZone} corresponds to the given {@link TimeZoneInfo}
     */
    public static TimeZone toTimeZone(TimeZoneInfo info) {
	// Unfortunately TimeZone.getTimeZone(String id) gives no error when
	// id is not recognized, so use a different approach
	String[] ids = TimeZone.getAvailableIDs();
	for (String id : ids) {
	    if (id.equals(info.getName()) ||
		id.equals(info.getAltName())) {
		return TimeZone.getTimeZone(id);
	    }
	}

	// XXX We should never return null.  TimeZoneInfo should have a
	// int getRawOffset method to ensure we can always create a
	// TimeZone.
	return null;
    }

    //
    // Instance data
    //

    private LocationPanel<TZChoice> locationPanel_;
    private MutableProperty<TZChoice> locationProp_;

    private Map<String, TZChoice> nameToTimeZone =
	new HashMap<String, TZChoice>();
    private Map<String, Continent> continentDesc =
	new HashMap<String, Continent>();
    private Map<String, Country> countryDesc = new HashMap<String, Country>();
    private Map<Integer, Offset> offsetDesc = new HashMap<Integer, Offset>();
    private Map<Integer, Offset> rawoffsetDesc = new HashMap<Integer, Offset>();

    //
    // Inner classes
    //

    /*
     * Need an object to encapsulate a timezone offset.
     */
    private class Offset {
	int offset_;

	public Offset(int offset) {
	    offset_ = offset;
	}

	@Override
	public String toString() {
	    boolean neg = offset_ < 0;
	    int minutes = Math.abs(offset_) / (60 * 1000);
	    int hours = minutes / 60;
	    minutes = minutes % 60;
	    return (String.format("GMT%s%d:%02d",
		neg ? "-" : "+", hours, minutes));
	}
    }

    /*
     * We could use TimeZoneInfos directly, but instead we use this wrapper
     * type to cache the associations between each time zone and its various
     * attributes.
     */
    private class TZChoice {
	TimeZoneInfo info_;
	Country country_;
	Continent continent_;
	Offset offset_;
	Offset rawoffset_;
	String label_;
	Point2D point_;

	public TZChoice(TimeZoneInfo info) {
	    TimeZone tz = TimeZone.getTimeZone(info.getName());
	    info_ = info;
	    String contname = info.getName().split("/")[0];
	    continent_ = continentDesc.get(contname);
	    country_ = countryDesc.get(info.getCountryCode());
	    offset_ = makeOffset(tz.getOffset(System.currentTimeMillis()),
		offsetDesc);
	    rawoffset_ = makeOffset(tz.getRawOffset(), rawoffsetDesc);

	    String alt = info.getAltName();
	    String name = alt != null ? alt : info.getName();
	    String display = tz.getDisplayName();
	    label_ = Finder.getString("timezone.description", name, display);

	    Coordinates coords = info.getCoordinates();
	    double east = (double)coords.getDegreesE() +
		(coords.getDegreesE() > 0 ? 1 : -1) *
		((double)coords.getSecondsE() / 60 +
		(double)coords.getMinutesE()) / 60;
	    double north = (double)coords.getDegreesN() +
		(coords.getDegreesN() > 0 ? 1 : -1) *
		((double)coords.getSecondsN() / 60 +
		(double)coords.getMinutesN()) / 60;
	    east = 180 + east;
	    north = 90 - north;
	    point_ = new Point2D.Double(east / 360, north / 180);
	}

	private Offset makeOffset(int offset, Map<Integer, Offset>map) {
	    Offset result = map.get(offset);
	    if (result == null)
		map.put(offset, result = new Offset(offset));
	    return (result);
	}

	public TimeZoneInfo getInfo() {
	    return (info_);
	}
    }

    private static class TimeZoneMapper implements LocationMapper<TZChoice> {
	@Override
	public Point2D map(TZChoice choice) {
	    return choice.point_;
	}

	@Override
	public String getLabel(TZChoice choice) {
	    return choice.label_;
	}
    }

    private class TZOffsetCriteria extends LocationCriteria<TZChoice, Offset>
	implements Comparator<Offset> {

	public String getLabel() {
	    return Finder.getString("timezone.label.offset");
	}

	public String getUnselectedText() {
	    return Finder.getString("timezone.offset.select");
	}

	@Override
	public Comparator<Offset> getComparator() {
	    return this;
	}

	public Offset toCriterion(TZChoice choice) {
	    return choice.offset_;
	}

	public String toDescription(Offset criterion) {
	    return criterion.toString();
	}

	/*
	 * Comparator methods
	 */

	public int compare(Offset o1, Offset o2) {
	    return (o1.offset_ - o2.offset_);
	}
    }

    private class TZContinentCriteria
	extends LocationCriteria<TZChoice, Continent> {

	public String getLabel() {
	    return Finder.getString("timezone.label.continent");
	}

	public String getUnselectedText() {
	    return Finder.getString("timezone.continent.select");
	}

	public Continent toCriterion(TZChoice choice) {
	    return (choice.continent_);
	}

	public String toDescription(Continent criterion) {
	    return criterion.getDescription();
	}
    }

    private class TZCountryCriteria
	extends LocationCriteria<TZChoice, Country> {

	public String getLabel() {
	    return Finder.getString("timezone.label.country");
	}

	public String getUnselectedText() {
	    return Finder.getString("timezone.country.select");
	}

	public Country toCriterion(TZChoice choice) {
	    return (choice.country_);
	}

	public String toDescription(Country criterion) {
	    return criterion.getDescription();
	}
    }

    private class TZZoneCriteria extends LocationCriteria<TZChoice, TZChoice> {

	public String getLabel() {
	    return Finder.getString("timezone.label.timezone");
	}

	public String getUnselectedText() {
	    return Finder.getString("timezone.timezone.select");
	}

	public TZChoice toCriterion(TZChoice choice) {
	    return choice;
	}

	public String toDescription(TZChoice criterion) {
	    return (MAPPER.getLabel(criterion));
	}
    }

    //
    // Constructors
    //

    public TimeZonePanel(TimeMXBean bean, final SimpleTimeModel model) {

	getHelpField().setText(Finder.getString("timezone.desc"));

	// Remove the spacing between the help and content panes
	ColumnLayoutConstraint constraint =
	    getLayout().getConstraint(getContentPane());
	constraint.setGap(0);

	/*
	 * Read metadata from MBean.  Ideally would be read from the model.
	 */
	List<TimeZoneInfo> infoSet = bean.gettimeZones();
	List<Continent> continents = bean.getcontinents();
	List<Country> countries = bean.getcountries();

	for (Continent c : continents)
	    continentDesc.put(c.getName(), c);

	for (Country c : countries)
	    countryDesc.put(c.getCode(), c);

	List<TZChoice> choices = new LinkedList<TZChoice>();
	for (TimeZoneInfo zone : infoSet) {
	    TZChoice choice = new TZChoice(zone);
	    if (choice.continent_ == null || choice.country_ == null)
		continue;
	    choices.add(choice);
	    nameToTimeZone.put(zone.getName(), choice);
	    if (zone.getAltName() != null)
		nameToTimeZone.put(zone.getAltName(), choice);
	}

	List<LocationCriteria<TZChoice, ?>> criteria =
	    new LinkedList<LocationCriteria<TZChoice, ?>>();
	criteria.add(new TZContinentCriteria());
	criteria.add(new TZCountryCriteria());
	// criteria.add(new TZOffsetCriteria());  // *instead* of the other two

	locationPanel_ = new LocationPanel<TZChoice>(BACKGROUND_ICON,
	    new Dimension(400, 200), MAPPER);
	locationProp_ = locationPanel_.getLocationProperty();
	getChangeableAggregator().addChangeables(locationProp_);
	locationPanel_.setCriteria(criteria, new TZZoneCriteria(), choices,
	    model != null ? Finder.getString("timezone.label.time") : null);

	if (model != null) {
	    /*
	     * Add listener that updates SimpleTimeModel with selected
	     * time zone
	     */
	    locationProp_.addChangeListener(
		new ChangeListener() {
		    @Override
		    public void stateChanged(ChangeEvent e) {
			TZChoice choice = locationProp_.getValue();
			if (choice != null) {
			    TimeZone zone = toTimeZone(choice.getInfo());
			    model.setTimeZone(zone);
			}
		    }
		});

	    /*
	     * And add a listener to the model that updates the auxiliary
	     * field of the location panel with the current time.
	     */
	    final DateFormat format = DateFormat.getDateTimeInstance(
		DateFormat.SHORT, DateFormat.SHORT);
	    format.setCalendar(model.getModelCalendar());

	    PropertyChangeListener timeLabelListener =
		new PropertyChangeListener() {
		    @Override
		    public void propertyChange(PropertyChangeEvent e) {
			locationPanel_.getAuxField().setText(format.format(
			    model.getCalendar().getTime()));
		    }
		};
	    model.addPropertyChangeListener(TimeModel.PROPERTY_TIME,
		timeLabelListener);

	    // Initialize
	    timeLabelListener.propertyChange(null);
	}

	getContentPane().add(locationPanel_);
	setContent(locationPanel_, false, false);
    }

    //
    // View methods
    //

    public void modelToView(TimeZoneModel model) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	String name = model.getTimeZone();
	TZChoice timeZone = nameToTimeZone.get(name);
	locationProp_.update(timeZone, false);
    }

    public void viewToModel(TimeZoneModel model) {
	TZChoice tz = locationProp_.getValue();
	model.setTimeZone(tz != null ? tz.getInfo().getName() : null);
    }
}
