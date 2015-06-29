#!/bin/sh

cat /dev/rw_semaphore &
cat /dev/rw_semaphore &
cat /dev/rw_semaphore &
sleep 1
echo abcd >/dev/rw_semaphore &
