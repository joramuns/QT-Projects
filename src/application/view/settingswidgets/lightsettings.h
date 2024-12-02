#ifndef VIEW_LIGHTSETTINGS_H_
#define VIEW_LIGHTSETTINGS_H_

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <array>
#include <string>

namespace s21 {
class LightSettings : public QWidget {
  Q_OBJECT

 public:
  LightSettings() = delete;
  LightSettings(std::array<std::string, 3> labels, float bound_value);
  virtual ~LightSettings() = default;
  void SetDecimals(int prec);

 public slots:
  void PositionSlot();

 signals:
  void PositionSignal(std::array<double, 3> args);

 private:
  std::array<std::string, 3> labels_;
  float bound_value_;
  QVBoxLayout *layout_;
  std::array<QDoubleSpinBox *, 3> inputs_;
  void InitFields();
  void ConnectFields();
};

}  // namespace s21
#endif  // VIEW_LIGHTSETTINGS_H_
