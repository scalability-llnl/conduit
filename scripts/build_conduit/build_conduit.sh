#!/bin/bash

##############################################################################
# Demonstrates how to manually build Conduit and its dependencies, including:
#
#  zlib, hdf5
#
# usage example:
#   env enable_mpi=ON enable_openmp=ON ./build_conduit.sh
#
#
# Assumes: 
#  - cmake is in your path
#  - selected compilers are in your path or set via env vars
#  - [when enabled] MPI and Python (+numpy and mpi4py), are in your path
#
##############################################################################
set -eu -o pipefail

##############################################################################
# Build Options
##############################################################################

# shared options
enable_fortran="${enable_fortran:=OFF}"
enable_python="${enable_python:=OFF}"
enable_openmp="${enable_openmp:=OFF}"
enable_mpi="${enable_mpi:=OFF}"
enable_mpicc="${enable_mpicc:=OFF}"
enable_find_mpi="${enable_find_mpi:=ON}"
enable_tests="${enable_tests:=OFF}"
enable_verbose="${enable_verbose:=ON}"
build_jobs="${build_jobs:=6}"
build_config="${build_config:=Release}"
build_shared_libs="${build_shared_libs:=ON}"

# tpl controls
build_zlib="${build_zlib:=true}"
build_hdf5="${build_hdf5:=true}"
build_pyvenv="${build_pyvenv:=false}"
build_caliper="${build_caliper:=false}"
build_silo="${build_silo:=true}"
build_zfp="${build_zfp:=true}"

# conduit options
build_conduit="${build_conduit:=true}"

# see if we are building on windows
build_windows="${build_windows:=OFF}"

# see if we are building on macOS
build_macos="${build_macos:=OFF}"

case "$OSTYPE" in
  win*)     build_windows="ON";;
  msys*)    build_windows="ON";;
  darwin*)  build_macos="ON";;
  *)        ;;
esac

if [[ "$build_windows" == "ON" ]]; then
  echo "*** configuring for windows"
fi

if [[ "$build_macos" == "ON" ]]; then
  echo "*** configuring for macos"
fi

################
# path helpers
################
function ospath()
{
  if [[ "$build_windows" == "ON" ]]; then
    echo `cygpath -m $1`
  else
    echo $1
  fi 
}

function abs_path()
{
  if [[ "$build_macos" == "ON" ]]; then
    echo "$(cd $(dirname "$1");pwd)/$(basename "$1")"
  else
    echo `realpath $1`
  fi
}

root_dir=$(pwd)
root_dir="${prefix:=${root_dir}}"
root_dir=$(ospath ${root_dir})
root_dir=$(abs_path ${root_dir})
script_dir=$(abs_path "$(dirname "${BASH_SOURCE[0]}")")
build_dir=$(ospath ${root_dir}/build)
source_dir=$(ospath ${root_dir}/source)

# root_dir is where we will build and install
# override with `prefix` env var
if [ ! -d ${root_dir} ]; then
  mkdir -p ${root_dir}
fi

cd ${root_dir}

# install_dir is where we will install
# override with `prefix` env var
install_dir="${install_dir:=$root_dir/install}"

echo "*** prefix:       ${root_dir}" 
echo "*** build root:   ${build_dir}"
echo "*** sources root: ${source_dir}"
echo "*** install root: ${install_dir}"
echo "*** script dir:   ${script_dir}"

################
# tar options
################
tar_extra_args=""
if [[ "$build_windows" == "ON" ]]; then
  tar_extra_args="--force-local"
fi

# make sure sources dir exists
if [ ! -d ${source_dir} ]; then
  mkdir -p ${source_dir}
fi
################
# CMake Compiler Settings
################
cmake_compiler_settings=""

# capture compilers if they are provided via env vars
if [ ! -z ${CC+x} ]; then
  cmake_compiler_settings="-DCMAKE_C_COMPILER:PATH=${CC}"
fi

if [ ! -z ${CXX+x} ]; then
  cmake_compiler_settings="${cmake_compiler_settings} -DCMAKE_CXX_COMPILER:PATH=${CXX}"
fi

if [ ! -z ${FTN+x} ]; then
  cmake_compiler_settings="${cmake_compiler_settings} -DCMAKE_Fortran_COMPILER:PATH=${FTN}"
fi

############################
# mpi related vars
############################
mpicc_exe="${mpicc_exe:=mpicc}"
mpicxx_exe="${mpicxx_exe:=mpic++}"

