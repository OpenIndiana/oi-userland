# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License"); you may
#    not use this file except in compliance with the License. You may obtain
#    a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
#    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
#    License for the specific language governing permissions and limitations
#    under the License.


""" openstack_upgrade - common functions used by the various OpenStack
components to facilitate upgrading of configuration files and MySQL
databases/tables (if in use)
"""

from ConfigParser import NoOptionError
from datetime import datetime
import errno
import glob
import os
import shutil
import time

import iniparse


def create_backups(directory):
    """ create backups of each configuration file which also has a .new file
    from the upgrade.
    """

    today = datetime.now().strftime("%Y%m%d%H%M%S")
    cwd = os.getcwd()
    os.chdir(directory)
    for new_file in glob.glob('*.new'):
        # copy the old conf file to a backup
        old_file = new_file.replace('.new', '')
        try:
            shutil.copy2(old_file, old_file + '.' + today)
        except (IOError, OSError):
            print 'unable to create a backup of %s' % old_file

    os.chdir(cwd)


def update_mapping(section, key, mapping):
    """ look for deprecated variables and, if found, convert it to the new
    section/key.
    """

    if (section, key) in mapping:
        print "Deprecated value found: [%s] %s" % (section, key)
        section, key = mapping[(section, key)]
        if section is None and key is None:
            print "Removing from configuration"
        else:
            print "Updating to: [%s] %s" % (section, key)
    return section, key


def alter_mysql_tables(engine):
    """ Convert MySQL tables to use utf8
    """

    import MySQLdb

    for _none in range(60):
        try:
            db = MySQLdb.connect(host=engine.url.host,
                                 user=engine.url.username,
                                 passwd=engine.url.password,
                                 db=engine.url.database)
            break
        except MySQLdb.OperationalError as err:
            # mysql is not ready. sleep for 2 more seconds
            time.sleep(2)
    else:
        print "Unable to connect to MySQL:  %s" % err
        print ("Please verify MySQL is properly configured and online "
               "before using svcadm(1M) to clear this service.")
        raise RuntimeError

    cursor = db.cursor()
    cursor.execute("SHOW table status")
    cursor.execute("ALTER DATABASE %s CHARACTER SET = 'utf8'" %
                   engine.url.database)
    cursor.execute("ALTER DATABASE %s COLLATE = 'utf8_general_ci'" %
                   engine.url.database)
    cursor.execute("SHOW tables")
    res = cursor.fetchall()
    if res:
        cursor.execute("SET foreign_key_checks = 0")
        for item in res:
            cursor.execute("ALTER TABLE %s.%s CONVERT TO "
                           "CHARACTER SET 'utf8', COLLATE 'utf8_general_ci'"
                           % (engine.url.database, item[0]))
        cursor.execute("SET foreign_key_checks = 1")
        db.commit()
        db.close()


def modify_conf(old_file, mapping=None, exception_list=None):
    """ Copy over all uncommented options from the old configuration file.  In
    addition, look for deprecated section/keys and convert them to the new
    section/key.
    """

    new_file = old_file + '.new'

    # open the previous version
    old = iniparse.ConfigParser()
    old.readfp(open(old_file))

    # open the new version
    new = iniparse.ConfigParser()
    try:
        new.readfp(open(new_file))
    except IOError as err:
        if err.errno == errno.ENOENT:
            # The upgrade did not deliver a .new file so, return
            print "%s not found - continuing with %s" % (new_file, old_file)
            return
        else:
            raise
    print "\nupdating %s" % old_file

    # walk every single section for uncommented options
    default_items = set(old.items('DEFAULT'))
    for old_section in old.sections() + ['DEFAULT']:

        # DEFAULT items show up in every section so remove them
        if old_section != 'DEFAULT':
            section_items = set(old.items(old_section)) - default_items
        else:
            section_items = default_items

        for old_key, value in section_items:
            # Look for deprecated section/keys
            if mapping is not None:
                new_section, new_key = update_mapping(old_section, old_key,
                                                      mapping)
                if new_section is None and new_key is None:
                    # option is deprecated so continue
                    continue
            else:
                # no deprecated values for this file so just copy the values
                # over
                new_section, new_key = old_section, old_key

            # Look for exceptions
            if exception_list is not None:
                if (new_section, new_key) in exception_list:
                    if (new_section != 'DEFAULT' and
                        not new.has_section(new_section)):
                        new.add_section(new_section)
                    print "Preserving [%s] %s = %s" % \
                        (new_section, new_key, value)
                    new.set(new_section, new_key, value)
                    continue

            if new_section != 'DEFAULT' and not new.has_section(new_section):
                new.add_section(new_section)

            # print to the log when a value for old_section.old_key is changing
            # to a new value
            try:
                new_value = new.get(new_section, new_key)
                if new_value != value and '%SERVICE' not in new_value:
                    print "Changing [%s] %s:\n- %s\n+ %s" % \
                        (old_section, old_key, value, new_value)
                    print
            except NoOptionError:
                # the new configuration file does not have this option set so
                # just continue
                pass

            # Only copy the old value to the new conf file if the entry doesn't
            # exist in the new file or if it contains '%SERVICE'
            if not new.has_option(new_section, new_key) or \
               '%SERVICE' in new.get(new_section, new_key):
                new.set(new_section, new_key, value)

    # copy the new conf file in place
    with open(old_file, 'wb+') as fh:
        new.write(fh)


def move_conf(original_file, new_file, mapping):
    """ move each entry in mapping from the original file to the new file.
    """
    # open the original file
    original = iniparse.ConfigParser()
    original.readfp(open(original_file))

    # open the new file
    new = iniparse.ConfigParser()
    new.readfp(open(new_file))

    # The mappings dictionary look similar to the deprecation mappings:
    # (original_section, original_key): (new_section, new_key)
    for (original_section, original_key) in mapping:
        try:
            original_value = original.get(original_section, original_key)
        except NoOptionError:
            # the original file does not contain this mapping so continue
            continue

        new_section, new_key = mapping.get((original_section, original_key))

        if new_section != 'DEFAULT' and not new.has_section(new_section):
            new.add_section(new_section)

        print 'Moving [%s] %s from %s to [%s] %s in %s' % \
            (original_section, original_key, original_file,
             new_section, new_key, new_file)

        # set the option in the new file
        new.set(new_section, new_key, original_value)

        # remove the option from the old file
        original.remove_option(original_section, original_key)

    with open(original_file, 'wb+') as fh:
        original.write(fh)

    with open(new_file, 'wb+') as fh:
        new.write(fh)
