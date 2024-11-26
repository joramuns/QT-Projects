#ifndef VIEW_LIGHTSETTINGS_H_
#define VIEW_LIGHTSETTINGS_H_

#include <QPushButton>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

namespace s21 {
  class LightSettings : public QWidget {
    Q_OBJECT

    public:
      LightSettings();
      virtual ~LightSettings() = default;

      public slots:
        /* void ColorSlot(); */
        /* void PositionSlot(); */

signals:
        void ColorSignal();
        void PositionSignal();

    private:
        QVBoxLayout *layout_;
        QPushButton *color_;
        QDoubleSpinBox *x_pos_;
        QDoubleSpinBox *y_pos_;
        QDoubleSpinBox *z_pos_;
        void InitFields();
        void CreateLabelButton(QString text, QDoubleSpinBox *pos);
        void ConnectFields();
        void InitLayouts();
  };

}  // namespace s21
#endif  // VIEW_LIGHTSETTINGS_H_
