#!/bin/bash

day=""
session=$(cat ".session")

usage() {
    echo "Usage: $0 -d <day>"
    echo "Options:"
    echo "  -d <day>: Specify the day to download. Values from 1 to 25. Format 01, 02, ..., 25."
}

while getopts ":d:v:h" opt; do
    case $opt in
        d)
            day="$OPTARG"
            ;;
        h)
            usage
            exit 0
            ;;
        \?)
            echo "Invalid option: -$OPTARG"
            usage
            exit 1
            ;;
        :)
            echo "Option -$OPTARG requires an argument."
            usage
            exit 1
            ;;
    esac
done

if [ -z "$day" ]; then
    echo "Missing day argument."
else
    curl -b "session=${session}" -o "input/day${day}" "https://adventofcode.com/2023/day/$((10#$day))/input" > /dev/null 2>&1
fi


