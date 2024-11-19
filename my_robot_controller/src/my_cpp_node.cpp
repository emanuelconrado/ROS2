#include "rclcpp/rclcpp.hpp"
#include <iostream>
#include <string>
#include <chrono>

class MyNode : public rclcpp::Node
{

private:
    int count_;
    rclcpp::TimerBase::SharedPtr timer_;

    void timer_callback(){
        this->count_++;
        RCLCPP_INFO(this->get_logger(), "Hello, World %d", this->count_);
    }

public:
    MyNode() : Node("my_cpp_node"){
        this->count_ = 0;
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&MyNode::timer_callback, this)
        );
    }
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);

    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
