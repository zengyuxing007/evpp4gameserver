#include <evpp/exp.h>
#include <evpp/tcp_server.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>

#include "header.h"

class AFTcpServer
{
public:
    explicit AFTcpServer(evpp::EventLoop* loop, const std::string& name, const std::string& addr, const int thread_num)
        : ev_loop(loop)
        , server(ev_loop, addr, name, thread_num)
    {
        server.SetMessageCallback(&AFTcpServer::OnMessage);
        server.SetConnectionCallback(&AFTcpServer::OnConnection);
    }

    void init_and_run()
    {
        server.Init();
        server.Start();

        std::thread run_thread(&AFTcpServer::Run, this);
        run_thread.detach();
    }

protected:
    static void OnConnection(const evpp::TCPConnPtr& conn)
    {
        if(conn->IsConnected())
        {
            conn->SetTCPNoDelay(true);
            std::shared_ptr<uint32_t> count(new uint32_t(0));
            conn->set_context(evpp::Any(count));
            //print threadid
            LOG_INFO << "[Connection] Server thread id =" << std::this_thread::get_id() << ", fd = " << conn->fd();
        }
    }
    static void OnMessage(const evpp::TCPConnPtr& conn, evpp::Buffer* buf)
    {
        LOG_INFO << " buf->size=" << buf->size();
        const size_t kHeaderLen = sizeof(Header);
        while(buf->size() > kHeaderLen)
        {
            Header* header = reinterpret_cast<Header*>(const_cast<char*>(buf->data()));
            auto full_size = header->get_full_size();
            if(buf->size() < full_size)
            {
                // need to read more data
                return;
            }

            LOG_INFO << "full_size=" << full_size << " header.body_size_=" << ntohl(header->body_size_) << " header.packet_count_=" << ntohl(header->packet_count_);

            header->inc_packet_count();
            //TODO:放到队列中去
            conn->Send(buf->data(), full_size);

            buf->Skip(full_size);
        }
    }

    void Run()
    {
        ev_loop->Run();
    }

private:
    evpp::TCPServer server;
    evpp::EventLoop* ev_loop;
};

int main(int argc, char* argv[])
{
    std::string addr = "0.0.0.0:9099";
    int thread_num = 4;

    evpp::EventLoop loop;
    AFTcpServer server(&loop, "AFTcpServer", addr, thread_num);
    server.init_and_run();

    return 0;
}


#include "../../../examples/echo/tcpecho/winmain-inl.h"