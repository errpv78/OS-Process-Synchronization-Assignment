Contents:
screenshots - screenshots of both codes
results.txt - it is not generated with code, its contents are manually written by examining the results of
                manager_case1.cpp.
manager_case1.cpp - It first prompts the user to enter for probability p, as given in question and then executes
                    and when deadlock is detected, the program terminates, and all the information regarding deadlock
                    is printed.
manager_case2.cpp - In this no deadlock ever happens so it keeps on executing

The program manager_case1.cpp can be run by executing following command on terminal:
g++ -o m1 -pthread manager_case1.cpp
./m1

The program manager_case2.cpp can be run by executing following command on terminal:
g++ -o m2 -pthread manager_case2.cpp
./m2