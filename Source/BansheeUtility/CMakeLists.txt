# Source files and their filters
include(CMakeSources.cmake)

# Packages
find_package(Snappy REQUIRED)

# Includes
set(BansheeUtility_INC 
	"Include" 
	"Include/ThirdParty"
	${Snappy_INCLUDE_DIRS})

if(WIN32)
	set(BansheeUtility_INC ${BansheeUtility_INC} "Include/Win32")
else()
	# TODO_OTHER_PLATFORMS_GO_HERE
endif()

include_directories(${BansheeUtility_INC})	

# Target
add_library(BansheeUtility SHARED ${BS_BANSHEEUTILITY_SRC})

add_executable(BansheeUtilityTest Source/BsUtilityTest.cpp)
target_link_libraries(BansheeUtilityTest BansheeUtility)

# Defines
target_compile_definitions(BansheeUtility PRIVATE -DBS_UTILITY_EXPORTS)

# Libraries
## External lib: Snappy
target_link_libraries(BansheeUtility ${Snappy_LIBRARIES})	

## OS libs
if(WIN32)
target_link_libraries(BansheeUtility 
	DbgHelp
	IPHLPAPI
	Rpcrt4
	)
else()
	target_link_libraries(BansheeUtility dl)
endif()

# IDE specific
set_property(TARGET BansheeUtility PROPERTY FOLDER Layers)
