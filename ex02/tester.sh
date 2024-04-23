#!/bin/bash

for N in $(seq 2 3000)
do
    output=$(make test N=$N | grep "Error")
    if [[ -z "$output" ]]; then
		echo "Test $N passed"
	else
		echo "Test failed for N=$N"
		break
    fi
done