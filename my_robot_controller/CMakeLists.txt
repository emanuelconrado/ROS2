cmake_minimum_required(VERSION 3.8)

#pasta do node
project(my_robot_controller)

# Encontrar dependências do ROS 2
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Adicionar o executável

#pasta do node e caminho do arquivo cpp
add_executable(my_robot_controller src/my_cpp_node.cpp)

# Linkar as bibliotecas

#pasta do node e RCLCPP
ament_target_dependencies(my_robot_controller rclcpp)

# Instalar o executável
install(TARGETS

  #pasta do node
  my_robot_controller
  DESTINATION lib/${PROJECT_NAME})

# Definir as dependências
ament_package()

