#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.h"
#include <iostream>
#include <string>
#include <chrono>

class draw_node : public rclcpp::Node
{

private:
    int count_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub;
    geometry_msgs::msg::Twist msg;

    void circle_draw(){

        //anda 2 para frente
        msg.linear.x = 2;
        //roda em torno do eixo z
        msg.angular.z = 1;
        
        RCLCPP_INFO(this->get_logger(), "Publishing: Position (%.2f, %.2f, %.2f)", msg.linear.x, msg.linear.y, msg.linear.z);

        //publicando mensagem do node
        cmd_vel_pub->publish(msg);
    }



    void timer_callback(){
        this->count_++;
        RCLCPP_INFO(this->get_logger(), "Hello, World %d", this->count_);
    }

public:
    draw_node() : Node("circle_draw"){
        RCLCPP_INFO(this->get_logger(), "Draw node started");

        //criando topic de nome turtle1/cmd_vel com tamanho 10 de buffer
        this->cmd_vel_pub = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);

        //chama a função circle_draw a cada 0.1 segundos
        timer_ = create_wall_timer(std::chrono::milliseconds(100), std::bind(&draw_node::circle_draw, this));
    }
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);

    auto node = std::make_shared<draw_node>();
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}