################
# print all build_ZZZ and enable_ZZZ options
################
echo "*** cmake_compiler_settings: ${cmake_compiler_settings}"
echo "*** build_conduit `enable` settings:"
set | grep enable_
echo "*** build_conduit `build` settings:"
set | grep build_

################
# Zlib
################
zlib_version=1.3.1
zlib_src_dir=$(ospath ${source_dir}/zlib-${zlib_version})
zlib_build_dir=$(ospath ${build_dir}/zlib-${zlib_version}/)
zlib_install_dir=$(ospath ${install_dir}/zlib-${zlib_version}/)
zlib_tarball=$(ospath ${source_dir}/zlib-${zlib_version}.tar.gz)

# build only if install doesn't exist
if [ ! -d ${zlib_install_dir} ]; then
if ${build_zlib}; then
if [ ! -d ${zlib_src_dir} ]; then
  echo "**** Downloading ${zlib_tarball}"
  curl -L https://github.com/madler/zlib/releases/download/v${zlib_version}/zlib-${zlib_version}.tar.gz -o ${zlib_tarball}
  tar  ${tar_extra_args} -xzf ${zlib_tarball} -C ${source_dir}
fi

echo "**** Configuring Zlib ${zlib_version}"
cmake -S ${zlib_src_dir} -B ${zlib_build_dir} ${cmake_compiler_settings} \
  -DCMAKE_VERBOSE_MAKEFILE:BOOL=${enable_verbose} \
  -DCMAKE_BUILD_TYPE=${build_config} \
  -DCMAKE_INSTALL_PREFIX=${zlib_install_dir}

echo "**** Building Zlib ${zlib_version}"
cmake --build ${zlib_build_dir} --config ${build_config} -j${build_jobs}
echo "**** Installing Zlib ${zlib_version}"
cmake --install ${zlib_build_dir} --config ${build_config}

fi
else
  echo "**** Skipping Zlib build, install found at: ${zlib_install_dir}"
fi # build_zlib


################
# HDF5
################
# release 1-2 GAH!
hdf5_version=1.14.1-2
hdf5_middle_version=1.14.1
hdf5_short_version=1.14
hdf5_src_dir=$(ospath ${source_dir}/hdf5-${hdf5_version})
hdf5_build_dir=$(ospath ${build_dir}/hdf5-${hdf5_version}/)
hdf5_install_dir=$(ospath ${install_dir}/hdf5-${hdf5_version}/)
hdf5_tarball=$(ospath ${source_dir}/hdf5-${hdf5_version}.tar.gz)

# build only if install doesn't exist
if [ ! -d ${hdf5_install_dir} ]; then
if ${build_hdf5}; then
if [ ! -d ${hdf5_src_dir} ]; then
  echo "**** Downloading ${hdf5_tarball}"
  curl -L https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-${hdf5_short_version}/hdf5-${hdf5_middle_version}/src/hdf5-${hdf5_version}.tar.gz -o ${hdf5_tarball}
  tar ${tar_extra_args} -xzf ${hdf5_tarball} -C ${source_dir}
fi

#################
#
# hdf5 1.14.x CMake recipe for using zlib
#
# -DHDF5_ENABLE_Z_LIB_SUPPORT=ON
# Add zlib install dir to CMAKE_PREFIX_PATH
#
#################

echo "**** Configuring HDF5 ${hdf5_version}"
cmake -S ${hdf5_src_dir} -B ${hdf5_build_dir} ${cmake_compiler_settings} \
  -DCMAKE_VERBOSE_MAKEFILE:BOOL=${enable_verbose} \
  -DCMAKE_BUILD_TYPE=${build_config} \
  -DHDF5_ENABLE_Z_LIB_SUPPORT=ON \
  -DCMAKE_PREFIX_PATH=${zlib_install_dir} \
  -DCMAKE_INSTALL_PREFIX=${hdf5_install_dir}

echo "**** Building HDF5 ${hdf5_version}"
cmake --build ${hdf5_build_dir} --config ${build_config} -j${build_jobs}
echo "**** Installing HDF5 ${hdf5_version}"
cmake --install ${hdf5_build_dir} --config ${build_config}

fi
else
  echo "**** Skipping HDF5 build, install found at: ${hdf5_install_dir}"
fi # build_hdf5


