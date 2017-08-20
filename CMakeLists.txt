cmake_minimum_required(VERSION 2.8)

Project(ServerApp)


add_definitions(-DASIO_STANDALONE)
add_definitions(-D_WIN32_WINNT=0x0A00)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/Launcher LAUNCHER_SOURCE_FILE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/EchoService ECHO_SERVICE_SOURCE_FILE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/Timer TIMER_SOURCE_FILE)

set(SOURCE_FILE ${LAUNCHER_SOURCE_FILE} ${ECHO_SERVICE_SOURCE_FILE} ${TIMER_SOURCE_FILE})

add_executable(TestASIO ${SOURCE_FILE})


SOURCE_GROUP("src\\Launcher" FILES ${LAUNCHER_SOURCE_FILE})
SOURCE_GROUP("src\\EchoService" FILES ${ECHO_SERVICE_SOURCE_FILE})
SOURCE_GROUP("src\\Timer" FILES ${TIMER_SOURCE_FILE})

