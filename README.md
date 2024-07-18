# CPP-WASM

前置依赖：Emscripten

```sh
cd build
emcmake cmake ../
emmake make
```

产出物在 dist 目录

- cpp 和 js bind 函数的类型必须都正确，否则会抛异常，没有明确信息
- 最佳实践，cpp 给 js 传 JSON，用 string，到了 js 解析下
- emcc cmd 更适合调试，调试没问题后，写到 cmake 配置，由 cmake 统一管理依赖和编译