#!/bin/bash -x

######################################
# Options
######################################

option_help() {
  echo -e "Usage: configure [OPTION]"
}

create_env() {
  if [[ ! -f "$BUILD_ABS/env.sh" ]]; then
    echo -e "creating script:$CB env.sh$CE"
    echo "export BUILD_ABS=\"$BUILD_ABS\"" >> $BUILD_ABS/env.sh
    echo "export HYPER_ABS=\"$HYPER_ABS\"" >> $BUILD_ABS/env.sh
    echo "export LLVM_RELEASE=\"release_39\"" >> $BUILD_ABS/env.sh
    #echo "export module_file=\"$module_file\"" >> $BUILD_ABS/env.sh
    echo "export compiler=\"$compiler\"" >> $BUILD_ABS/env.sh
    #echo "export CFLAGS=\"$CROSS_CCFLAGS\"" >> $BUILD_ABS/env.sh
    #echo "export CXXFLAGS=\"$CROSS_CXXFLAGS\"" >> $BUILD_ABS/env.sh
    #printf "export extensions=\"" >> $BUILD_ABS/env.sh
    #printf "%s;" "${extensions[@]}" >> $BUILD_ABS/env.sh
    #printf "\"\n" >> $BUILD_ABS/env.sh
  fi
}

copy_script() {
  local hyper_filename="$HYPER_ABS/tools/scripts/$1"
  local build_filename="$BUILD_ABS/build_scripts/$1"

  if [ "$hyper_filename" -nt "$build_filename" ]; then

      echo -e "generating script: $CB$1$CE"

      if [[ ! -d $BUILD_ABS/build_scripts/ ]]; then
          mkdir -p $BUILD_ABS/build_scripts/
      fi

      cp -p $hyper_filename $build_filename
      sed -i "s/%ENV_SOURCE%/source ${BUILD_ABS//\//\\/}\/env.sh/g" $build_filename
  fi
}

copy_scripts() {
  # copy_script "bareflank_gcc_wrapper.sh"
  # copy_script "filter_module_file.sh"
  # copy_script "build_newlib.sh"
  copy_script "build_libcxx.sh"
  # copy_script "build_libcxxabi.sh"
  # copy_script "build_libbfc.sh"
  # copy_script "build_driver.sh"
  # copy_script "load_driver.sh"
  # copy_script "clean_driver.sh"
  #copy_script "fetch_newlib.sh"
  copy_script "fetch_libcxx.sh"
  # copy_script "fetch_libcxxabi.sh"
  # copy_script "fetch_llvm.sh"
  # copy_script "fetch_libbfc.sh"
  # copy_script "verify_source.sh"
}

option_run() {
  if [[ -z "$HYPER_ABS" ]]; then
    HYPER_ABS=`pwd`
  fi
  if [[ -z "$BUILD_ABS" ]]; then
    BUILD_ABS="$HYPER_ABS/libs"
  fi
  create_env
  copy_scripts
}

while [[ $# -ne 0 ]]; do
  if [[ $1 == "-h" ]] || [[ $1 == "--help" ]]; then
    option_help
    exit 0
  fi

  if [[ $1 == "--compiler" ]]; then
    shift
    compiler=$1
  fi
  shift
done
option_run
