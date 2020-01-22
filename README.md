# Alpha version of Linux Leap Motion driver for Godot

For a quick build, just download build.sh, get a copy of the leap SDK 2.3.1 for linux and follow the instructions in the shell script. It will automatically build the driver for you.

Based on the idea from gdleapmotion, however this uses an older Leap motion SDK as the Leapc api is only available for windows at the moment.
https://github.com/BastiaanOlij/gdleapmotion

Requires: Leap_Motion_SDK_Linux_2.3.1.tgz from Leap Motion site

Requires godot-cpp from: https://github.com/GodotNativeTools/godot-cpp/tree/499300ea6a4625020b2d535dfcd0751cd7119834
(the above version)

and godot-headers from: https://github.com/GodotNativeTools/godot_headers/tree/2d221de20c7ddc297b8bb14f0dbd55c053eb3024

in the root directory:

symlink leap to LeapDeveloperKit_2.3.1+31549_linux/LeapSDK

symlink godot-cpp to godot-cpp-499300ea6a4625020b2d535dfcd0751cd7119834 (this will have to be compiled)

symlink godot_headers to godot_headers-2d221de20c7ddc297b8bb14f0dbd55c053eb3024

weirdly the dependencies path in gdexample.gdnlib does not work so libLeap.so from the sdk must be copied into /usr/lib or in a path in your LD_LIBRARY_PATH

The skeleton is taken straight from the gdnative c++ example:
https://godot.readthedocs.io/en/latest/tutorials/plugins/gdnative/gdnative-cpp-example.html

The leap motion code is taken from Sample.cpp in the SDK samples directory.


