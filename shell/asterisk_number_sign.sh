#!/bin/bash

set -- "First one" "second" "third:one" "" "Fifth: :one"

echo  "\"First one\""  "\"second\""  "\"third:one\""  "\"\""  "\"Fifth: :one\""
echo

echo 'IFS unchanged , using "$*"'
c=0
for i in "$*"
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo 'IFS unchanged , using $*'
c=0
for i in $*
do
	echo "$((c+=1)): [$i]"
done
echo ---
echo

echo 'IFS unchanged , using "$@"'
c=0
for i in "$@"
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo 'IFS unchanged , using $@'
c=0
for i in $@
do
	echo "$((c+=1)): [$i]"
done
echo ---
echo
echo
echo

IFS=:

echo 'IFS=":" , using "$*"'
c=0
for i in "$*"
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo 'IFS=":" , using $*'
c=0
for i in $*
do
	echo "$((c+=1)): [$i]"
done
echo ---
echo

var=$*
echo 'IFS=":" , using $var (var=$*)'
c=0
for i in $var
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo 'IFS=":" , using "$var" (var=$*)'
c=0
for i in "$var"
do
	echo "$((c+=1)): [$i]"
done
echo ---
echo

var="$*"
echo 'IFS=":" , using $var (var="$*")'
c=0
for i in $var
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo 'IFS=":" , using "$var" (var="$*")'
c=0
for i in "$var"
do
	echo "$((c+=1)): [$i]"
done
echo ---
echo
echo
echo

echo 'IFS=":" , using "$@"'
c=0
for i in "$@"
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo 'IFS=":" , using $@'
c=0
for i in $@
do
	echo "$((c+=1)): [$i]"
done
echo ---
echo

var=$@
echo 'IFS=":" , using "$var" (var=$@)'
c=0
for i in "$var"
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo 'IFS=":" , using $var (var=$@)'
c=0
for i in $var
do
	echo "$((c+=1)): [$i]"
done
echo ---
echo

var="$@"
echo 'IFS=":" , using $var (var="$@")'
c=0
for i in $var
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo 'IFS=":" , using "$var" (var="$@")'
c=0
for i in "$var"
do
	echo "$((c+=1)): [$i]"
done
echo ---
echo
