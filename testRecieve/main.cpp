#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString portName;

    // Check if a command-line argument for the port is provided
    if (argc > 1) {
        portName = argv[1];
    } else {
        // If no argument is provided, use a default port name
        portName = "/dev/pts/6";  // Replace with your desired port
    }

    QSerialPort serial;
    serial.setPortName(portName);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    if (serial.open(QIODevice::ReadOnly)) {
        qDebug() << "Serial port opened successfully.";

        // Continuously wait for and process incoming data
        while (true) {
            // Wait until data is available
            if (serial.waitForReadyRead(-1)) {
                // Read and display the received data
                QByteArray data = serial.readAll();
                qDebug() << "Received data: " << data;

                // You can add additional processing logic here

            } else {
                qDebug() << "Failed to wait for data.";
                break; // Break out of the loop on error
            }
        }

        // Close the serial port and quit the application
        serial.close();
        return 0;
    } else {
        qDebug() << "Failed to open serial port.";
        return 1;
    }
}
