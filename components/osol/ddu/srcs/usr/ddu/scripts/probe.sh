#!/usr/bin/ksh93
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
#PCI CLASS CODES
#define    PCI_CLASS_NONE        0x0    /* class code for pre-2.0 devices */
#define    PCI_CLASS_MASS        0x1    /* Mass storage Controller class */
#define    PCI_CLASS_NET        0x2    /* Network Controller class */
#define    PCI_CLASS_DISPLAY    0x3    /* Display Controller class */
#define    PCI_CLASS_MM        0x4    /* Multimedia Controller class */
#define    PCI_CLASS_MEM        0x5    /* Memory Controller class */
#define    PCI_CLASS_BRIDGE    0x6    /* Bridge Controller class */
#define    PCI_CLASS_COMM        0x7    /* Communications Controller class */
#define    PCI_CLASS_PERIPH    0x8    /* Peripheral Controller class */
#define    PCI_CLASS_INPUT        0x9    /* Input Device class */
#define    PCI_CLASS_DOCK        0xa    /* Docking Station class */
#define    PCI_CLASS_PROCESSOR    0xb    /* Processor class */
#define    PCI_CLASS_SERIALBUS    0xc    /* Serial Bus class */
#define    PCI_CLASS_WIRELESS    0xd    /* Wireless Controller class */
#define    PCI_CLASS_INTIO        0xe    /* Intelligent IO Controller class */
#define    PCI_CLASS_SATELLITE    0xf    /* Satellite Communication class */
#define    PCI_CLASS_CRYPT        0x10    /* Encrytion/Decryption class */
#define    PCI_CLASS_SIGNAL    0x11    /* Signal Processing class */

# Driver version number --- modinfo
# scsi_vhci info: ./all_devices -L /scsi_vhci
# usb device: if there is usb_mid layer, get productname from this layer. 
# get driver name from the last layer.
# How to detect infrared/bluetooth/winmodem  device

# Class code to be filtered
# "000600", "000601", "000602", "000603", "000604", "0005","000c05", "0008", 
# "000380", "0000", "000b", "Motherboard"
# Normaly 000680 is a bridge device, but there are some nvidia network devices 
# with 000680 classcode.
#
# Description: Probe the system to detect the device information and check the
#              missing driver availability through local driver db or IPS.
#
#              Usage:
#              probe.sh $1 
#              $1 is the device category("network", "storage" etc..)
#              For example, "network" is to call network() function to probe
#              the network devices.


builtin chmod
builtin cp
builtin mkdir
builtin mv
builtin rm
builtin cat

#
# Find the xorg driver of video device on the system
#

