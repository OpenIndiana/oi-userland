# Extend default set of security group rules that comes with Openstack
# to include Solaris admin ports.

SECURITY_GROUP_RULES.update({
    'rad_tls': {
        'name': 'RAD TLS',
        'ip_protocol': 'tcp',
        'from_port': '12302',
        'to_port': '12302',
    },
    'rad_gss': {
        'name': 'RAD GSS',
        'ip_protocol': 'tcp',
        'from_port': '6789',
        'to_port': '6789',
    },
    'analytics_bui': {
        'name': 'Analytics BUI',
        'ip_protocol': 'tcp',
        'from_port': '6787',
        'to_port': '6787',
    },
})
