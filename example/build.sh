#!/bin/sh
g++ --std=c++0x example1.cpp -I.. -o example1 `pkg-config libcurl --libs`
g++ --std=c++0x example2.cpp ../Fetch.cpp  -I.. -o example2 `pkg-config libcurl --libs`
