#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::tcp;
int main()
{
    try {
        boost::asio::io_service io_service;
        //������ �̸��� TCP ���������� �ٲٱ� ���ؼ� Resolver�� ����Ѵ�
        tcp::resolver resolver(io_service);
        //�����δ� ���� ����, ���񽺴� Daytime ��������
        tcp::resolver::query query("localhost", "daytime");
        //DNS�� ���� IP �ּ� �� ��Ʈ ��ȣ�� ���´�
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        //���� ��ü�� �ʱ�ȭ�ؼ� ������ �����Ѵ�
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        while (true)
        {
            //���� �� ���� ó�� ������ �����Ѵ�
            boost::array<char, 128> buf;
            boost::system::error_code error;
            //���۸� �̿��� �����κ��� �����͸� �޾ƿ´�
            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
                break;
            else if (error)
                throw boost::system::system_error(error);
            //���ۿ� ��� �����͸� ȭ�鿡 ���
            std::cout.write(buf.data(), len);
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}