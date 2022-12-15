#!/bin/bash
./samples/main <samples/test.in >samples/std.out
rm -r data
./bin/test/Bookstore_tst_1 <samples/test.in >samples/test.out
diff samples/std.out samples/test.out >samples/test.log

