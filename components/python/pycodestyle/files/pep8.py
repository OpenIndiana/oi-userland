# This file ensures that import pep8 will still work and correctly import new
# pycodestyle instead. It can be safely removed after all Solaris pep8 related
# scripts have their imports fixed.

import sys
import pycodestyle

sys.modules['pep8'] = sys.modules['pycodestyle']
