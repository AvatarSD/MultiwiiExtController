#!/bin/bash

# $1 is a build configuration and a output folder
# $2 is a builder args

conf=$1
args=$2

if [[ $conf = "" ]]; then
	echo "No config, set Release/ output dir"
	conf="Release"
fi

if [[ $conf = "clean" ]]; then
	conf="Release"
	args="clean"
fi

if [[ $args = "clean" ]]; then
	echo "Clean $conf configuration"
	rm -rf $conf
else
	echo "Build configuration is: $conf"
	if [[ ! -d $conf ]]; then
		mkdir $conf
	fi
	cd $conf
	cmake -DCMAKE_BUILD_TYPE:STRING=$conf ../
	make
	cd ../
fi

exit 0
