-- premake5.lua
workspace "cutils"
    configurations { "Debug", "Release" }

project "cutils"
    kind "ConsoleApp"
    toolset "clang"
    language "C"
    cdialect "c11"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"

    files { 
        "*.h", 
        "test_hash.c",
        "thirdparty/fnv/src/*.c"  
    }

    links{"check"}

    filter "system:windows"
        includedirs{
            "include",
            "C:/Program Files (x86)/Check/include",
            "thirdparty/fnv"  
        }
        libdirs{
            "C:/Program Files (x86)/Check/lib"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
