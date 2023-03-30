#include "mybutton.h"

MyButton::MyButton(QString text, QWidget *parent):
    QPushButton(parent){
    setText(text);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QSize MyButton::sizeHint() const {
    QSize size = QPushButton::sizeHint();
    size.rheight() += 30;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

