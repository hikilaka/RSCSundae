#!/bin/sh
mkdir -p stage/data/
cp -p rscsundae.exe stage/
cp -p openssl-3/x86/bin/libcrypto-3.dll stage/
cp -p lua54.dll stage/
cp -Rp ../../data/settings.ini stage/data/
cp -Rp ../../data/*.jag stage/data/
