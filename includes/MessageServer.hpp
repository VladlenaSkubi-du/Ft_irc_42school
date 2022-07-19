#pragma once

#include "FD.hpp"

class MessageServer {
    public:
        MessageServer() {};
        ~MessageServer() {};
        void        send_message();
        void        write_message();
    private:
        void        *read_func();
        void        *write_func();
        // char        **read_buff;
        // char        **write_buf;
        FD          *fds;
};