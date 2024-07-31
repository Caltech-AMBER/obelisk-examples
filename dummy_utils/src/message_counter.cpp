#include <chrono>
#include <cmath>
#include <vector>
#include <algorithm>
#include "rclcpp/rclcpp.hpp"
#include "obelisk_sensor_msgs/msg/obk_image.hpp"

class MessageCounterNode : public rclcpp::Node
{
public:
  MessageCounterNode()
  : Node("message_counter_node"), count_(0)
  {
    this->declare_parameter<std::string>("topic", "topic");
    std::string topic = this->get_parameter("topic").as_string();

    subscription_ = this->create_subscription<obelisk_sensor_msgs::msg::ObkImage>(
      topic, 10, std::bind(&MessageCounterNode::topic_callback, this, std::placeholders::_1));
      
    timer_ = this->create_wall_timer(
      std::chrono::seconds(1), std::bind(&MessageCounterNode::timer_callback, this));
  }

private:
  void topic_callback(const obelisk_sensor_msgs::msg::ObkImage::SharedPtr msg)
  {
    (void)msg;  // To avoid unused variable warning

    auto now = std::chrono::high_resolution_clock::now();
    if (last_time_.time_since_epoch().count() != 0) {
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - last_time_).count();
      time_differences_.push_back(duration);
    }
    last_time_ = now;

    count_++;
  }

  void timer_callback()
  {
    if (count_ > 0) {
      double mean = 0.0;
      double stdev = 0.0;
      double min_diff = *std::min_element(time_differences_.begin(), time_differences_.end());
      double max_diff = *std::max_element(time_differences_.begin(), time_differences_.end());
      
      for (const auto& diff : time_differences_) {
        mean += diff;
      }
      mean /= time_differences_.size();

      for (const auto& diff : time_differences_) {
        stdev += (diff - mean) * (diff - mean);
      }
      stdev = std::sqrt(stdev / time_differences_.size());

      RCLCPP_INFO(this->get_logger(), 
                  "Received %d msgs in last 1s | min: %.2f ms | max: %.2f ms | mean_diff: %.2f ms | stdev: %.2f ms", 
                  count_, min_diff / 1000.0, max_diff / 1000.0, mean / 1000.0, stdev / 1000.0);

      time_differences_.clear();
    } else {
      RCLCPP_INFO(this->get_logger(), "No messages received in the last second");
    }

    count_ = 0;
  }

  rclcpp::Subscription<obelisk_sensor_msgs::msg::ObkImage>::SharedPtr subscription_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
  std::chrono::time_point<std::chrono::high_resolution_clock> last_time_;
  std::vector<double> time_differences_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MessageCounterNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
