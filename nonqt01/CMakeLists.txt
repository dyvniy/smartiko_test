cmake_minimum_required(VERSION 3.5)

project(nonqt01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("../../paho.mqtt.cpp/src/")

# need link
# libpaho-mqttpp3.so & libpaho-mqtt3a.so
set(MQTT_CPP ../../build-paho.mqtt.cpp-Desktop-Debug/src/)
set(MQTT_C   ../../build-paho.mqtt.c-Desktop-Debug/src/)

set(paho-mqttpp3 ${MQTT_CPP}libpaho-mqttpp3.so)
set(paho-mqtt3a ${MQTT_C}/libpaho-mqtt3a.so)

add_library(pahottpp STATIC IMPORTED)
set_target_properties(pahottpp PROPERTIES IMPORTED_LOCATION ${paho-mqttpp3})

add_library(pahomqtt3a SHARED IMPORTED)
set_property(TARGET pahomqtt3a PROPERTY IMPORTED_LOCATION ${paho-mqtt3a})

add_executable(nonqt01 main.cpp paho_mqtt.h paho_mqtt.cpp
    mymqttpublisher.cpp mymqttpublisher.h
    dataemulator.cpp dataemulator.h
    jsonutils.cpp jsonutils.h
)

target_link_libraries(nonqt01 pahottpp)
target_link_libraries(nonqt01 pahomqtt3a)

install(TARGETS nonqt01
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
