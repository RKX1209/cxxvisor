#!/bin/bash -e
#
# K2E Project
#
# Copyright (C) 2017
# Author: Ren Kimura        <rkx1209dev@gmail.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

%ENV_SOURCE%

if [[ ! -d "$BUILD_ABS/source_llvm" ]]; then
    $BUILD_ABS/build_scripts/fetch_llvm.sh $BUILD_ABS
fi

rm -Rf $BUILD_ABS/build_libllvm
rm -Rf $BUILD_ABS/sysroot/x86_64-elf/include/llvm
mkdir -p $BUILD_ABS/build_libllvm

pushd $BUILD_ABS/build_libllvm

if [[ $PRODUCTION == "yes" ]]; then
    BUILD_TYPE=Release
else
    BUILD_TYPE=Debug
fi

if [[ $compiler == *"clang"* ]]; then
    cc="$BUILD_ABS/build_scripts/x86_64-bareflank-clang"
    cxx="$BUILD_ABS/build_scripts/x86_64-bareflank-clang++"
else
    cc="$BUILD_ABS/build_scripts/x86_64-bareflank-gcc"
    cxx="$BUILD_ABS/build_scripts/x86_64-bareflank-g++"
fi

cmake $BUILD_ABS/source_llvm/ \
    -DCMAKE_SYSTEM_NAME=Linux \
    -DCMAKE_INSTALL_PREFIX=$BUILD_ABS/sysroot/x86_64-elf/ \
    -DLLVM_TARGETS_TO_BUILD="X86" \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_C_COMPILER=$cc \
    -DCMAKE_CXX_COMPILER=$cxx \
    -DLLVM_BUILD_TOOLS=OFF \
    -DLLVM_INCLUDE_TOOLS=OFF \
    -DLLVM_INCLUDE_TESTS=OFF \
    -DLLVM_ENABLE_THREADS=OFF \
    -DLLVM_ENABLE_ASSERTIONS=OFF \
    -DLLVM_ENABLE_EH=OFF \
    -DBUILD_SHARED_LIBS=OFF

make -j6
make -j6 install

popd
