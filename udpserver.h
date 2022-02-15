#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QFile>
#include "cipher.h"



QT_BEGIN_NAMESPACE
namespace Ui { class UDPServer; }
QT_END_NAMESPACE
class QUdpSocket;
class UDPServer : public QWidget
{
    Q_OBJECT

public:
    UDPServer(QWidget *parent = nullptr);
    ~UDPServer();

private slots:
    void on_submitButton_clicked();

private:
    Ui::UDPServer *ui;
    QUdpSocket *socket;
    QByteArray employees;
};
#endif // UDPSERVER_H
