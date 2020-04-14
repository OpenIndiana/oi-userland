Gnome-Connection-Manager

Get the latest version here:
http://kuthulu.com/gcm

1. REQUIREMENTS:
you must have python 2.6 or later, python-gtk2, expect, python-vte, libglade2-0, python-glade2

2. INSTALLATION:
- Linux/Unix:
copy the gcm files wherever you want, then execute the gnome_connection_manager.py
example:
/home/someuser/gcm/gnome_connection_manager.py

- FreeBSD:
Edit the file gnome_connection_manager.py and use the full path of the "ssh" and "telnet" binaries in the lines:
SSH_BIN = 'ssh'
TEL_BIN = 'telnet'
Edit the file ssh.expect and replace the first line with the full path of the "expect" command:
#!/usr/bin/expect

3. LANGUAGE:
to force a language start the application with this command:
LANGUAGE=en /home/someuser/gcm/gnome_connection_manager.py

if that doesn't work, try with:
env LANGUAGE=en python /home/someuser/gcm/gnome_connection_manager.py
