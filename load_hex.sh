#!/bin/bash
INPUT=./out.hex
 
while IFS= read -r -n1 char
do
    echo -n "$char"
    sleep .001
done < "$INPUT"
