
#!/bin/bash
cat generated/gen.txt src/Utils/Exception.h src/Utils/TokenScanner.h src/Utils/TokenScanner.cc src/Files/FileSystem.h src/List/UnrolledLinkedList.h src/List/UnrolledLinkedList.cc src/User/UserSystem.h src/User/UserSystem.cc src/Book/BookSystem.h src/Book/BookSystem.cc src/BookStore.h src/BookStore.cc src/main.cc >generated/submit.cc
sed -i '/#include "Exception.h"/'d ./generated/submit.cc
sed -i '/#include "Utils\/Exception.h"/'d ./generated/submit.cc
sed -i '/#include "TokenScanner.h"/'d ./generated/submit.cc
sed -i '/#include "Utils\/TokenScanner.h"/'d ./generated/submit.cc
sed -i '/#include "FileSystem.h"/'d ./generated/submit.cc
sed -i '/#include "Files\/FileSystem.h"/'d ./generated/submit.cc
sed -i '/#include "UnrolledLinkedList.h"/'d ./generated/submit.cc
sed -i '/#include "List\/UnrolledLinkedList.h"/'d ./generated/submit.cc
sed -i '/#include "UserSystem.h"/'d ./generated/submit.cc
sed -i '/#include "User\/UserSystem.h"/'d ./generated/submit.cc
sed -i '/#include "BookSystem.h"/'d ./generated/submit.cc
sed -i '/#include "Book\/BookSystem.h"/'d ./generated/submit.cc
sed -i '/#include "Bookstore.h"/'d ./generated/submit.cc
