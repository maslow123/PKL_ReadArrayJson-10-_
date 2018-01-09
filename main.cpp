#include <QCorepplication>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>
#include <QModelIndex>




void sendRequest();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    sendRequest();

    return a.exec();
}

void sendRequest(){
    //membuat event perulangan sementara
    QEventLoop eventLoop;
    // selesai
    QNetworkAccessManager mgr;
    QObject::connect(&mgr,SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));

    //http request
    QNetworkRequest req(QUrl(QString("http://localhost/api/index.php?operasi=view")));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    if(reply -> error() == QNetworkReply::NoError){
        QString strReply = (QString)reply ->readAll();

        //parse json
        qDebug()<<"Hasil:" <<endl <<endl << strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonArray jsonArray = jsonResponse.array();

        foreach(const QJsonValue &value,jsonArray){


                QJsonObject jsonObj = value.toObject();

                qDebug() <<jsonObj["NIS"].toString();
                qDebug() <<jsonObj["Nama"].toString();
                qDebug() <<jsonObj["Kelas"].toString();
                qDebug() <<jsonObj["Alamat"].toString();
                qDebug() <<jsonObj["Hobi"].toString();

                delete reply;


        }
   }
    else{
        qDebug()<<"Mohon Periksa Koneksi Database Anda !";
        delete reply;
    }


}
QJsonObject ObjectFromString(const QString& in)
{
    QJsonObject obj;

    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if(!doc.isNull())
    {
        if(doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qDebug() << "Document is not an object" << endl;
        }
    }
    else
    {
        qDebug() << "Invalid JSON...\n" << in << endl;
    }

    return obj;
}
