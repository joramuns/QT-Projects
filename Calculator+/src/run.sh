#!/bin/bash
make clean
cd ..
docker rmi -f valgrindcheck:1.0 && docker build . -t valgrindcheck:1.0 && docker run valgrindcheck:1.0