################
# Silo
################
silo_version=4.11.1
silo_src_dir=$(ospath ${source_dir}/Silo-${silo_version})
silo_build_dir=$(ospath ${build_dir}/silo-${silo_version}/)
silo_install_dir=$(ospath ${install_dir}/silo-${silo_version}/)
silo_tarball=$(ospath ${source_dir}/silo-${silo_version}.tar.gz)

# build only if install doesn't exist
if [ ! -d ${silo_install_dir} ]; then
if ${build_silo}; then
if [ ! -d ${silo_src_dir} ]; then
  echo "**** Downloading ${silo_tarball}"
  curl -L https://github.com/LLNL/Silo/archive/refs/tags/${silo_version}.tar.gz -o ${silo_tarball}
  # untar and avoid symlinks (which windows despises)
  tar ${tar_extra_args} -xzf ${silo_tarball} -C ${source_dir} \
      --exclude="Silo-${silo_version}/config-site/*" \
      --exclude="Silo-${silo_version}/README.md"
  # apply silo patches
  cd  ${silo_src_dir}
  patch -p1 < ${script_dir}/2024_07_25_silo_4_11_cmake_fix.patch

  # windows specifc patch
  if [[ "$build_windows" == "ON" ]]; then
    patch -p1 < ${script_dir}/2024_07_29_silo-pr389-win32-bugfix.patch
  fi

  cd ${root_dir}
fi


echo "**** Configuring Silo ${silo_version}"
cmake -S ${silo_src_dir} -B ${silo_build_dir} ${cmake_compiler_settings} \
  -DCMAKE_VERBOSE_MAKEFILE:BOOL=${enable_verbose} \
  -DCMAKE_BUILD_TYPE=${build_config} \
  -DCMAKE_INSTALL_PREFIX=${silo_install_dir} \
  -DSILO_ENABLE_SHARED=${build_shared_libs} \
  -DCMAKE_C_FLAGS=-Doff64_t=off_t \
  -DSILO_ENABLE_HDF5=ON \
  -DSILO_ENABLE_TESTS=OFF \
  -DSILO_BUILD_FOR_BSD_LICENSE=ON \
  -DSILO_ENABLE_FORTRAN=OFF \
  -DSILO_HDF5_DIR=${hdf5_install_dir}/cmake/ \
  -DCMAKE_PREFIX_PATH=${zlib_install_dir}


echo "**** Building Silo ${silo_version}"
cmake --build ${silo_build_dir} --config ${build_config} -j${build_jobs}
echo "**** Installing Silo ${silo_version}"
cmake --install ${silo_build_dir} --config ${build_config}

fi
else
  echo "**** Skipping Silo build, install found at: ${silo_install_dir}"
fi # build_silo

############################
# Python Virtual Env
############################
python_exe="${python_exe:=python3}"
venv_install_dir=$(ospath ${install_dir}/python-venv/)
venv_python_exe=$(ospath ${venv_install_dir}/bin/python3)
venv_sphinx_exe=$(ospath ${venv_install_dir}/bin/sphinx-build)

# build only if install doesn't exist
if [ ! -d ${venv_install_dir} ]; then
if ${build_pyvenv}; then
    echo "**** Creating Python Virtual Env"
    cd ${install_dir} && ${python_exe} -m venv python-venv
    ${venv_python_exe} -m pip install --upgrade pip
    ${venv_python_exe} -m pip install numpy sphinx sphinx_rtd_theme
    if ${build_zfp}; then
        ${venv_python_exe} -m pip install cython setuptools
    fi
    if [[ "$enable_mpi" == "ON" ]]; then
        ${venv_python_exe} -m pip install mpi4py
    fi
fi
else
  echo "**** Skipping Python venv build, install found at: ${venv_install_dir}"
fi # build_pyvenv

if ${build_pyvenv}; then
    venv_python_ver=`${venv_python_exe} -c "import sys;print('{0}.{1}'.format(sys.version_info.major, sys.version_info.minor))"`
    venv_python_site_pkgs_dir=${venv_install_dir}/lib/python${venv_python_ver}/site-packages
fi

################
# Caliper
################
caliper_version=2.11.0
caliper_src_dir=$(ospath ${source_dir}/Caliper-${caliper_version})
caliper_build_dir=$(ospath ${build_dir}/caliper-${caliper_version}/)
caliper_install_dir=$(ospath ${install_dir}/caliper-${caliper_version}/)
caliper_tarball=$(ospath ${source_dir}/caliper-${caliper_version}-src-with-blt.tar.gz)

