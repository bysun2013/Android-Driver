#!/bin/sh

cat /dev/semaphore &
sleep 1
echo data >/dev/semaphore
