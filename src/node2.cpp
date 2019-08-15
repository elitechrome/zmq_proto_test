#include <zmq.hpp>
#include <msgs/Robot.pb.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

int main (int argc, char *argv[])
{
  zmq::context_t context (1);
  zmq::socket_t socket(context, ZMQ_SUB);
  socket.bind ("tcp://*:5556");

  while (true) {
    zmq::message_t request;
    //  Wait for next request from client
    socket.recv (&request);
    static unsigned int cnt = 0;
    std::cout << "Received #" << cnt << "\n";
    Robot::Path2D path;
    std::string msg_str(static_cast<char*>(request.data()), request.size());
    path.ParseFromString(msg_str);
  }
  return 0;
}
