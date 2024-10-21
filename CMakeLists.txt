# Мінімальна версія CMake
cmake_minimum_required(VERSION 3.10)

# Назва проекту
project(ClientServerProject)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Вказуємо директорію з заголовочними файлами
include_directories(${CMAKE_SOURCE_DIR}/client/include)

# Додаємо виконуваний файл для клієнта
add_executable(client
    ${CMAKE_SOURCE_DIR}/client/src/client.cpp
    ${CMAKE_SOURCE_DIR}/client/src/communication.cpp
)

# Додаємо команду для завантаження коду на Arduino
add_custom_target(upload_server
    COMMAND arduino-cli upload -p COM3 --fqbn arduino:avr:nano ${CMAKE_SOURCE_DIR}/server/server.ino
    COMMENT "Uploading server code to Arduino"
)
