#!/bin/bash

# Abort script on any failures
set -e

# Define the number of simultaneous jobs to trigger for the different
# tasks that allow it. Use the number of available processors in the
# system.
export PARALLEL_JOBS=$(nproc)

if [[ -f /opt/ros/indigo/setup.bash ]] ; then
    source /opt/ros/indigo/setup.bash
else
    echo "ROS environment not found, please install it"
    exit 1
fi

my_loc="$(cd "$(dirname $0)" && pwd)"
source $my_loc/config.sh
source $my_loc/utils.sh

prefix=$(cd $1 && pwd)

run_cmd() {
    cmd=$1.sh
    shift
    $my_loc/$cmd $@ || die "$cmd $@ died with error code $?"
}

if [ -z $ANDROID_NDK ] ; then
    die "ANDROID_NDK ENVIRONMENT NOT FOUND!"
fi

if [ -z $ROS_DISTRO ] ; then
    die "HOST ROS ENVIRONMENT NOT FOUND! Did you source /opt/ros/indigo/setup.bash"
fi

[ -d $standalone_toolchain_path ] || run_cmd setup_standalone_toolchain

mkdir -p $prefix/libs

# Start with catkin since we use it to build almost everything else
[ -d $prefix/target ] || mkdir -p $prefix/target
export CMAKE_PREFIX_PATH=$prefix/target

# Get the android ndk build helper script
# If file doesn't exist, then download and patch it
if ! [ -e $prefix/android.toolchain.cmake ]; then
    cd $prefix
    download 'https://raw.githubusercontent.com/taka-no-me/android-cmake/556cc14296c226f753a3778d99d8b60778b7df4f/android.toolchain.cmake'
    patch -p0 -N -d $prefix < /opt/roscpp_android/patches/android.toolchain.cmake.patch
    cat $my_loc/files/android.toolchain.cmake.addendum >> $prefix/android.toolchain.cmake
fi

export RBA_TOOLCHAIN=$prefix/android.toolchain.cmake

echo
echo -e '\e[34mCross-compiling ROS.\e[39m'
echo

run_cmd build_cpp -p $prefix

echo
echo 'done.'
