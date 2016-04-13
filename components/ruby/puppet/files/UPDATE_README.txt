When updating puppet to a newer version one of the required update
steps is to update the puppet SMF configuration file.  To aid in
that process the update_smf.py utility can be used to automate the
regeneration of this file.  To use this utility follow the outlined
steps below.


1. Update the puppet release and perform all update activities
   associated with it.

2. Generate and install the puppet release on a system.

3. Execute the following puppet command

$ puppet agent --genconfig > puppet.conf

4. Copy or make available the puppet.conf file created in step 3
   to the system with the userland tree

5. Execute the following commands:

$ cd <userland>/components/puppet/files
$ python update_smf.py -c <path>/puppet.conf -s puppet.xml 
      -v <puppet_version> -o puppet.new.xml

6. Perform a quick check of the resulting SMF file puppet.new.xml
   to make sure everything looks correct. 

7. Update the current puppet.xml file with the new version

$ mv puppet.new.xml puppet.xml


