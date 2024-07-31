# How to build
The following assumes that the build folder is placed inside the projects root tree. You can of course build it outside of the tree by adjusting the parameters accordingly. 

From within the project's root folder run the following commands:
```bash
mkdir build
cd build
cmake -G Ninja -DCMAKE_PREFIX_PATH=<path to your qt installation> -DBUILD_WITH_QT6:BOOL=ON -DCMAKE_BUILD_TYPE=Debug ..
```
Afterwards you can execute the built binary named `keychain-test` which is located inside the build folder.