# build only if install doesn't exist
if [ ! -d ${caliper_install_dir} ]; then
if ${build_caliper}; then
if [ ! -d ${caliper_src_dir} ]; then
  echo "**** Downloading ${caliper_tarball}"
  curl -L https://github.com/LLNL/Caliper/archive/refs/tags/v${caliper_version}.tar.gz -o ${caliper_tarball}
  tar ${tar_extra_args} -xzf ${caliper_tarball} -C ${source_dir}
  # windows specifc patch
  cd  ${caliper_src_dir}
  if [[ "$build_windows" == "ON" ]]; then
    patch -p1 < ${script_dir}/2024_08_01_caliper-win-smaller-opts.patch
  fi
  cd ${root_dir}
fi

#
# Note: Caliper has optional Umpire support,
# if we want to support in the future, we will need to build umpire first
#

# -DWITH_CUPTI=ON -DWITH_NVTX=ON -DCUDA_TOOLKIT_ROOT_DIR={path} -DCUPTI_PREFIX={path}
# -DWITH_ROCTRACER=ON -DWITH_ROCTX=ON -DROCM_PREFIX={path}

caliper_windows_cmake_flags="-DCMAKE_CXX_STANDARD=17 -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=ON -DWITH_TOOLS=OFF"

caliper_extra_cmake_args=""
if [[ "$build_windows" == "ON" ]]; then
  caliper_extra_cmake_args="${caliper_windows_cmake_flags}"
fi

# TODO enable_cuda
#
# if [[ "$enable_hip" == "ON" ]]; then
#   caliper_extra_cmake_args="${caliper_extra_cmake_args} -DWITH_ROCTRACER=ON"
#   caliper_extra_cmake_args="${caliper_extra_cmake_args} -DWITH_ROCTX=ON"
#   caliper_extra_cmake_args="${caliper_extra_cmake_args} -DROCM_PREFIX:PATH=${ROCM_PATH}"
#   caliper_extra_cmake_args="${caliper_extra_cmake_args} -DROCM_ROOT_DIR:PATH=${ROCM_PATH}"
# fi

if [[ "$enable_mpicc" == "ON" ]]; then
  caliper_extra_cmake_args="${caliper_extra_cmake_args} -DMPI_C_COMPILER=${mpicc_exe}"
  caliper_extra_cmake_args="${caliper_extra_cmake_args} -DMPI_CXX_COMPILER=${mpicxx_exe}"
fi


echo "**** Configuring Caliper ${caliper_version}"
cmake -S ${caliper_src_dir} -B ${caliper_build_dir} ${cmake_compiler_settings} \
  -DCMAKE_VERBOSE_MAKEFILE:BOOL=${enable_verbose} \
  -DCMAKE_BUILD_TYPE=${build_config} \
  -DBUILD_SHARED_LIBS=${build_shared_libs} \
  -DCMAKE_INSTALL_PREFIX=${caliper_install_dir} \
  -DWITH_MPI=${enable_mpi} ${caliper_extra_cmake_args}

echo "**** Building Caliper ${caliper_version}"
cmake --build ${caliper_build_dir} --config ${build_config} -j${build_jobs}
echo "**** Installing Caliper ${caliper_version}"
cmake --install ${caliper_build_dir} --config ${build_config}

fi
else
  echo "**** Skipping Caliper build, install found at: ${caliper_install_dir}"
fi # build_caliper


################
# ZFP
################
zfp_version=1.0.1
zfp_src_dir=$(ospath ${source_dir}/zfp-${zfp_version})
zfp_build_dir=$(ospath ${build_dir}/zfp-${zfp_version}/)
zfp_install_dir=$(ospath ${install_dir}/zfp-${zfp_version}/)
zfp_tarball=$(ospath ${source_dir}/zfp-${zfp_version}.tar.gz)

# build only if install doesn't exist
if [ ! -d ${zfp_install_dir} ]; then
if ${build_zfp}; then
if [ ! -d ${zfp_src_dir} ]; then
  echo "**** Downloading ${zfp_tarball}"
  curl -L https://github.com/LLNL/zfp/releases/download/${zfp_version}/zfp-${zfp_version}.tar.gz -o ${zfp_tarball}
  tar ${tar_extra_args} -xzf ${zfp_tarball} -C ${source_dir}

  # apply patches
  cd ${zfp_src_dir}
  patch -p1 < ${script_dir}/2025_02_14_zfp_python_build_hardening.patch
  cd ${root_dir}
fi

