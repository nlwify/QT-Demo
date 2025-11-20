# 设置CMake最低版本要求[4,5](@ref)
cmake_minimum_required(VERSION 3.5)

# 设置项目名称和语言
project(qtdemo LANGUAGES CXX)

# 设置自动处理Qt的元对象系统[12](@ref)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 设置C++标准[8](@ref)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 根据您安装的Qt版本选择其一：

# 方案A: 如果您安装的是Qt6（推荐，因为您设置了6.10.0路径）
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/mingw_64")
find_package(Qt6 COMPONENTS Core Widgets Multimedia MultimediaWidgets REQUIRED)

# 方案B: 如果您安装的是Qt5
# set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw_64")  # 改为您实际的Qt5路径
# find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# 收集源文件[8](@ref)
aux_source_directory(./src srcs)

# 设置编译器编码选项（仅MSVC需要）[2](@ref)
if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# 创建可执行文件[1,7](@ref)
add_executable(${PROJECT_NAME}
    WIN32  # 注释掉这行如果需要在调试时显示终端
    ${srcs}
)

# 链接Qt库[12](@ref)
if(Qt6_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets Qt6::Widgets)
elseif(Qt5_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets)
endif()

# 添加包含目录（重要！）
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    # 添加其他包含目录
)

# 设置目标属性
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    WIN32_EXECUTABLE OFF
)


