#ifndef VIEW_APP_MANAGEMENT_H_
#define VIEW_APP_MANAGEMENT_H_

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace s21 {
class AppManagement : public QGroupBox {
  Q_OBJECT

 public:
  AppManagement() = delete;
  explicit AppManagement(const QString &label);

 signals:
  void AppOpenFileSignal();

 public slots:
  void AppOpenFileSlot();

 private:
  void InitFields();
  void InitLayouts();

 private:
  QPushButton *open_button_;
  QPushButton *shot_button_;
  QPushButton *cast_button_;
};
}  // namespace s21

#endif  // VIEW_APP_MANAGEMENT_H_
