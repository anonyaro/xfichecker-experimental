#xfichecker CMake project file.

cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("xfichecker")

set(CMAKE_CXX_STANDARD 17)
set	(CMAKE_CXX_STANDARD_REQUIRED ON)

set(XFICHECKER_INCLUDE_DIRS 
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/core"
	"${CMAKE_CURRENT_SOURCE_DIR}/cli"
	"${CMAKE_CURRENT_SOURCE_DIR}/modules"
	"${CMAKE_CURRENT_SOURCE_DIR}/CliUI"
)

set(XFICHECKER_LIBS 
"core/xfiler.cpp" 
"CliUI/cli.cpp"
)

add_library(xfichecker_libs STATIC ${XFICHECKER_LIBS})

target_include_directories(xfichecker_libs PUBLIC ${XFICHECKER_INCLUDE_DIRS})
target_compile_features(xfichecker_libs PUBLIC cxx_std_17)	

add_executable (xfichecker "xfichecker.cpp")

target_link_libraries(xfichecker PRIVATE xfichecker_libs)


