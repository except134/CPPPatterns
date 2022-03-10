COMPUTER_NAME       = os.getenv("COMPUTERNAME") 
LOCATION_DIR        = "Build/" ..  COMPUTER_NAME .. "/" .. _ACTION

solution ("Lesson1")
    	location(LOCATION_DIR)
    	configurations { "Release", "Debug" }
    	platforms { "x64" }
    	architecture "x64"
    	cppdialect("C++latest")
    	language "C++"
    	system "Windows"
    	systemversion("latest")
    	startproject("Lesson1")
        staticruntime "On"
        buildoptions { "/Zm512 /bigobj" }

    	defines { 
	}

        includedirs { 
	}

        libdirs { 
	}

    	filter "configurations:Debug"
        	optimize "Off"
        	symbols "On"
        	inlining "Disabled"
        	flags { "MultiProcessorCompile" }
        	defines { "_DEBUG" }

    	filter "configurations:Release"
        	optimize "Full"
        	symbols "Off"
        	inlining "Auto"
        	flags { "MultiProcessorCompile", "LinkTimeOptimization" }
        	defines { "NDEBUG" }

project "Game"
    	targetdir "Bin"
    	debugdir "$(TargetDir)"
    	targetname "$(ProjectName)$(PlatformArchitecture)$(Configuration)"
    	kind "ConsoleApp"
    	pchheader("LessonPCH.h") 
    	pchsource("Src/LessonPCH.cpp") 
    	
	links {  
	}

    	files { 
        	"Src/LessonPCH.cpp",
        	"Src/LessonPCH.h",
        	"Src/ExtLibs.cpp",
        	"Src/**.h", 
        	"Src/**.cpp", 
    	}
