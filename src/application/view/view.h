#ifndef VIEW_H_
#define VIEW_H_

#include <QMainWindow>

/* QT_BEGIN_NAMESPACE */
/* class QWidge; */
/* class QGridLayout; */
/* QT_END_NAMESPACE */
#include <QGridLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>
#include <QWidget>

namespace s21 {
class View final : public QMainWindow {
  Q_OBJECT

 public:
  View();

 private:
};
}  // namespace s21

#endif  // VIEW_H_
