#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

//���� ��ǻ���� ��¥ �� �ð� ������ ��ȯ
string make_daytime_string() {
    time_t  now = time(0);
    return ctime(&now);
}

int main() {
    //80�� port -> HTTP ��������, 13 port -> Day time ��������
    try {
        //�⺻������ Boost Asio ���α׷��� �ϳ��� IO Service ��ü�� ����
        boost::asio::io_service io_service;
        //TCP ���������� 13�� ��Ʈ�� ������ �޴� ���� ������ ����
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

        //��� Ŭ���̾�Ʈ�� ���� ������ �ݺ� ����
        while (true)
        {
            //���� ��ü�� ������ ������ ��ٸ�
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            //������ �Ϸ�Ǹ� �ش� Ŭ���̾�Ʈ���� ���� �޼����� ����
            string message = make_daytime_string();

            //�ش� Ŭ���̾�Ʈ���� �޼����� ��� ����
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (exception& e)
    {
        cerr << e.what() << std::endl;
    }
    return 0;
}