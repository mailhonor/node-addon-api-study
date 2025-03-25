{
  "targets": [
    {
      "target_name": "hello",
      # -fno-exceptions 忽略掉编译过程中的一些报错
      "cflags!": [ "-fno-exceptions" ],
      # 下面这句话, 支持源码是 UTF-8 字符集
      "cflags_cc!": ["-fno-exceptions", "-finput-charset=UTF-8", '-std=c++11'],
      "sources": [ "hello.cc" ],
      "include_dirs": [ # 头文件搜索路径
        "<!@(node -p \"require('node-addon-api').include\")",
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      # 全局库
      'libraries': [
      ],
      "conditions": [
        [
          'OS == "linux"',
          {
            "include_dirs": [
              "<!@(node -p \"require('node-addon-api').include\")",
              # "./src/",
            ],
            "libraries": [
            ],
          },
          'OS == "mac"',
          {
            "include_dirs": [
              # "./src/",
            ],
            "libraries": [
            ],
          },
          'OS == "win"',
          {
            "include_dirs": [
              # "./src/",
            ],
            "libraries": [
            ],
            'msvs_settings': {
              'VCCLCompilerTool': {
                'runtimeLibrary': 0,
              },
              "VCCLCompilerTool": {
                "AdditionalOptions": [
                  "/utf-8"
                ]
              },
            }
          }
        ]
      ]
    }
  ]
}