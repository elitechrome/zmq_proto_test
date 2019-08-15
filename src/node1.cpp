#include <zmq.hpp>
#include <msgs/Robot.pb.h>
#include <iostream>
#include <cstdlib>
#include <string>


#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

int main () {

  GOOGLE_PROTOBUF_VERIFY_VERSION;
  Robot::Path2D path;

  zmq::context_t context (1);
  zmq::socket_t publisher (context, ZMQ_PUB);
  publisher.bind("tcp://*:5556");

  while (1) {
    for (ssize_t i = 0; i < 100000; i++)
    {
      Robot::Point2D* point = path.add_points();
      point->set_x(1);
      point->set_y(1);
    }

    std::string msg_str;
    path.SerializeToString(&msg_str);
    // create a zmq message from the serialized string
    zmq::message_t request (msg_str.size());
    memcpy ((void *) request.data (), msg_str.c_str(), msg_str.size());
    std::cout << "Sending Path data ...\n";
    publisher.send (request);

  }

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}
