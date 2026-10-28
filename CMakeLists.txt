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

target_compile_definitions(TPAP4A PRIVATE
	LOG_DIRECTORY="${CMAKE_CURRENT_BINARY_DIR}"
)

#chaque fichier log est généré dans le répertoire de construction, mais on peut changer le répertoire de sortie en modifiant la variable LOG_DIRECTORY
