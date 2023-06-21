workspace "ppm"
    configurations { "Debug", "Release" }

project "cppm"
    kind "StaticLib"
    language "c++"
    cppdialect "c++17"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"
    includedirs { "include", "src" }
    files { "src/**.cpp", "src/**.h" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

project "cppm-sandbox"
    kind "ConsoleApp"
    language "c++"
    cppdialect "c++17"
    targetdir "sandbox/bin/%{cfg.buildcfg}"
    objdir "sandbox/obj/%{cfg.buildcfg}"
    includedirs { "include" }
    files { "sandbox_src/**.cpp", "sandbox_src/**.h" }
    links { "cppm" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"