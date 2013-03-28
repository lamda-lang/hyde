mkdir -p bin
c99 -g -c -O 0 src/*.c 
c99 -g -c -O 0 -I src test/*.c
mv *.o bin