function xorg_driver
{
    typeset temp_str x_log x_conf x_run x_driver_list x_driver
    typeset device_section_index_total device_section_line
    typeset driver_list 
    
    ps -e | grep "Xorg" > /dev/null
    if [ $? -eq 0 ]; then
        x_run="Xorg"
        x_log="/var/log/Xorg.0.log"
        if [ -f /etc/X11/xorg.conf ]; then
            x_conf="/etc/X11/xorg.conf"
        elif [ -f /etc/X11/.xorg.conf ]; then
            x_conf="/etc/X11/.xorg.conf"
        fi
    fi
    
    if [ ! -z "${x_run}" ]; then
        if [ -s ${x_log} ]; then
            x_driver_list=$(cat ${x_log} | grep "New driver is" \
                | awk -F\" '{ print $2 }')
            for driver_list in $x_driver_list; do
                if [ ! -z "${driver_list}" ]; then
                    if [ -z "${x_driver}" ]; then
                        x_driver=$driver_list
                    fi
                fi
            done
        fi
    
        if [ -z "${x_driver}" ]; then
            if [ ! -z "${x_conf}" ] && [ -s ${x_conf} ]; then
                device_section_index_total=$(grep -n '^Section\ \"Device\"' \
                    ${x_conf} | awk -F: '{ print $1 }')
                for device_section_index in ${device_section_index_total}; do
                    if [ ! -z "${device_section_index}" ]; then
                        device_section_line=$(sed -n "${device_section_index}"p \
                            ${x_conf})
                        while [ "${device_section_line}" != "EndSection" ]; do
                            if [ -z $(echo "${device_section_line}" \
                                | sed -n '/^[ \t]*#/p') ] && [ ! -z $(echo \
                                "${device_section_line}" | grep "Driver") \
                                ]; then

                                driver_list=$(echo ${device_section_line} \
                                    | awk -F\" '{ print $2 }')
                                if [ -z "${x_driver}" ]; then
                                    x_driver=$driver_list
                                fi
                                break
                            fi
                            device_section_index=$((${device_section_index} + 1))
                            device_section_line=$(sed -n \
                                "${device_section_index}"p ${x_conf})
                        done
                    fi
                done
            fi
        fi
    
        if [ -z "${x_driver}" ]; then
                    x_driver=${video_driver}
        fi
    
        print -u1 "${x_driver}"
    fi
}

#
# Probe and output the network controllers info on the system with the 
# following format.  
# id:Null:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#
#
function network
{
    typeset    index=0 i j
    typeset    NIC_keywords_file=$base_dir/NIC_keywords
    typeset    line total_IDs result devid

    NIC_info_file=/tmp/dvt_network_info_file

    temp_file=/tmp/dvt_network_temp
    temp_file_2=/tmp/dvt_network_temp_2

    # Get the keywords of NIC.
    # CLASS=00020000 indicates a device is a NIC.
    # Non-standard class code NIC is organized by 
    #     class code to improve search efficiency.

    grep "CLASS=" $NIC_keywords_file > $temp_file

    i=1
    total_IDs=$(cat $temp_file | wc -l)
    while [ $i -le $total_IDs ]; do
        line=$(sed -n $i'p' $temp_file)
        keys1[$i]=$(echo $line | awk -F":" '{print $1}')
        keys2[$i]=$(echo $line | awk -F":" '{print $2}')
        i=$(($i + 1))
    done
    rm -f $temp_file

    lines=$(cat $ctl_file | wc -l)
    i=1
    while [ $i -le $lines ]; do
        line=$(sed -n $i'p' $ctl_file)
        j=1
        while [ $j -le $total_IDs ]; do
            result=$(echo $line | grep ${keys1[$j]})
            if [ ! -z $result ]; then
                if [ ! -z ${keys2[$j]} ]; then
                    devid=$(echo $line | awk -F":" '{print $2}' | cut -d'=' -f2)
                    result=$(echo ${keys2[$j]} | grep $devid)
                fi
            fi
            if [ ! -z $result ]; then
                echo $line >> $temp_file
                break
            fi
            j=$(($j + 1))
        done
        i=$(($i + 1))
    done
    rm -f $temp_file_2
    lines=
    line=


    if [ -s $temp_file ]; then
        mv -f $temp_file $NIC_info_file

        #cat $NIC_info_file
        for i in $(cat $NIC_info_file); do
            echo ${index}::$i | eval $chg_format
            ((index=index+1))
        done

        rm -f $NIC_info_file
    fi
}

#
# Probe and output the storage controllers info on the system with the
# following format.
# id:Null:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#
#
function storage
{
    typeset index 
    typeset class_code_1 class_code_2 str_class_code
    typeset inst 

    index=100
    c_file=/tmp/str_ctrl_file
    c_file1=/tmp/str_ctrl_file_1
    c_file2=/tmp/str_ctrl_file_2
    c_file3=/tmp/str_ctrl_file_3
    c_file4=/tmp/str_ctrl_file_4
    c_file5=/tmp/str_ctrl_file_5
    class_code_1="CLASS=000100|CLASS=000101|CLASS=000104|CLASS=000105"
    class_code_2="|CLASS=000106|CLASS=000107|CLASS=000180|CLASS=000c04"
    str_class_code=${class_code_1}${class_code_2}

    cat $ctl_file | egrep ${str_class_code}  > $c_file

    # deal with the out put like this:
    # "American Megatrends Inc. MegaRAID:DEVID=0x1960:CLASS=00010400 \
    #  :/pci@3,0/pci8086,b154/pci8086,b154/pci1028,493:amr"

    # deal with same kind of controllers
    cat $c_file | awk -F: '{print $1}' | sort | uniq -c > $c_file2
    if [ ! -s $c_file2 ]; then
        exit 
    fi

    while read inline; do
        inst=$(echo $inline | awk '{print $1}')
        if [ $inst -gt 1 ]; then
            ctrl=$(echo $inline |
    awk '
    {
        for(i=2; i<NF; i++)
        printf("%s ", $i)
        printf("%s", $i)
        printf("\n")
    }')

            cat $c_file | fgrep "${ctrl}:" >$c_file3
            :>$c_file4
            i=1
            while [ $i -le $inst ]; do
                cat $c_file3 | sed -n "$i"p | sed "s;:;(${i}) :;1" >> $c_file4
                ((i = $i + 1))
            done
            cat $c_file | fgrep -v "${ctrl}:" > $c_file5
            cat $c_file4 $c_file5 > $c_file
        fi
    done<$c_file2

    for i in $(cat $c_file); do
        echo ${index}::$i | eval $chg_format
        ((index=index+1))
    done

    rm -f $c_file $c_file1 $c_file2 $c_file3 $c_file4 $c_file5
}

#
# Probe and output the audio device info on the system with the
# following format.
# id:Null:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#
#

function audio
{
    typeset index audio_class

    index=200
    audio_class="CLASS=00040100|CLASS=00040300"

    if [ -z $(cat $ctl_file | /usr/bin/egrep -e ${audio_class}) ]; then
      return 0
    fi

    for i in $(cat $ctl_file | /usr/bin/egrep -e ${audio_class}); do
        echo ${index}::$i | eval $chg_format
        ((index=index+1))
    done
}

#
# Probe and output the video info on the system with the
# following format.
# id:Null:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#
function video
{
    typeset index video_class

    index=300
    video_class="CLASS=00030000|CLASS=00038000"

    xorg_drv=$(xorg_driver)
        
    if [ -z $(cat $ctl_file | /usr/bin/egrep -e ${video_class}) ]; then
      return 0
    fi

    for i in $(cat $ctl_file | /usr/bin/egrep -e ${video_class}); do
        if [ ! -z "$xorg_drv" ]; then
             i="$(echo $i | awk -F":" '{printf "%s:%s:%s:%s::%s:%s:%s\n", \
                 $1,$2,$3,$4,$6,$7,$8}' | eval sed 's/::/:"$xorg_drv":/g')"
        fi
        echo ${index}::$i | eval $chg_format
        ((index=index+1))
    done
}

#
# Probe and output the cd/dvd info on the system with the
# following format.
# id:parent id:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#

function cd_dvd
{
    typeset index p_index 
    typeset dev_pci_path ctl_pci_path_1

    index=400
    dvt_cd_dev_tmpfile=/tmp/dvt_cd_dev_tmpfile
    dvt_cd_ctl_tmpfile=/tmp/dvt_cd_ctl_tmpfile
    dvt_cd_ctl_tmpfile1=/tmp/dvt_cd_ctl_tmpfile1
    pfexec ${bin_dir}/all_devices -v -t ddi_block:cdrom | sort | uniq \
        |awk -F')' '{print $2}' > $dvt_cd_dev_tmpfile
    pfexec rm -f $dvt_cd_ctl_tmpfile
    for i in $(cat $dvt_cd_dev_tmpfile); do
        dev_pci_path=$(echo $i | cut -d: -f4)
        pfexec ${bin_dir}/all_devices -p ${dev_pci_path} >> $dvt_cd_ctl_tmpfile
    done
    cat $dvt_cd_ctl_tmpfile 2>/dev/null | sort | uniq > $dvt_cd_ctl_tmpfile1
    for i in $(cat ${dvt_cd_ctl_tmpfile1}); do
        ctl_pci_path=$(echo $i | cut -d: -f4)
        ctl_pci_path_1=$(pfexec ${bin_dir}/all_devices -d $ctl_pci_path \
                        | grep "devfs path" | cut -d: -f2)

        echo ${index}::$i | eval $chg_format
        p_index=${index}
        ((index=index+1))
        for j in $(cat ${dvt_cd_dev_tmpfile} | grep ":${ctl_pci_path_1}"); do
            echo ${index}:${p_index}:$j | awk -F":" \
                '{printf "%s:%s:%s::%s:%s:%s:%s\n", $1,$2,$3,$6,$7,$8,$9}'
            ((index=index+1))
        done
    done

    rm -f $dvt_cd_dev_tmpfile
    rm -f $dvt_cd_ctl_tmpfile
    rm -f $dvt_cd_ctl_tmpfile1
}

#
# Probe and output the usb device info on the system with the
# following format.
# id:parent id:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#
#

function usb
{
    typeset index p_index usb_class
    typeset  pci_path ctl_drv_name dev_pci_path dev_drv_name p_name
    typeset  up_dev_pci_path 

    index=500
    usb_class="CLASS=000c0300|CLASS=000c0310|CLASS=000c0320"
    temp_file1=/tmp/dvt_tmp_file1
    
    cat $ctl_file | egrep -e ${usb_class} > $temp_file1
    for i in $(cat $temp_file1); do
        echo ${index}::$i | eval $chg_format
        p_index=${index}
        ((index=index+1))
        pci_path=$(echo $i | cut -d: -f4)
        ctl_drv_name=$(echo $i | cut -d: -f5)
        for j in $(pfexec ${bin_dir}/all_devices -L  $pci_path); do
            dev_pci_path=$(echo $j | cut -d: -f3)
            dev_drv_name=$(echo $j | cut -d: -f4)
            if [ $dev_drv_name = "usb_mid" ]; then
                echo ${index}:${p_index}:$j 
                ((index=index+1))
            else
                up_dev_pci_path=$(echo $dev_pci_path \
                    | awk -F"/" '{for(i=2;i<NF;i++)
                    printf("/%s",$i)}')
                p_name=$(pfexec ${bin_dir}/all_devices \
                    | grep "${up_dev_pci_path}:usb_mid")
                if [ $? -eq 0 ]; then
                    p_name=$(echo ${p_name} | sed 's/^    *(Dev)//' \
                        | cut -d: -f1)
                    print -u1 "${index}:${p_index}:(${p_name})${j}"
                    ((index=index+1))
                else
                    print -u1 ${index}:${p_index}:${j}
                    ((index=index+1))
                fi
            fi
         done
    done

    rm -f $temp_file1
}

#
# Probe and output the battery info on the system with the
# following format.
# id:Null:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#
#

function battery
{
    typeset index 
    typeset vendor model tech per charge_des charge_cur dev_path
    typeset driver t_s  t_s1

    index=700
    battery_tmpfile=/tmp/battery_tmpfile
    battery_tmpfile1=/tmp/battery_tmpfile1
    battery_tmpfile2=/tmp/battery_tmpfile2
    if [ -f ${bin_dir}/bat_detect ]; then
        ${bin_dir}/bat_detect -l > $battery_tmpfile 2>/dev/null
        for i in $(cat $battery_tmpfile); do
            ${bin_dir}/bat_detect -d $i > $battery_tmpfile1
            vendor=$(grep battery.vendor $battery_tmpfile1 \
                | cut -d: -f2 | tr -d \')
            model=$(grep battery.model $battery_tmpfile1 | cut -d: -f2 \
                | tr -d \' | tr -d ' ')
            tech=$(grep battery.reporting.technology $battery_tmpfile1 \
                | cut -d: -f2 | tr -d \')
            per=$(grep battery.charge_level.percentage $battery_tmpfile1 \
                | cut -d: -f2 | tr -d \')
            charge_des=$(grep battery.charge_level.design $battery_tmpfile1 \
                | cut -d: -f2 | tr -d \')
            charge_cur=$(grep battery.charge_level.current $battery_tmpfile1 \
                | cut -d: -f2 | tr -d \')
            echo "scale = 1" > $battery_tmpfile2
            echo "$charge_des/1000" >> $battery_tmpfile2
            charge_des=`bc < $battery_tmpfile2`
            echo "scale = 1" > $battery_tmpfile2
            echo "$charge_cur/1000" >> $battery_tmpfile2
            charge_cur=`bc < $battery_tmpfile2`
            dev_path=$i
            driver=$(grep info.solaris.driver  $battery_tmpfile1 | cut -d: -f2 \
                | tr -d \')
            t_s="${vendor} ${charge_des}Wh ${tech} ${model}"
            t_s1="( ${per}%  ${charge_cur}Wh )"
            print -u1 "${index}::${t_s} ${t_s1}:::${dev_path}:${driver}:0:Attached:"
            ((index=index+1))
        done
        rm -f $battery_tmpfile $battery_tmpfile1 $battery_tmpfile2
    fi
}

#
# Probe and output the cpu info on the system with the
# following format.
# id:Null:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#
#

function cpu
{
    typeset index cpu_tmpfile cpu_tmpfile1 cpu_num cpu_type cpu_core
    index=800
    cpu_tmpfile=/tmp/cpu_tmpfile
    cpu_tmpfile1=/tmp/cpu_tmpfile1
    cpu_num=$(${bin_dir}/dmi_info -C | grep "CPU Number" | cut -d":" -f2)
    cpu_type=$(${bin_dir}/dmi_info -C | grep "CPU Type" | cut -d":" -f2)
    cpu_core=$(${bin_dir}/dmi_info -C | grep "cores" | cut -d":" -f2)

    print -u1 "${index}::${cpu_num} X ${cpu_type}, ${cpu_core}-core:::cpu:---:0:Attached:"
}

#
# Probe and output the memory info on the system with the
# following format.
# 801:Null:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#
#
function memory
{
    typeset index phy_mem max_mem

    index=801
    phy_mem=$(${bin_dir}/dmi_info -m | grep "Physical Memory" | cut -d: -f2)
    max_mem=$(${bin_dir}/dmi_info -m | grep "Maximum Memory Support" \
        | cut -d: -f2)
    if [ ! -z "$max_mem" ]; then
        max_mem="; $max_mem maximum"
    fi

    print -u1 "${index}::${phy_mem} ${max_mem}:::memory:---:0:Attached:"
}

#
# Probe and output the others device info on the system with the
# following format.
# id:Null:Device Name:device id:class code:pci id:driver name:
# instance id:driver status:vendor id
#
#

function others
{
    typeset index c1 c2 c3 c4 c5 other_class class_code
    index=600
    c1="CLASS=00030000|CLASS=000c0300|CLASS=000c0310|CLASS=000c0320"
    c2="|CLASS=00040100|CLASS=00040300|CLASS=000100|CLASS=000101"
    c3="|CLASS=000104|CLASS=000105|CLASS=000106|CLASS=000107"
    c4="|CLASS=000180|CLASS=000c04|CLASS=0006|CLASS=00020000|CLASS=00038000"
    c5="|CLASS=00028000|CLASS=0005|CLASS=0008|CLASS=000a|CLASS=000b"
    other_class="${c1}${c2}${c3}${c4}${c5}"

    for i in $(cat $ctl_file | egrep -v -e ${other_class}); do
        #
        # Filter out devices with CLASS=unknown on sparc platform
        #
	if [ $platform = "sparc" ]; then
	    class_code=$(echo $i | cut -d: -f3 | cut -d= -f2)
            if [ $class_code = 'unknown' ]; then
	        continue
            fi
        fi
        
        echo ${index}::$i | eval $chg_format
        ((index=index+1))
    done
}

#
# Init process before probe the devices.
#
function init
{
    pfexec ${bin_dir}/all_devices -s 
    pfexec ${bin_dir}/all_devices -c | egrep -v ${e_class} \
        > $ctl_file
    #
    # Make /tmp/ddu_err.log writable for every user
    #
    if [ -f /tmp/ddu_err.log ]; then
        pfexec chmod 666 /tmp/ddu_err.log
    else
        touch /tmp/ddu_err.log; chmod 666 /tmp/ddu_err.log
    fi
}

function clean_up
{
    {
        rm -f $s_result_file $temp_file $temp_file_2 $NIC_info_file
        rm -f $c_file $c_file1 $c_file2 $c_file3 $c_file4 $c_file5
        rm -f $dvt_cd_ctl_tmpfile $dvt_cd_dev_tmpfile $ctl_file
        rm -f $dvt_cd_ctl_tmpfile $dvt_cd_ctl_tmpfile1 $temp_file1
        rm -f $battery_tmpfile $battery_tmpfile1 $battery_tmpfile2
    } >/dev/null 2>&1
}
        

#Main()

PATH=/usr/bin:/usr/sbin:$PATH; export PATH
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/ddu/lib; export LD_LIBRARY_PATH

trap 'clean_up;exit 10' KILL INT
trap 'clean_up' EXIT

#
# Confirm the correct number of commnad line argument
#
if (( $# != 1 )); then
    exit 1
fi

typeset -r base_dir=$(dirname $0)
typeset -r platform=$(uname -p)
typeset -r bin_dir=$(echo $base_dir |sed 's/scripts$/bin\//')"$platform"
typeset    ctl_file=/tmp/dvt_ctl_file
#
# net_stat can be 0,1,2 or 3 
# 0:can connet to IPS 
# 1:can not connect to IPS 
# 2:No need to connect IPS as there is a driver for the device in the system 
# 3. 3rd party driver.
#
typeset net_stat=0
typeset matched_drv=
typeset matched_drv_pkg_type= #SVR4,IPS,DU,UNK
typeset chg_format="sed -e 's/DEVID=//' -e 's/CLASS=//' -e 's/VENDOR=//'"

#
# Set carriage return to IFS
#

IFS='
'


typeset c_1="CLASS=0000|CLASS=0005|CLASS=000b|CLASS=000c05"
typeset c_2="|CLASS=0008|^Motherboard"
typeset e_class="${c_1}${c_2}"
typeset ret_result

if [ ! -s "$ctl_file" ]; then
    pfexec ${bin_dir}/all_devices -c | egrep -v ${e_class} > $ctl_file
fi

chmod 666 $ctl_file 2>/dev/null

case $1 in
storage | audio | video | network) 
    $1
;;
cd_dvd | usb | battery | init)  
    $1
;;
cpu | memory | others)
    $1
;;
*) 
    exit 1
;;
esac

ret_status=$?

return ${ret_status}
