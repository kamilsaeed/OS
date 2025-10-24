#!/bin/bash

echo "Name: Kamil Saeed"
echo "Age: 20"
echo -e "Favorite Color: Blue\n"


num=-1
    
if [ $num -gt 0 ]; then 
    echo -e "Positive Number\n"
else
    echo -e "Negative Number\n"
fi


num2=10

if [ $num2 -lt 10 ]; then
    echo -e "Small\n"
elif [ $num2 -le 20 ]; then
    echo -e "Medium\n"
else
    echo -e "It is Large\n"
fi


echo "For loop"

for i in {1..5}
do
    echo "Number: $i"
done


echo -e "\nWhile loop"

num3=1

while [ $num3 -le 5 ]
do
    echo "Number: $num3"
    num3=$((num3+1))
done 


sum=$((num2+num3))
echo -e "\nSum of $num2 and $num3 is $sum\n"


echo "Check if givn string is empty or not: "
string="a"

if [ -z "$string" ]; then
    echo -e "String is empty\n"
else
    echo -e "String is not empty\n"
fi


echo "Check if file is readable or not:"
file="file.txt"

if [ -r "$file" ]; then
    echo -e "File exists and is readable\n"
else
    echo -e "File does not exits or is not readable\n"
fi


echo "Check if file is writable or not:"
file="file.txt"

if [ -w "$file" ]; then
    echo -e "File exists and is writable\n"
else
    echo -e "File does not exits or is not writable\n"
fi


echo "Check if directory exists"
dir="Desktop"

if [ ! -d "$dir" ]; then
    echo -e "Directory does not exists\n"
else
    echo -e "Directory exists\n"
fi


num4=1

while [ $num4 -le 10 ];
do

    if [ $num4 -eq 5 ]; then
        break
    fi

    echo "Number: $num4"
    num4=$((num4+1))
done 



dir2="Desktop"
file2="file.txt"

if [ -d "$dir2" -a -w "$dir2" -o -f "$file2" -a -r "$file2" ]; then
    echo -e "\nDirectory exists and writable. File exists and readable\n"
else
    echo -e "\nDirectory or file do not exists"
fi


echo -e "\nPrint number 1-10 but skip 7"

for i in {1..10};
do 
    if [ $i -eq 7 ]; then
        continue
    fi

    echo "Number: $i"
done


echo -e "\nKeep loop running until enter stop"
i=1

while [ $i -eq 1 ];
do 
    echo "Running..."
    read -p "Enter 'stop' to exit: " str
    if [ "$str" == "stop" ]; then
        break
    fi
done















































