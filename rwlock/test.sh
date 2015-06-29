#!/bin/sh

./test_rwlock &
./test_rwlock &
./test_rwlock &

echo abcd >/dev/rw_lock &
