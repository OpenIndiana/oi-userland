#!/usr/bin/python

import json
import sys

final_manifest = {}

# Read in all the JSON manifest files provided on the command line
# and create a single, merged one.
for manifest in sys.argv[1:]:
    with open(manifest, 'r') as infile:
        final_manifest.update(json.load(infile))

# Write out the merged manifest in JSON
with open('static/dashboard/manifest.json', 'w') as outfile:
    json.dump(final_manifest, outfile, indent=4)
