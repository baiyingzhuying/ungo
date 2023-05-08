#ifndef CHATFORM_H
#define CHATFORM_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWidget>

namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = nullptr);
    ~ChatForm();

private:
    Ui::ChatForm *ui;
    QLineEdit *usernameEdit;

    bool send();
};

#endif // CHATFORM_H
