#!/bin/sh
g++ example1.cpp -I.. -o example1 `pkg-config libcurl --libs`
g++ example2.cpp ../Fetch.cpp  -I.. -o example2 `pkg-config libcurl --libs`
