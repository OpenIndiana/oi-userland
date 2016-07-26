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
DDU exception class
"""
class DDUException(Exception):
    """DDU exception"""
    pass

class RepositoryNotFoundException(DDUException):
    """No repo found"""
    pass

class RepositoryCreatedException(DDUException):
    """can not create repo"""
    def __init__(self, repo_name):
        DDUException.__init__(self)
        self.repo_name = repo_name
    def __str__(self):
        str_message = "Can not create repository for: %s" % str(self.repo_name)
        return(str(str_message))

class RepositoryNotReadyException(DDUException):
    """can not run pkg command"""
    pass

class RepositoryNotAvailableException(DDUException):
    """can not get data from repo"""
    def __init__(self, repo_name):
        DDUException.__init__(self)
        self.repo_name = repo_name
    def __str__(self):
        str_message = "Can not get database from repo %s" % str(self.repo_name)
        return(str(str_message))

class DevScanNotStart(DDUException):
    """can not start probe script"""
    pass

class DevDetailNotAvailable(DDUException):
    """can not get device inf"""
    def __init__(self, dev_path):
        DDUException.__init__(self)
        self.dev_path = dev_path
    def __str__(self):
        str_message = "Can not get detail information from device:%s" % \
                      str(self.dev_path)
        return(str(str_message))

class RepositorylistNotValid(DDUException):
    """invalid repo list"""
    pass

class RepositoryConformException(DDUException):
    """repo invalid"""
    pass

class DDuDevDataNotValid(DDUException):
    """device inf invalid"""
    pass

class DevInfNotRetrievedDB(DDUException):
    """device inf not ready"""
    pass

class PackageNoFound(DDUException):
    """no package found"""
    def __init__(self, dev_des):
        DDUException.__init__(self)
        self.dev_des = dev_des
    def __str__(self):
        str_message = "Package for device %s not found" % self.dev_des
        return(str(str_message))

class PackageTypeInvalid(DDUException):
    """package type invalid"""
    pass

class PackageInstallNotAllowed(DDUException):
    """can not install package"""
    pass

class InstallAreaUnaccessible(DDUException):
    """install area unaccessible"""
    pass

class InstallPkgFail(DDUException):
    """install PKG package fail"""
    pass

class InstallUnkFail(DDUException):
    """install UNK package fail"""
    pass
