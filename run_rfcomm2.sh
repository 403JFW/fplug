#!/bin/bash

if [ $# -ne 1 ]; then
  echo Usage: ./record_fplug.sh rfcomm
  echo
  echo Ex: ./record_fplug.sh 0
  exit 1
fi

DEVICE="/dev/rfcomm${1}"

rfcomm -r connect $1 &
sleep 10

while true
do
  if [ ! -e $DEVICE ]; then
    NOW=`/bin/date +'%Y/%m/%d %H:%M:%S'`
    echo "Disconnected $NOW"
    rfcomm -r connect $1 &
    sleep 10
  fi
  sleep 1
done
