#ifndef ADDRESSSETTING_H
#define ADDRESSSETTING_H

#include <QWidget>

namespace Ui {
class addressSetting;
}

class addressSetting : public QWidget
{
    Q_OBJECT

public:
    explicit addressSetting(QWidget *parent = nullptr);
    ~addressSetting();
    void situationUpdate();

    bool eventFilter(QObject *obj, QEvent *event);                                    //自定义一些Qlable的点击实现
private:
    Ui::addressSetting *ui;
};

#endif // ADDRESSSETTING_H