#
# extra cmake args
#
zfp_extra_cmake_opts="-DBUILD_ZFPY=${enable_python}"
if ${build_pyvenv}; then
  zfp_extra_cmake_opts="${zfp_extra_cmake_opts} -DPYTHON_EXECUTABLE=${venv_python_exe}"
  zfp_extra_cmake_opts="${zfp_extra_cmake_opts} -Dpython_install_lib_dir=${venv_python_site_pkgs_dir}"
fi

echo "**** Configuring ZFP ${zfp_version}"
cmake -S ${zfp_src_dir} -B ${zfp_build_dir} ${cmake_compiler_settings} \
  -DCMAKE_VERBOSE_MAKEFILE:BOOL=${enable_verbose} \
  -DCMAKE_BUILD_TYPE=${build_config} \
  -DBUILD_SHARED_LIBS=${build_shared_libs} \
  -DCMAKE_INSTALL_PREFIX=${zfp_install_dir} ${zfp_extra_cmake_opts}

echo "**** Building ZFP ${zfp_version}"
cmake --build ${zfp_build_dir} --config ${build_config} -j${build_jobs}
echo "**** Installing ZFP ${zfp_version}"
cmake --install ${zfp_build_dir} --config ${build_config}

fi
else
  echo "**** Skipping ZFP build, install found at: ${zfp_install_dir}"
fi # build_zfp


################
# H5Z-ZFP
################
h5zzfp_version=1.1.1
h5zzfp_src_dir=$(ospath ${source_dir}/H5Z-ZFP-${h5zzfp_version})
h5zzfp_build_dir=$(ospath ${build_dir}/h5zzfp-${h5zzfp_version}/)
h5zzfp_install_dir=$(ospath ${install_dir}/h5zzfp-${h5zzfp_version}/)
h5zzfp_tarball=$(ospath ${source_dir}/h5zzfp-${h5zzfp_version}.tar.gz)

# build only if install doesn't exist
if [ ! -d ${h5zzfp_install_dir} ]; then
# also enabled via `build_zfp` instead of sep option
if ${build_zfp}; then
if [ ! -d ${h5zzfp_src_dir} ]; then
  echo "**** Downloading ${h5zzfp_tarball}"
  curl -L "https://github.com/LLNL/H5Z-ZFP/archive/refs/tags/v${h5zzfp_version}.tar.gz"  -o ${h5zzfp_tarball}
  tar ${tar_extra_args} -xzf ${h5zzfp_tarball} -C ${source_dir}
fi

echo "**** Configuring H5Z-ZFP ${h5zzfp_version}"

HDF5_DIR=${hdf5_install_dir}  \
ZFP_DIR=${zfp_install_dir}/lib/cmake/zfp/ \
cmake -S ${h5zzfp_src_dir} -B ${h5zzfp_build_dir} ${cmake_compiler_settings} \
  -DCMAKE_VERBOSE_MAKEFILE:BOOL=${enable_verbose} \
  -DCMAKE_BUILD_TYPE=${build_config} \
  -DBUILD_SHARED_LIBS=${build_shared_libs} \
  -DCMAKE_INSTALL_PREFIX=${h5zzfp_install_dir}

echo "**** Building H5Z-ZFP ${h5zzfp_version}"
cmake --build ${h5zzfp_build_dir} --config ${build_config} -j${build_jobs}
echo "**** Installing H5Z-ZFP ${h5zzfp_version}"
cmake --install ${h5zzfp_build_dir} --config ${build_config}

fi
else
  echo "**** Skipping H5Z-ZFP build, install found at: ${h5zzfp_install_dir}"
fi # build_h5zzfp


################
# Conduit
################
# if we are in an checkout, use existing source
conduit_checkout_dir=$(ospath ${script_dir}/../../src)
conduit_checkout_dir=$(abs_path ${conduit_checkout_dir})
echo ${conduit_checkout_dir}
if [ -d ${conduit_checkout_dir} ]; then
    conduit_version=checkout
    conduit_src_dir=$(abs_path ${conduit_checkout_dir})
    echo "**** Using existing Conduit source repo checkout: ${conduit_src_dir}"
else
    # otherwise use develop
    conduit_version=develop
    conduit_src_dir=$(ospath ${source_dir}/conduit/src)
fi

