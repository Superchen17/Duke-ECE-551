#!/bin/bash

generatedFile="generated.txt"
expectedFile="expected.txt"

[ -e $generatedFile ] && rm $generatedFile
[ -e $expectedFile ] && rm $expectedFile

for i in $(seq -500 500)
do
    ./isPrime-broken$1 $i >> $generatedFile
    ./isPrime-correct $i >> $expectedFile
done

diff $generatedFile $expectedFile
