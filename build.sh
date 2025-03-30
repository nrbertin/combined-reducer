#module load gcc/11.2.1 cuda/12.2.2
rm -rf build
mkdir -p build && cd build
cmake -DKokkos_ENABLE_SERIAL=On -DKokkos_ENABLE_CUDA=On -DKokkos_ARCH_VOLTA70=On ..
make -j8
