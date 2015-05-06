#!bin/bash

cp ./Makefile ./bin/
cp -v ./src/Source.cpp ./bin/
cp -v ./src/Parser.cpp ./bin/
cp -v ./src/headers/Parser.h

echo "Files copied into: ./bin/"

cd ./bin/
make
