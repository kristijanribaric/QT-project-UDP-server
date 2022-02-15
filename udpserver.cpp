#include "udpserver.h"
#include "ui_udpserver.h"
#include <QUdpSocket>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

UDPServer::UDPServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UDPServer)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("UDP Server"));
    socket = new QUdpSocket(this);

}

UDPServer::~UDPServer()
{
    delete ui;
}

QByteArray getPublicKey() {
    QByteArray PublicKey;
    PublicKey.append("-----BEGIN PUBLIC KEY-----\n");
    PublicKey.append("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAntGSOUusaJACRVWYWIp+\n");
    PublicKey.append("AqlUd155lKK56fQBg0es0nyYNi+ps3j+k9qJh9hmqQ9FyugugPe1rgvjMbyLrI/P\n");
    PublicKey.append("XGUcpyO98bIrJwNLr9s0apFt6YfBSDJVUnHhvbXGBBoCyxUiMnc1hUDs/JDkEJI7\n");
    PublicKey.append("DcfTLxO4cERIVVtJQw+JsUuLS/sJ9BrBKM94FDYrVxCqDL1znq7OCiIeWPoT4Nvw\n");
    PublicKey.append("9tPoFortncDFCPqmaj7eppXFKq4oKKpDeuwZYAS+M23qw8x+DtfXSaGutZOJSK7v\n");
    PublicKey.append("AWeeMac7e9dEs8y7Hez31DyWOHkY+0ymZ134Zl8MSc7MdbGWh0O8tq2F9P3ogSf7\n");
    PublicKey.append("ZwIDAQAB\n");
    PublicKey.append("-----END PUBLIC KEY-----\n");

    return PublicKey;
}

QByteArray EncryptRSA (QByteArray employees) {
    qDebug() << "Loading keys..";
    QByteArray PublicKey = getPublicKey();

    Cipher cWrapper;
    RSA* publickey = cWrapper.getPublicKey(PublicKey);

    QByteArray plain = employees;
    QByteArray encrypted = cWrapper.encryptRSA(publickey,plain);
    qDebug() << plain;
    qDebug() << encrypted.toBase64();
    cWrapper.freeRSAKey(publickey);
    return encrypted;
}


void UDPServer::on_submitButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("db/ntp_database.db");



        if(db.open()){
            QSqlQuery query;
            query.prepare("select name,lastname,vacation_remaining from employees where vacation_remaining = 30 or vacation_remaining is null");

            if(!query.exec()){
                QMessageBox::warning(this,"Connection","Query exectuion failed!");

            }
            else {
                employees = "";
                while(query.next()){
                    QString nameDB = query.value(0).toString();
                    QString lastnameDB = query.value(1).toString();

                    QString employee = nameDB + " " + lastnameDB + "\n";
                    employees.append(employee.toUtf8());

                }
            }
        }
     QByteArray _employees = EncryptRSA(employees);

    auto datagram = _employees;

    socket->writeDatagram(datagram,QHostAddress::Broadcast,ui->port->value());
}

