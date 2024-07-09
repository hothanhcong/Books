#!/bin/bash

#lt : <
#gt : >
#le : <=
#ge : >=
#eq : ==
#ne : !=

NUM=200

if [ $NUM -le 100 ]
then
	echo "The condition is true"
else
	echo "not equal"
fi

if [ -e ~/catkin_ws ]
then
	echo "File exist"
else
	echo "not exist"
fi

command=htop

if command -v $command
then
	echo "$command is available, run it now"
else
	echo "$command is not available, installing it"
	sudo apt update && sudo apt install $command
fi

$command
