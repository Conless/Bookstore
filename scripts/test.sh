#!/bin/bash
rm -rf data
for ((var = 1 ; $var <= 5; var++))
do
    FILENAME='samples/advanced/'$var'.in'
    ./code <$FILENAME >test.out
    ./code_wly <$FILENAME >std.out
    DIFF=$(diff test.out std.out >test.log)
    if ["$DIFF" == ""]
    then
        echo "Answer correct on testcase 1, testpoint "$var"."
    else
        echo "Answer wrong on testcase 1, testpoint "$var"."
    fi
done
