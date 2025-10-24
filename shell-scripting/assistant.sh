#!/bin/bash

read -p "Enter your name: " emp_name
read -p "Enter yout department: " emp_dept

echo -e "\n\n**********Welcome $emp_name to $emp_dept Department**********\n\n"

echo -e "Your current working directory is: "
pwd
echo -e "List of files in this diretory: "
ls

echo -e ""

read -p "Enter your age: " emp_age

if [ "$emp_age" -le 17 ]; then
    echo -e "Access restricted -- you are under 18\n"
elif [ "$emp_age" -le 35 ]; then
    echo -e  "Standard Access Granted\n"
else
    echo -e "Supervisor Access granted\n"
fi

read -p "Enter path of your directory: " emp_dir

if [ -d $emp_dir ]; then
    echo -e "Workspace verified\n"
else
    echo -e "Workspace not found - please create it"
fi 

dir=/home/

count=1

for file in "$dir";
do 
    if [ -f "$file" ]; then
        echo -e "$count- $(basename "$file")"
        ((count++))
    else
        echo -e "No file exists\n"
    fi 
done



echo -e "\n\n**********Goodbye! $emp_name from $emp_dept Department**********\n\n"