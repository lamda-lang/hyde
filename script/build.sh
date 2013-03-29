# build obj/runtime
mkdir -p obj/runtime
gcc @script/arg.txt src/runtime/*.c
mv *.o obj/runtime

# build obj/test
mkdir -p obj/test
gcc @script/arg.txt src/test/*.c
mv *.o obj/test

# remove obj
rm -r obj
