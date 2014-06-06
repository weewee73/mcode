#!/bin/bash

while true; do
    read -p "Do you want to continue (Y/N)?" answer
    case $answer in
        [Yy]* ) echo "YES"; break;;
        [Nn]* ) echo "NO"; break;;
            * ) echo "Please answer yes or no.";;
    esac
done
