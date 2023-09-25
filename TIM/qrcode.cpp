#include "ui_qrcode.h"
#include"qrencode.h"
#include "qrcode.h"
#include<QPainter>
#include"widget.h"
#include<QString>
#include<QPixmap>
#include<QLabel>
#include<QImage>

extern Widget* ww;
extern qrcode *cc;

qrcode::qrcode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qrcode)
{
    ui->setupUi(this);
    this->setWindowTitle("qrcode");
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground);                                                    //把窗口背景设置为透明;
    setWindowFlags(Qt::FramelessWindowHint | windowFlags()|Qt::WindowStaysOnTopHint);              //去窗口边框
    ui->close->installEventFilter(this);
    ui->QRlabel->setScaledContents(true);                                                          //控件图片自适应大小
    ui->close->setAttribute(Qt::WA_Hover,true);                                                    //开启悬停事件
}

qrcode::~qrcode()
{
    delete ui;
    ww->refresh();
}


bool qrcode::eventFilter(QObject *obj, QEvent *event)
{

    if(qobject_cast<QLabel*>(obj) == ui->close)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/close.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            cc->close();
            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/close2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/close1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img


        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/close.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

        }
    }
  return false;
}

void qrcode::GernerateQRCode(const QString &text, QPixmap &qrPixmap, int scale)
  {
     if(text.isEmpty())
     {
         return;
     }

     //二维码数据
     QRcode *qrCode = nullptr;
     //这里二维码版本传入参数是2,实际上二维码生成后，它的版本是根据二维码内容来决定的
     qrCode = QRcode_encodeString(text.toStdString().c_str(), 2,
                                  QR_ECLEVEL_Q, QR_MODE_8, 1);

     if(nullptr == qrCode)
     {
         return;
     }

     int qrCode_Width = qrCode->width > 0 ? qrCode->width : 1;
     int width = scale * qrCode_Width;
     int height = scale * qrCode_Width;

     QImage image(width, height, QImage::Format_ARGB32_Premultiplied);

     QPainter painter(&image);
     painter.setBrush(QColor("#FFE4E1"));
     painter.setPen(Qt::NoPen);
     painter.drawRect(0, 0, width, height);
     painter.setBrush(QColor("#363636"));
     for(int y = 0; y < qrCode_Width; ++y)
     {
         for(int x = 0; x < qrCode_Width; ++x)
         {
             unsigned char character = qrCode->data[y * qrCode_Width + x];
             if(character & 0x01)
             {
                QRect rect(x * scale, y * scale, scale, scale);
                painter.drawRects(&rect, 1);
             }
         }
     }

     qrPixmap = QPixmap::fromImage(image);
     QRcode_free(qrCode);
}

void qrcode::slot_GenerateQRCode()
  {
    QPixmap qrPixmap;
    int width = ui->QRlabel->width();
    int height = ui->QRlabel->height();
    GernerateQRCode("https://grounded-screen-774762.framer.app/", qrPixmap, 2);
    qrPixmap = qrPixmap.scaled(QSize(width, height),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->QRlabel->setPixmap(qrPixmap);
  }

