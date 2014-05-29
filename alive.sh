#!/bin/sh

pid=$(pidof -o %PPID -x alive.sh)
[ "$pid" != "" ] && exit

while [ true ]; do
	ping=$(./ping.sh 2>&1)
	date +"%D %T: $ping" >/tmp/ping.log
	sleep 1 # But ping should wait up to 60 seconds unless events are waiting
done
