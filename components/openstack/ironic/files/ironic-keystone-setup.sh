#!/usr/bin/env bash

# Copyright 2013 OpenStack Foundation
#
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
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

# Sample initial data for Keystone ironic setup using python-keystoneclient
#
# Creates ironic user and user-role, then creates ironic keystone service.
# Finally creates keystone-endpoint of required.
#
# If any keystone components already exist, will remove them before attempting
# to create.
#
# Disable creation of endpoints by setting DISABLE_ENDPOINTS environment
# variable. Use this with the Catalog Templated backend.
#
# Tenant               User      Roles
# -------------------------------------------------------
# service              ironic    admin

# By default, passwords used are those in the OpenStack Install and Deploy
# Manual. One can override these (publicly known, and hence, insecure) passwords
# by setting the appropriate environment variables. A common default password
# can be used by the "SERVICE_PASSWORD" environment variable.

PATH=/usr/bin

IRONIC_PASSWORD=${IRONIC_PASSWORD:-${SERVICE_PASSWORD:-ironic}}

CONTROLLER_PUBLIC_ADDRESS=${CONTROLLER_PUBLIC_ADDRESS:-localhost}
CONTROLLER_ADMIN_ADDRESS=${CONTROLLER_ADMIN_ADDRESS:-localhost}
CONTROLLER_INTERNAL_ADDRESS=${CONTROLLER_INTERNAL_ADDRESS:-localhost}

IRONIC_PUBLIC_ADDRESS=${IRONIC_PUBLIC_ADDRESS:-$CONTROLLER_PUBLIC_ADDRESS}
IRONIC_ADMIN_ADDRESS=${IRONIC_ADMIN_ADDRESS:-$CONTROLLER_ADMIN_ADDRESS}
IRONIC_INTERNAL_ADDRESS=${IRONIC_INTERNAL_ADDRESS:-$CONTROLLER_INTERNAL_ADDRESS}

export OS_AUTH_URL="http://localhost:5000/v2.0"
export OS_USERNAME="admin"
export OS_PASSWORD="secrete"
export OS_TENANT_NAME="demo"

function get_id () {
    echo `"$@" | grep ' id ' | awk '{print $4}'`
}

function get_role_id () {
    echo `"$@" | grep ' admin ' | awk '{print $2}'`
}

function get_endpoint_id () {
    echo `"$@" | grep $KEYSTONE_SERVICE | awk '{print $2}'`
}

#
# Service tenant
#
SERVICE_TENANT=$(get_id keystone tenant-get service)

#
# Admin Role
#
ADMIN_ROLE=$(get_role_id keystone user-role-list)


#
# Ironic User
#
IRONIC_USER=$(get_id keystone user-get ironic 2> /dev/null)
if ! [[ -z "$IRONIC_USER" ]]; then
  keystone user-role-remove --user=ironic \
                            --role=admin \
                            --tenant=service
  keystone user-delete ironic
fi
IRONIC_USER=$(get_id keystone user-create --name=ironic \
                                          --pass="${IRONIC_PASSWORD}")
keystone user-role-add --user-id $IRONIC_USER \
                       --role-id $ADMIN_ROLE \
                       --tenant-id $SERVICE_TENANT

#
# Ironic service
#
KEYSTONE_SERVICE=$(get_id keystone service-get ironic 2> /dev/null)
if ! [[ -z "$KEYSTONE_SERVICE" ]]; then
  KEYSTONE_ENDPOINT=$(get_endpoint_id keystone endpoint-list)
  keystone endpoint-delete $KEYSTONE_ENDPOINT
  keystone service-delete ironic
fi

KEYSTONE_SERVICE=$(get_id \
keystone service-create --name=ironic \
                        --type=baremetal \
                        --description="Ironic Bare Metal Provisioning Service")
if [[ -z "$DISABLE_ENDPOINTS" ]]; then
    keystone endpoint-create --region RegionOne --service-id $KEYSTONE_SERVICE \
        --publicurl "http://$IRONIC_PUBLIC_ADDRESS:6385" \
        --adminurl "http://$IRONIC_ADMIN_ADDRESS:6385" \
        --internalurl "http://$IRONIC_INTERNAL_ADDRESS:6385"
fi
