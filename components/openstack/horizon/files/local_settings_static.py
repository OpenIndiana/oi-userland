# -*- coding: utf-8 -*-

import os

from django.utils.translation import ugettext_lazy as _

from horizon.utils import secret_key

from openstack_dashboard import exceptions
from openstack_dashboard.settings import HORIZON_CONFIG

DEBUG = False
TEMPLATE_DEBUG = DEBUG

WEBROOT = '/horizon/'
STATIC_ROOT = 'static'
COMPRESS_OFFLINE = True

# Create an scss logger to prevent manage.py from
# spewing scss errors
LOGGING = {
    'version': 1,
    'disable_existing_loggers': True,
    'handlers': {
        'null': {
            'level': 'DEBUG',
            'class': 'logging.NullHandler',
        },
    },
    'loggers': {
        'scss': {
            'handlers': ['null'],
            'propagate': False,
        },
     }
}

AVAILABLE_THEMES = [
    ('default', 'Default', 'themes/default'),
]
