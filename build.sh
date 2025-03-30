#module load gcc/11.2.1 cuda/12.2.2
rm -rf build
mkdir -p build && cd build
cmake $@ -S ..
make -j8
