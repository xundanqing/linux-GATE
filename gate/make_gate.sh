#!/bin/bash

echo "---------------请选择编译版本---------------"
echo "0：8720设备版本"
echo "1：8731设备版本"
echo "2：PC端调试版本"
echo "3：8721设备版本"
echo "--------------------------------------------"
make_type=$1
#read make_type

if [ "$make_type" = "0" ];then
	echo "--------------编译8720设备版本--------------"
	make clean;
	make;
fi

if [ "$make_type" = "1" ];then
	echo "--------------编译8731设备版本--------------"
	make clean;
	make ARCH=arm-hisiv100nptl-linux-;
fi

if [ "$make_type" = "2" ];then
	echo "---------------编译PC调试版本---------------"
	make clean;
	make ARCH=;
fi

if [ "$make_type" = "3" ];then
	echo "---------------编译8721设备版本---------------"
	make clean;
	make ARCH=arm-hisiv300-linux-;
fi

