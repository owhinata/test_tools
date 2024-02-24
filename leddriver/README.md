```bash
rm -rf build && cmake -Bbuild -DWITH_EXAMPLES=OFF -DBUILD_SHARED_LIBS=OFF
cmake --build build && ctest --test-dir build/test/cmocka -V && valgrind --leak-check=full ctest --test-dir build/test/cmocka
```

```bash
lizard src include
================================================
  NLOC    CCN   token  PARAM  length  location  
------------------------------------------------
       3      2     20      1       3 is_led_out_of_bounds@19-21@src/driver.c
       3      1     17      1       3 convert_ledno_to_bit@23-25@src/driver.c
       3      1     14      1       3 set_led_image_bit@27-29@src/driver.c
       3      1     14      1       3 clear_led_image_bit@31-33@src/driver.c
       3      1     11      1       3 update_hardware@35-37@src/driver.c
       5      1     20      1       5 LedDriver_Create@39-43@src/driver.c
       2      1      6      1       2 LedDriver_Destroy@45-46@src/driver.c
       8      2     35      1       8 LedDriver_TurnOn@48-55@src/driver.c
       7      2     27      1       7 LedDriver_TurnOff@57-63@src/driver.c
       4      1     14      1       4 LedDriver_TurnAllOn@65-68@src/driver.c
       4      1     14      1       4 LedDriver_TurnAllOff@70-73@src/driver.c
       6      2     29      1       6 LedDriver_IsOn@75-80@src/driver.c
       3      1     14      1       3 LedDriver_IsOff@82-84@src/driver.c
3 file analyzed.
==============================================================
NLOC    Avg.NLOC  AvgCCN  Avg.token  function_cnt    file
--------------------------------------------------------------
     66       4.2     1.3       18.1        13     src/driver.c
     12       0.0     0.0        0.0         0     include/led/driver.h
      4       0.0     0.0        0.0         0     include/util/runtime_error.h

===============================================================================================================
No thresholds exceeded (cyclomatic_complexity > 15 or length > 1000 or nloc > 1000000 or parameter_count > 100)
==========================================================================================
Total nloc   Avg.NLOC  AvgCCN  Avg.token   Fun Cnt  Warning cnt   Fun Rt   nloc Rt
------------------------------------------------------------------------------------------
        82       4.2     1.3       18.1       13            0      0.00    0.00
```
