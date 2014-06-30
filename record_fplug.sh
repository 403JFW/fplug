#!/bin/bash

if [ $# -ne 2 ]; then
  echo Usage: ./record_fplug.sh rfcomm name
  echo
  echo Ex: ./record_fplug.sh 0 server_room
  echo device=/dev/rfcomm0 name=server_room
  exit 1
fi

DEVICE="/dev/rfcomm${1}"

if [ ! -e $DEVICE ]; then
  sleep 10
  if [ ! -e $DEVICE ]; then
    exit 1
  fi
fi

FPLUG=`/home/user/fplug/record_fplug $DEVICE`
DATE=`date +%Y%m`

LOGFILE="/home/user/Logs/fplug/${2}/fplug_${DATE}.csv"

echo $FPLUG >> $LOGFILE

# DEST="fuka@49.212.202.118:/home/user/Logs/fplug/${2}/fplug_${DATE}.csv"
# /usr/bin/rsync -a -e "ssh -i /home/user/.ssh/id_rsa" $LOGFILE $DEST
