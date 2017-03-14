#!/bin/bash
#if [ ! -n "$1" ];then
#	echo "i"
#	exit -1
#fi
git remote rm origin 
git remote add origin git@github.com:zhangxinming1991/mfc.git
git remote show origin
