#include "WebsocketClient.h"

//Use http://think-async.com/ insted of boost
#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_STL_
#define _WEBSOCKETPP_CPP11_THREAD_
#define _WEBSOCKETPP_CPP11_FUNCTIONAL_
#define _WEBSOCKETPP_CPP11_SYSTEM_ERROR_
#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_MEMORY_

#include "websocketpp/config/asio_client.hpp"
#include "websocketpp/client.hpp"

typedef websocketpp::client<websocketpp::config::asio_tls_client> Client;

class MillicastWebsocketClientImpl : public WebsocketClient
{
public:
    MillicastWebsocketClientImpl();
    ~MillicastWebsocketClientImpl();
    virtual bool connect(
      const std::string & url,
      const std::string & room,
      const std::string & username,
      const std::string & token,
      Listener          * listener
    ) override;
    virtual bool open(
      const std::string & sdp,
      const std::string & codec = "vp8",
      const std::string & Id = ""
    ) override;
    virtual bool trickle(
      const std::string & mid,
      const int index,
      const std::string & candidate,
      const bool last
    ) override;
    virtual bool disconnect(
      const bool wait
    ) override;

private:
    // Candidate for deletion: bool logged;
    std::string token;
    // Candidate for deletion: long long handle_id;

    std::atomic<bool> is_running;
    std::future<void> handle;
    std::thread thread;
   
    Client client;
    Client::connection_ptr connection;
};

