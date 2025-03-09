#!/bin/sh

if ! [ -e sqlite-amalgamation-3460100 ]; then
	if ! [ -e sqlite-amalgamation-3460100.zip ]; then
		curl -OJL https://sqlite.org/2024/sqlite-amalgamation-3460100.zip
	fi
	unzip sqlite-amalgamation-3460100.zip
fi

rm -f sqlite-amalgamation-3460100.zip

if ! [ -e bzip2-1.0.8 ]; then
	if ! [ -e bzip2-1.0.8.tar.gz ]; then
		curl -OJL https://sourceware.org/pub/bzip2/bzip2-1.0.8.tar.gz
	fi
	tar xzf bzip2-1.0.8.tar.gz
fi

rm -f bzip2-1.0.8.tar.gz

if ! [ -e phc-winner-argon2-20190702 ]; then
	if ! [ -e phc-winner-argon2-20190702.zip ]; then
		curl -OJL https://github.com/P-H-C/phc-winner-argon2/archive/refs/tags/20190702.zip
	fi
	unzip phc-winner-argon2-20190702.zip
fi

rm -f phc-winner-argon2-20190702.zip

if ! [ -e libtommath-1.3.0 ]; then
	if ! [ -e ltm-1.3.0.zip ]; then
		curl -OJL https://github.com/libtom/libtommath/releases/download/v1.3.0/ltm-1.3.0.zip
	fi
	unzip ltm-1.3.0.zip
fi

rm -f ltm-1.3.0.zip

cd libtommath-1.3.0 && perl gen.pl
cd ..

rm -f ../../config.h
touch ../../config.h
