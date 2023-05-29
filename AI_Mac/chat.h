#ifndef CHAT_H
#define CHAT_H
#include <QMainWindow>
#include <QLineEdit>
#include <QMainWindow>

namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
    Q_OBJECT

public:

    explicit Chat(QWidget *parent = nullptr);
    ~Chat();
    Ui::Chat *ui;
private:


    // create a usernameEdit
    QLineEdit *usernameEdit;

    bool send();
signals:
    void send_info(QString );
};

#endif // CHAT_H
