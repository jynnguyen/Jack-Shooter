cmake_minimum_required(VERSION 3.10)
project(SFML_Project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Chỉ định thư mục chứa file cấu hình CMake của SFML
set(SFML_DIR "C:/SFML_mingw64/SFML-3.0.0/lib/cmake/SFML")

# Gọi đúng phiên bản SFML 3 và module viết hoa
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio Network)

# Lấy tất cả file .cpp trong src/
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Tạo executable
add_executable(.main ${SRC_FILES})

# Include thư viện (nếu bạn có thư mục include riêng)
target_include_directories(.main
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    "C:/SFML_mingw64/SFML-3.0.0/include"
)

# Liên kết thư viện SFML
target_link_libraries(.main
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    SFML::Network
)
