# create build directory
mkdir -p build

# build object files
gcc @tool/arg.txt src/*.c src/test/*.c
mv *.o build
