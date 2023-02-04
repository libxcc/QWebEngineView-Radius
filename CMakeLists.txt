# CMake最低版本号要求
cmake_minimum_required(VERSION 3.20)


# 项目名称
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_CXX_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
project(QWebEngineView-Radius VERSION ${PROJECT_CXX_VERSION})


# 输出提示信息
message(STATUS "Operation System : ${CMAKE_SYSTEM}")
message(STATUS "CMAKE_INSTALL_PREFIX : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_C_COMPILER : ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER : ${CMAKE_CXX_COMPILER}")


# 配置文件
configure_file("${CMAKE_SOURCE_DIR}/config/VersionInfo.rc.in" "${CMAKE_BINARY_DIR}/VersionInfo.rc")


# 设置模块搜索路径
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_INSTALL_PREFIX}/lib/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{CXX_QT_DIR}/lib/cmake)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_MODULE_PATH})
set(Qt5Core_DIR $ENV{CXX_QT_DIR}/lib/cmake/Qt5Core)
set(Qt5Gui_DIR $ENV{CXX_QT_DIR}/lib/cmake/Qt5Gui)
set(Qt5Widgets_DIR $ENV{CXX_QT_DIR}/lib/cmake/Qt5Widgets)

message(STATUS "CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_PREFIX_PATH : ${CMAKE_PREFIX_PATH}")


# 设置编译环境
if (MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd /Od")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /Od")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG : ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE : ${CMAKE_CXX_FLAGS_RELEASE}")


# 添加资源文件
set(QRC_SOURCE_FILES resources/XWindowApplication.qrc)
set(WRC_SOURCE_FILES resources/XWindowApplication.rc)


# 设置忽略路径
set(CMAKE_IGNORE_PATH ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
message(STATUS "CMAKE_IGNORE_PATH : ${CMAKE_IGNORE_PATH}")


# 项目依赖
include_directories(${PROJECT_SOURCE_DIR}/include)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5WebChannel REQUIRED)
find_package(Qt5WebSockets REQUIRED)
find_package(Qt5WebEngine REQUIRED)
find_package(Qt5WebEngineCore REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)


# 设置自动生成QT文件
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# C++支持
set(CMAKE_CXX_STANDARD 17)


# 设置宏
add_definitions(-D_CRT_SECURE_NO_WARNINGS)


# 头文件搜索目录
include_directories(${PROJECT_SOURCE_DIR})


# 链接库搜索目录


# 包含源文件
aux_source_directory(./source SRC)
aux_source_directory(./source/window SRC)
if(MSVC)
	list(APPEND SRC ${CMAKE_BINARY_DIR}/VersionInfo.rc)
endif()


# 指定可执行程序输出目录
if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG $ENV{CXX_BINARY}/xcc/windows/debug)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE $ENV{CXX_BINARY}/xcc/windows/release)
elseif(APPLE)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG $ENV{CXX_BINARY}/xcc/darwin/debug)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE $ENV{CXX_BINARY}/xcc/darwin/release)
elseif(UNIX)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG $ENV{CXX_BINARY}/xcc/linux/debug)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE $ENV{CXX_BINARY}/xcc/linux/release)
endif()


# 链接库
if (WIN32)
	link_libraries("Ws2_32.lib")
	link_libraries("Wlanapi.lib")
	link_libraries("IPHLPAPI.lib")
	link_libraries("Dwmapi.lib")
	link_libraries("urlmon.lib")
	link_libraries("wininet.lib")
	link_libraries("Shlwapi.lib")
	link_libraries("Dbghelp.lib")
elseif (MINGW)
	link_libraries("Ws2_32")
	link_libraries("Wlanapi")
	link_libraries("IPHLPAPI")
	link_libraries("Dwmapi")
	link_libraries("urlmon")
	link_libraries("wininet")
	link_libraries("Shlwapi")
	link_libraries("Dbghelp")
else ()
	link_libraries("pthread")
	link_libraries("dl")
	link_libraries("rt")
endif ()
if (APPLE)
	link_libraries("objc")
endif ()
link_libraries(Qt5::Core)
link_libraries(Qt5::Gui)
link_libraries(Qt5::Widgets)
link_libraries(Qt5::WebEngineWidgets)


# 设置Mac RPATH
if (APPLE)
	set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
	set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
endif ()


# 设置 Windows 链接标志
message(STATUS "CMAKE_EXE_LINKER_FLAGS : ${CMAKE_EXE_LINKER_FLAGS}")
if (WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:\"mainCRTStartup\"")
	# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /TSAWARE")
endif ()
message(STATUS "CMAKE_EXE_LINKER_FLAGS : ${CMAKE_EXE_LINKER_FLAGS}")


# 构建
add_executable(${PROJECT_NAME} WIN32 ${SRC} ${QRC_SOURCE_FILES} ${WRC_SOURCE_FILES})


# 设置项目属性
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)


# 设置安装文件(可执行文件)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
