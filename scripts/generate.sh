#!/bin/bash
cat generated/gen.txt src/List/UnrolledLinkedList.h src/List/UnrolledLinkedList.cc test/ull/test1.cc >generated/submit.cc
sed -i '/#include "UnrolledLinkedList.h"/'d ./generated/submit.cc
sed -i '/#include "List\/UnrolledLinkedList.h"/'d ./generated/submit.cc
sed -i '/#include "List\/UnrolledLinkedList.cc"/'d ./generated/submit.cc
sed -i '/#include "Utils\/Exception.h"/'d ./generated/submit.cc
sed -i 's/throw Exception(UNKNOWN, "Given data was not found.");/return;/' ./generated/submit.cc
sed -i 's/throw Exception(UNKNOWN, "Given data has already been inserted.");/return;/' ./generated/submit.cc
sed -i 's/const Exception &x/.../' ./generated/submit.cc

