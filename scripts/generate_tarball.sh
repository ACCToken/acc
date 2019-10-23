#!/usr/bin/env bash
set -eo pipefail

NAME=$1
ACC_PREFIX=${PREFIX}/${SUBPREFIX}
mkdir -p ${PREFIX}/bin/
#mkdir -p ${PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${ACC_PREFIX}/bin
mkdir -p ${ACC_PREFIX}/licenses/acc
#mkdir -p ${ACC_PREFIX}/include
#mkdir -p ${ACC_PREFIX}/lib/cmake/${PROJECT}
#mkdir -p ${ACC_PREFIX}/cmake
#mkdir -p ${ACC_PREFIX}/scripts

# install binaries 
cp -R ${BUILD_DIR}/bin/* ${ACC_PREFIX}/bin  || exit 1

# install licenses
cp -R ${BUILD_DIR}/licenses/acc/* ${ACC_PREFIX}/licenses || exit 1

# install libraries
#cp -R ${BUILD_DIR}/lib/* ${ACC_PREFIX}/lib

# install cmake modules
#sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/EosioTesterPackage.cmake &> ${ACC_PREFIX}/lib/cmake/${PROJECT}/EosioTester.cmake
#sed "s/_PREFIX_/\/${SPREFIX}\/${SSUBPREFIX}/g" ${BUILD_DIR}/modules/${PROJECT}-config.cmake.package &> ${ACC_PREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake

# install includes
#cp -R ${BUILD_DIR}/include/* ${ACC_PREFIX}/include

# make symlinks
#pushd ${PREFIX}/lib/cmake/${PROJECT} &> /dev/null
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake ${PROJECT}-config.cmake
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/EosioTester.cmake EosioTester.cmake
#popd &> /dev/null

for f in $(ls "${BUILD_DIR}/bin/"); do
   bn=$(basename $f)
   ln -sf ../${SUBPREFIX}/bin/$bn ${PREFIX}/bin/$bn || exit 1
done
echo "Generating Tarball $NAME.tar.gz..."
tar -cvzf $NAME.tar.gz ./${PREFIX}/* || exit 1
rm -r ${PREFIX} || exit 1
