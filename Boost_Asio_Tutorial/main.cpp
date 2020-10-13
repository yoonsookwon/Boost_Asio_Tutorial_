#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::tcp;
int main()
{
    try {
        boost::asio::io_service io_service;
        //도메인 이름을 TCP 종단점으로 바꾸기 위해서 Resolver를 사용한다
        tcp::resolver resolver(io_service);
        //서버로는 로컬 서버, 서비스는 Daytime 프로토콜
        tcp::resolver::query query("localhost", "daytime");
        //DNS를 거쳐 IP 주소 및 포트 번호를 얻어온다
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        //소켓 객체를 초기화해서 서버에 연결한다
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        while (true)
        {
            //버퍼 및 오류 처리 변수를 선언한다
            boost::array<char, 128> buf;
            boost::system::error_code error;
            //버퍼를 이용해 서버로부터 데이터를 받아온다
            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
                break;
            else if (error)
                throw boost::system::system_error(error);
            //버퍼에 담긴 데이터를 화면에 출력
            std::cout.write(buf.data(), len);
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}