if [ -d "build" ]; then rm -Rf build; fi
mkdir -p build
mkdir -p output
cd build || exit
rm -rf *
cmake .. -DSIM=ON
make
cd ..
echo Compilation done. Executable in the bin folder
