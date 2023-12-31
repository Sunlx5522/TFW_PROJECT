#ifndef QRCODE_H
#define QRCODE_H

#include "qrencode.h" //该头文件在工程目录下 可饮用
#include <QWidget>
#include <QString>
#include "QPixmap"
namespace Ui {
class qrcode;
}
class qrcode : public QWidget
{
    Q_OBJECT

public:
    explicit qrcode(QWidget *parent = nullptr);
    ~qrcode();
    void GernerateQRCode(const QString &text, QPixmap &qrPixmap, int scale); //二维码生成函数
    bool eventFilter(QObject *obj, QEvent *event); //自定义一些Qlable的点击实现
    void slot_GenerateQRCode(); //辅助槽函数
private:
    Ui::qrcode *ui;
};

#endif // QRCODE_H