conduit_build_dir=$(ospath ${build_dir}/conduit-${conduit_version}/)
conduit_install_dir=$(ospath ${install_dir}//conduit-${conduit_version}/)

echo "**** Creating Conduit host-config (conduit-config.cmake)"
#
echo '# host-config file generated by build_conduit.sh' > ${root_dir}/conduit-config.cmake

# capture compilers if they are provided via env vars
if [ ! -z ${CC+x} ]; then
    echo 'set(CMAKE_C_COMPILER ' ${CC} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi

if [ ! -z ${CXX+x} ]; then
    echo 'set(CMAKE_CXX_COMPILER ' ${CXX} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi

if [ ! -z ${FTN+x} ]; then
    echo 'set(CMAKE_Fortran_COMPILER ' ${FTN} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi

# capture compiler flags  if they are provided via env vars
if [ ! -z ${CFLAGS+x} ]; then
    echo 'set(CMAKE_C_FLAGS "' ${CFLAGS} '" CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi

if [ ! -z ${CXXFLAGS+x} ]; then
    echo 'set(CMAKE_CXX_FLAGS "' ${CXXFLAGS} '" CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi

if [ ! -z ${FFLAGS+x} ]; then
    echo 'set(CMAKE_F_FLAGS "' ${FFLAGS} '" CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi

if [[ "$enable_mpicc" == "ON" ]]; then
  echo 'set(MPI_C_COMPILER '  ${mpicc_exe}  ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
  echo 'set(MPI_CXX_COMPILER ' ${mpicxx_exe}  ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi

echo 'set(CMAKE_VERBOSE_MAKEFILE ' ${enable_verbose} ' CACHE BOOL "")' >> ${root_dir}/conduit-config.cmake
echo 'set(CMAKE_BUILD_TYPE ' ${build_config} ' CACHE STRING "")' >> ${root_dir}/conduit-config.cmake
echo 'set(BUILD_SHARED_LIBS ' ${build_shared_libs} ' CACHE STRING "")' >> ${root_dir}/conduit-config.cmake
echo 'set(CMAKE_INSTALL_PREFIX ' ${conduit_install_dir} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
echo 'set(ENABLE_TESTS ' ${enable_tests} ' CACHE BOOL "")' >> ${root_dir}/conduit-config.cmake
echo 'set(ENABLE_MPI ' ${enable_mpi} ' CACHE BOOL "")' >> ${root_dir}/conduit-config.cmake
echo 'set(ENABLE_FIND_MPI ' ${enable_find_mpi} ' CACHE BOOL "")' >> ${root_dir}/conduit-config.cmake
echo 'set(ENABLE_FORTRAN ' ${enable_fortran} ' CACHE BOOL "")' >> ${root_dir}/conduit-config.cmake
echo 'set(ENABLE_PYTHON ' ${enable_python} ' CACHE BOOL "")' >> ${root_dir}/conduit-config.cmake
if ${build_pyvenv}; then
echo 'set(PYTHON_EXECUTABLE ' ${venv_python_exe} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
echo 'set(PYTHON_MODULE_INSTALL_PREFIX ' ${venv_python_site_pkgs_dir} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
echo 'set(ENABLE_DOCS ON CACHE BOOL "")' >> ${root_dir}/conduit-config.cmake
echo 'set(SPHINX_EXECUTABLE ' ${venv_sphinx_exe} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi
if ${build_caliper}; then
  echo 'set(CALIPER_DIR ' ${caliper_install_dir} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi
echo 'set(HDF5_DIR ' ${hdf5_install_dir} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
echo 'set(ZLIB_DIR ' ${zlib_install_dir} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
if ${build_zfp}; then
  echo 'set(ZFP_DIR ' ${zfp_install_dir} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
  echo 'set(H5ZZFP_DIR ' ${h5zzfp_install_dir} ' CACHE PATH "")' >> ${root_dir}/conduit-config.cmake
fi

# build only if install doesn't exist
if [ ! -d ${conduit_install_dir} ]; then
if ${build_conduit}; then
if [ ! -d ${conduit_src_dir} ]; then
    echo "**** Cloning Conduit"
    git clone --recursive https://github.com/LLNL/conduit.git
fi

echo "**** Configuring Conduit"
cmake -S ${conduit_src_dir} -B ${conduit_build_dir} -C ${root_dir}/conduit-config.cmake

echo "**** Building Conduit"
cmake --build ${conduit_build_dir} --config ${build_config} -j${build_jobs}

echo "**** Installing Conduit"
cmake --install ${conduit_build_dir}  --config ${build_config}

fi
else
  echo "**** Skipping Conduit build, install found at: ${conduit_install_dir}"
fi # build_conduit
