cmake_minimum_required(VERSION 3.8)

#pasta do node
project(circle_draw)

# Encontrar dependências do ROS 2
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(turtlesim REQUIRED)

# Adicionar o executável

#pasta do node e caminho do arquivo cpp
add_executable(circle_draw src/circle_draw.cpp)

# Linkar as bibliotecas

#pasta do node e RCLCPP
ament_target_dependencies(circle_draw rclcpp geometry_msgs std_msgs turtlesim)

# Instalar o executável
install(TARGETS

  #pasta do node
  circle_draw
  DESTINATION lib/${PROJECT_NAME})

# Definir as dependências
ament_package()
