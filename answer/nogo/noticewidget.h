#ifndef NOTICEWIDGET_H
#define NOTICEWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class NoticeWidget;
}

class NoticeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NoticeWidget(QString s = "", QWidget *parent = nullptr);
    ~NoticeWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NoticeWidget *ui;
};

#endif // NOTICEWIDGET_H
