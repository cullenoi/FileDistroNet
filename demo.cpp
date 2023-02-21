#include <asio.hpp>
#include <iostream>

using namespace std;


enum class CustomMsgTypes : uint32_t
{
    Serveraccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};