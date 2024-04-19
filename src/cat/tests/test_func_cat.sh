#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"-b tests/test_case_cat.txt"
"-e tests/test_case_cat.txt"
"-n tests/test_case_cat.txt"
"-s tests/test_case_cat.txt"
"-t tests/test_case_cat.txt"
"-v tests/test_case_cat.txt"
"-E tests/test_case_cat.txt"
"-T tests/test_case_cat.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ../cat/s21_cat $t > test_s21_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(diff -s test_s21_cat.log test_sys_cat.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    then
      (( SUCCESS++ ))
        echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $t"
    else
      (( FAIL++ ))
        echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $t"
    fi
    rm test_s21_cat.log test_sys_cat.log
}


# 1 параметр
for var1 in b
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done


echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"