#!/bin/sh

cat /dev/seq_lock &

echo abcd >/dev/seq_lock 
