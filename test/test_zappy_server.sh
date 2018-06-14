#!/bin/bash

cmd=`dirname $0`/../serveur
error_nb=0

function assert_return()
{
    if [[ $1 -eq 0 ]];then
        $cmd $2 2>&1 >/dev/null
        if [[ $? -eq 0 ]]; then
            status="ok"
        else
            status="ko"
        fi
    else
        expected="$1 errors !"
        if [[ `uname` == "Darwin" ]]; then
            output=`$cmd $2 2>&1 | sed -E "s/"$'\E'"\[([0-9]{1,2}(;[0-9]{1,2})*)?m//g" | grep "$1 errors"`
        else
            output=`$cmd $2 2>&1 | sed -r "s/\x1B\[([0-9]{1,3}((;[0-9]{1,3})*)?)?[m|K]//g" | grep "$1 errors"`
        fi
        if [[ "$output" == "$expected" ]]; then
            status="ok"
        else
            status="ko"
        fi
    fi
    if [[ $status == "ok" ]]; then
        echo -e "[\033[0;33mASSERT\033[0;m:\033[0;32mOK\033[0m] $cmd $2 == $1"
    else
        echo -e "[\033[0;33mASSERT\033[0;m:\033[0;31mKO\033[0m] $cmd $2 == $1"
        error_nb=`expr $error + 1`
    fi
}

# declare test variables
args=(
    ""
    "-x 10 -y 10 -c 20 -n toto tutu -t 10"
    "-p 1234 -y 10 -c 20 -n toto tutu -t 10"
    "-p 1234 -x 10 -c 20 -n toto tutu -t 10"
    "-p 1234 -x 10 -y 10 -n toto tutu -t 10"
    "-p 1234 -x 10 -y 10 -c 20 -t 10"
    "-p 1234 -x 10 -y 10 -c 20 -n toto tutu"
    "-p 1234 -x 10 -y 10 -c 20 -n toto tutu toto -t 10"
)
error=(
    6
    1
    1
    1
    1
    1
    1
    1
)

test_nb=0
for arg in "${args[@]}"
do
    assert_return ${error[$test_nb]} "$arg"
    test_nb=`expr $test_nb + 1`
done
if [[ $error_nb -gt 0 ]]; then
    echo "Total error: $error_nb"
    exit 1
fi
