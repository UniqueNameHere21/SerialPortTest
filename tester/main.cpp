#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QDebug>

void sendData(QSerialPort& serial)
{
    // Send a single message
    QByteArray data = "Hello, Virtual Serial Port!";
    serial.write(data);
    qDebug() << "Sent data: " << data;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSerialPort serial;
    serial.setPortName("/dev/pts/5");  // Replace with your virtual port
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    if (serial.open(QIODevice::WriteOnly)) {
        qDebug() << "Serial port opened successfully.";

        // Use a QTimer to send data every 1 seconds
        QTimer timer;
        timer.setInterval(1000);  // 1 seconds interval
        QObject::connect(&timer, &QTimer::timeout, [&]() {
            sendData(serial);
        });
        timer.start();

        // Start the application event loop
        return a.exec();
    } else {
        qDebug() << "Failed to open serial port.";
        return 1;
    }
}
