#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
#
# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#
"""
repo object data
"""

class ddu_repo_object(object):
    '''
    repo object data
    '''
    def __init__(self, repo_name, repo_url, repo_database = ''):
        '''
        Constructor
        '''

        self.repo_name = repo_name
        self.repo_url = repo_url
        self.repo_database = repo_database

    def get_repo_name(self):
        return self.repo_name

    def get_repo_url(self):
        return self.repo_url

    def get_repo_database(self):
        return self.repo_database
