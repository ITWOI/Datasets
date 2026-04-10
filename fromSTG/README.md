# DefectCase from STG

## defect source
182 case from open-source project.
| Project Name | Version | LOC |
|--------------|---------|-----|
| bzip3 | 1.4.0 | 1,369 |
| libusb | 1.0.27 | 21,492 |
| libevent | 2.1.12 | 50,803 |
| libpng | libpng16 | 54,605 |
| libuv | 1.51.0 | 65,099 |
| jq | 1.8.1 | 112,615 |
| Redis | 8.2.2 | 192,124 |
|  cpython | 3.10.17 | 369,870 |



## generate method
Using STG tool. 
If you want the `compile_commands.json` file, you can use:
```shell
bear -- clang -c  *_end.c
```

## tips
defect_info.json中的`directory`是用例来源的绝对路径，仓库中使用path/xxxx替代，但不重要。
`executed_lines`是CSA给出的执行路径，仅供参考
`labels`留空，可参考`qwen3.5-122b-a10b_labels`字段。