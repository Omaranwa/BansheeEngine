# Source files and their filters
include(CMakeSources.cmake)

# Includes
set(RenderBeast_INC 
	"Include"
	"../BansheeUtility/Include" 
	"../BansheeCore/Include"
	"../BansheeEngine/Include")

include_directories(${RenderBeast_INC})	
	
# Target
add_library(RenderBeast SHARED ${BS_RENDERBEAST_SRC})

# Defines
target_compile_definitions(RenderBeast PRIVATE -DBS_BSRND_EXPORTS)

# Libraries
## Local libs
target_link_libraries(RenderBeast BansheeEngine BansheeUtility BansheeCore)

# IDE specific
set_property(TARGET RenderBeast PROPERTY FOLDER Plugins)