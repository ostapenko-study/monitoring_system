#ifndef WEBSOCKET_COMMON_H
#define WEBSOCKET_COMMON_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#define GET_SET_POINTER(type, name) \
private: \
type* m##name = nullptr; \
public: \
void set##name(type* var) {m##name = var;} \
type* get##name() const {return m##name;}

namespace file
{
    QByteArray read(const QString &filename);
    void write(const QString &filename, const QString &data);
}

namespace generator
{
    QString machineId();
}

class QWebSocket;

namespace websocket
{
    bool sendTextMessage(QWebSocket* socket, const QString& message);
}

namespace json
{
    QJsonDocument toJson(const QByteArray& data);
    QString toString(const QJsonObject& obj);
    QJsonObject parseStr(const QString& msg);

    template<class ForwardIt>
    QJsonArray containerToJson(ForwardIt begin, ForwardIt end)
    {
        QJsonArray answer;

        for(/**/; begin != end; ++begin){
            answer.append(begin->toJson());
        }

        return answer;
    }


    QJsonObject generateError(const QString& text_error);

    QJsonObject generateResult(QJsonObject obj);

    const QJsonObject resultOk = generateResult({});
}


#endif // WEBSOCKET_COMMON_H
