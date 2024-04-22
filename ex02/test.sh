#!/bin/bash

for N in $(seq 2 3000)
do
    output=$(make test N=$N | grep "SUCCESS")
    if [[ -z "$output" ]]; then
        echo "Test failed for N=$N"
		break
	else
		echo "Test $N passed"
    fi
done