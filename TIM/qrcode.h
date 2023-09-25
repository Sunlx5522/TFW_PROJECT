#ifndef QRCODE_H
#define QRCODE_H

#include"qrencode.h"
#include <QWidget>
#include<QString>
#include"QPixmap"
namespace Ui {
class qrcode;
}

class qrcode : public QWidget
{
    Q_OBJECT

public:
    explicit qrcode(QWidget *parent = nullptr);
    ~qrcode();
    void GernerateQRCode(const QString &text, QPixmap &qrPixmap, int scale);
    bool eventFilter(QObject *obj, QEvent *event);                                    //自定义一些Qlable的点击实现
    void slot_GenerateQRCode();
private:
    Ui::qrcode *ui;
};

#endif // QRCODE_H
