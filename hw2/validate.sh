#!/bin/bash

if [ $# -eq 0 ]; then
	echo Expected hw name
	exit 0
fi

HW=$1
HW_PATH=$HOME/$HW
HW_EXEC=$HW_PATH/$HW
ANS_PATH=$HW_PATH/answer
RES_PATH=$HW_PATH/results

if [ -e $ANS_PATH ]; then
	rm -rf $ANS_PATH
fi

cp /home/share/$HW $ANS_PATH -r

if ! [ -e $RES_PATH ]; then
	mkdir $RES_PATH
fi
rm $RES_PATH/*


OLD_IFS=$IFS
IFS="_"

if [ "$HW" == "hw1" ]; then
	for file in $ANS_PATH/result_*; do
	
		read -ra str <<< $file
	
		N=${str[1]}
	
		$HW_EXEC $N > $RES_PATH/result_$N
	
		diff -sq $ANS_PATH/result_$N $RES_PATH/result_$N
	done

elif [ "$HW" == "hw2" ]; then
	for file in $ANS_PATH/*.csv; do
	
		read -ra str <<< $file

		N=${str[1]:4:1}
		
		$HW_EXEC "$file" > $RES_PATH/result_$N

	
		diff -sq $ANS_PATH/result_$N $RES_PATH/result_$N
	done
fi
