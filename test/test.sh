#!/bin/bash

TESTOUTPUT='./testoutput'
TESTCASE='./testcase'

echo "please enter test case min, in the form of lol*"
read min_t
echo "please enter test case max, in the form of lol*"
read max_t

rm -r $TESTOUTPUT
mkdir $TESTOUTPUT

chmod 777 menu
chmod 777 sample


for ((j=$min_t; j<=$max_t; j++))
    do
        ./menu < $TESTCASE/input$j > $TESTOUTPUT/o1$j
        ./sample < $TESTCASE/input$j > $TESTOUTPUT/o2$j
        echo "test case $j finished"
done


echo "/********************************compare restuls****************************************/"


for ((j=$min_t; j<=$max_t; j++))
    do
        diff -wiB $TESTOUTPUT/o1$j $TESTOUTPUT/o2$j
        echo "test case $j passed"
done