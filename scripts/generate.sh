#!/bin/bash
cat generated/gen.txt src/List/UnrolledLinkedList.h src/List/UnrolledLinkedList.cc test/test.cc >generated/submit.cc
sed -i '/#include "UnrolledLinkedList.h"/'d ./generated/submit.cc
sed -i '/#include "List\/UnrolledLinkedList.h"/'d ./generated/submit.cc
sed -i '/#include "Utils\/Exception.h"/'d ./generated/submit.cc
sed -i 's/throw Exception(UNKNOWN, "Not found.");/return;/' ./generated/submit.cc
