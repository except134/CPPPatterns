solution ("Lesson1")
	if not os.ishost("windows") then
		LOCATION_DIR        = "Build/" ..  os.outputof("uname -n") .. "/" .. _ACTION
    		staticruntime "Off"
    		system "linux"
	else
		LOCATION_DIR        = "Build/" ..  os.getenv("COMPUTERNAME") .. "/" .. _ACTION
    		staticruntime "On"
    		system "Windows"
    		buildoptions { "/Zm512 /bigobj" }
	end

    	location(LOCATION_DIR)
    	configurations { "Release", "Debug" }
    	architecture "x64"
    	cppdialect("C++latest")
    	language "C++"
    	systemversion("latest")
    	startproject("Lesson1")

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
    	kind "ConsoleApp"
	if not os.ishost("windows") then
   		pchheader("Src/LessonPCH.h") 
	else
   		pchheader("LessonPCH.h") 
	end
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

	if not os.ishost("windows") then
   		targetname "SBomberLX64"
		excludes { 
			"Src/Common/Input.*" 
		}	
	else
   		targetname "$(ProjectName)$(PlatformArchitecture)$(Configuration)"
	end
