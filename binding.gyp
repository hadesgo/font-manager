{
    "targets": [
        {
            "target_name": "fontmanager",
            "sources": ["src/FontManager.cc"],
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "MACOSX_DEPLOYMENT_TARGET": "10.7",
            },
            "msvs_settings": {
                "VCCLCompilerTool": {"ExceptionHandling": 1},
            },
            "conditions": [
                [
                    'OS=="mac"',
                    {
                        "sources": ["src/FontManagerMac.mm"],
                        "link_settings": {
                            "libraries": ["CoreText.framework", "Foundation.framework"]
                        },
                    },
                ],
                [
                    'OS=="win"',
                    {
                        "sources": ["src/FontManagerWindows.cc"],
                        "link_settings": {"libraries": ["Dwrite.lib"]},
                    },
                ],
                [
                    'OS=="linux"',
                    {
                        "sources": ["src/FontManagerLinux.cc"],
                        "link_settings": {"libraries": ["-lfontconfig"]},
                    },
                ],
            ],
        },
    ]
}
