#!/bin/bash

if [ $# -ne 2 ]; then
  echo Usage: ./record_fplug.sh rfcomm address
  echo
  echo Ex: ./record_fplug.sh 0 aa:bb:cc:dd:ee:ff
  exit 1
fi

DEVICE="/dev/rfcomm${1}"

rfcomm connect $1 $2 &
sleep 10

while true
do
  if [ ! -e $DEVICE ]; then
    NOW=`/bin/date +'%Y/%m/%d %H:%M:%S'`
    echo "Disconnected $NOW"
    rfcomm connect $1 $2 &
    sleep 10
  fi
  sleep 1
done
