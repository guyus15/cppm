workspace "ppm"
    configurations { "Debug", "Release" }

project "ppm"
    kind "ConsoleAPp"
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