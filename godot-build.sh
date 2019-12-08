#!/bin/sh
echo download LeapMotionSDK for Linux version 2.3.1
echo from: https://developer.leapmotion.com/sdk/v2
echo It is expected to be extracted in the directory this script is run from.
echo 
echo You must also install the appropriate package, where in the sdk are two
echo .deb files with the driver, or read the README file to convert the packages
echo for your distribution.
echo
echo Once installed, when you plan to use godot run "leapd" as root with
echo the leap motion device attached.
echo 
echo -n Hit enter to continue:
read tmp
set -x
git clone https://github.com/cathoderaymission/godot-leapmotion-linux.git
cd godot-leapmotion-linux
wget https://github.com/GodotNativeTools/godot-cpp/archive/499300ea6a4625020b2d535dfcd0751cd7119834.zip
wget https://github.com/GodotNativeTools/godot_headers/archive/2d221de20c7ddc297b8bb14f0dbd55c053eb3024.zip
unzip 499300ea6a4625020b2d535dfcd0751cd7119834.zip
unzip 2d221de20c7ddc297b8bb14f0dbd55c053eb3024.zip
ln -s godot-cpp-499300ea6a4625020b2d535dfcd0751cd7119834/ godot-cpp
ln -s godot_headers-2d221de20c7ddc297b8bb14f0dbd55c053eb3024/ godot-headers
ln -s ../LeapDeveloperKit_2.3.1+31549_linux/LeapSDK/ leap
cd godot-cpp
rmdir godot_headers
ln -s ../godot_headers-2d221de20c7ddc297b8bb14f0dbd55c053eb3024/ godot_headers
scons platform=linux generate_bindings=yes
cd ..
mkdir demo
mkdir demo/bin
ln -s libgodot-cpp-499300ea6a4625020b2d535dfcd0751cd7119834.linux.64.a godot-cpp/bin/libgodot-cpp.linux.debug.64.a
scons platform=linux
