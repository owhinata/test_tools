rm -rf build && cmake -Bbuild -DWITH_EXAMPLES=OFF
cmake --build build && ctest --test-dir build/test/cmocka

