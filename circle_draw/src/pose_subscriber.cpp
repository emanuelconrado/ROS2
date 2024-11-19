#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include <iostream>
#include <string>
#include <chrono>

class pose_node : public rclcpp::Node
{

private:
    int count_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr cmd_pos_sub;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub;
    geometry_msgs::msg::Twist msg;

    void pose_update(const turtlesim::msg::Pose::SharedPtr msg){
        RCLCPP_INFO(this->get_logger(), "X: %.f Y: %.f\n", msg->linear_velocity, msg->angular_velocity);
    }

    void circle_draw(const turtlesim::msg::Pose::SharedPtr msg){

        //anda 2 para frente
        this->msg.linear.x = msg->linear_velocity + 2;
        //roda em torno do eixo z
        this->msg.angular.z = msg->angular_velocity + 3;
        
        RCLCPP_INFO(this->get_logger(), "Publishing: Position (%.2f, %.2f, %.2f)", this->msg.linear.x, this->msg.linear.y, this->msg.linear.z);

        //publicando mensagem do node
        cmd_vel_pub->publish(this->msg);
    }

public:
    pose_node() : Node("pose_subscriber"){
        this->cmd_vel_pub = this->create_publisher<geometry_msgs::msg::Twist>("turtle2/cmd_vel", 10);
        this->cmd_pos_sub = this->create_subscription<turtlesim::msg::Pose>("turtle1/pose", 10, std::bind(&pose_node::circle_draw, this, std::placeholders::_1));
    }
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);

    auto node = std::make_shared<pose_node>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}