#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton {
  Q_OBJECT

public:
  explicit MyButton(QString text, QWidget *parent = nullptr);

  QSize sizeHint() const override;
};

#endif // MYBUTTON_H
