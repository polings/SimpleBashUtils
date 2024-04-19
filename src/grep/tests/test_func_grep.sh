#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"Linus tests/test_1_grep.txt tests/test_2_grep.txt"
"-e Linus tests/test_1_grep.txt"
"-i LINUS tests/test_1_grep.txt"
"-v Linus tests/test_1_grep.txt"
"-c Linus tests/test_1_grep.txt"
"-l Linus tests/test_1_grep.txt tests/test_2_grep.txt tests/patterns_grep.txt"
"-n Linus tests/test_1_grep.txt"

"-o Linus tests/test_1_grep.txt"
"-h Linus tests/test_1_grep.txt tests/test_2_grep.txt"
"-s Linus find_me.txt"
"-f tests/patterns_grep.txt tests/test_2_grep.txt"

"-cv Linus tests/test_1_grep.txt"
"-iv Linus tests/test_1_grep.txt"
"-lv Linus tests/test_1_grep.txt tests/test_2_grep.txt tests/patterns_grep.txt"
"-ho Linus tests/test_1_grep.txt tests/test_2_grep.txt"
"-nf tests/patterns_grep.txt tests/test_2_grep.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ../grep/s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
    else
      (( FAIL++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

for i in "${tests[@]}"
do
    var="-"
    testing $i
done


echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
