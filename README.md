google test

git clone https://github.com/google/googletest.git -b v1.13.0
cd googletest        # Main directory of the cloned repository.
mkdir build          # Create a directory to hold the build output.
cd build
cmake ..             # Generate native build scripts for GoogleTest.
cmake .. -DBUILD_GMOCK=OFF #non mocks

cmake .  -Wno-dev
cmake --build .
ctest