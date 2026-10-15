cmake_minimum_required(VERSION 3.15)
project(TPAP4A LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TPAP4A
	main.cpp
	server.cpp
	sensor.cpp
	scheduler.cpp
	temperatureSensor.cpp
	humiditySensor.cpp
	lightSensor.cpp
	soundSensor.cpp
)
