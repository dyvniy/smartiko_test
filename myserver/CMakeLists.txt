cmake_minimum_required(VERSION 3.10)

project(myserver)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

include_directories("../../paho.mqtt.cpp/src/")
set(MQTT_CPP ../../build-paho.mqtt.cpp-Desktop-Debug/src/)
set(MQTT_C   ../../build-paho.mqtt.c-Desktop-Debug/src/)

set(paho-mqttpp3 ${MQTT_CPP}libpaho-mqttpp3.so)
set(paho-mqtt3a ${MQTT_C}/libpaho-mqtt3a.so)

add_library(pahottpp STATIC IMPORTED)
set_target_properties(pahottpp PROPERTIES IMPORTED_LOCATION ${paho-mqttpp3})

add_library(pahomqtt3a SHARED IMPORTED)
set_property(TARGET pahomqtt3a PROPERTY IMPORTED_LOCATION ${paho-mqtt3a})

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(myserver main.cpp mymqttsubscriber.cpp mymqttsubscriber.h
    dbworker.cpp dbworker.h
    # ../nonqt01/jsonutils.cpp ../nonqt01/jsonutils.h
)

TARGET_LINK_LIBRARIES(myserver ${PQXX_LIB} ${PQ_LIB})
target_link_libraries(myserver pahottpp)
target_link_libraries(myserver pahomqtt3a)
