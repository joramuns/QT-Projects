#ifndef VIEW_SETTINGS_H_
#define VIEW_SETTINGS_H_

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace s21 {
class ASettings : public QWidget {
  Q_OBJECT

 public:
  ASettings();
  virtual ~ASettings() = default;

 public slots:
  void ColorSlot();
  void ComboBoxSlot();

 signals:
  void ColorSignal();
  void ComboBoxSignal(int index);

 protected:
  QVBoxLayout *layout_;

 private:
  virtual void InitFields() = 0;
  virtual void ConnectFields() = 0;
  virtual void InitLayouts() = 0;
};

class SceneSettings : public ASettings {
 public:
  SceneSettings();
  void SetComboBoxOptions(const QVector<QString> &labels);

 private:
  void InitFields() override;
  void ConnectFields() override;
  void InitLayouts() override;

 private:
  QPushButton *color_;
  QComboBox *type_;
};

class ExtraSceneSettings : public SceneSettings {
  Q_OBJECT

 public:
  ExtraSceneSettings();
  void SetExtraComboBoxOptions(const QVector<QString> &labels);

 public slots:
  void ExtraComboBoxSlot();

 signals:
  void ExtraComboBoxSignal(int index);

 private:
  void InitFields() override;
  void ConnectFields() override;
  void InitLayouts() override;

 private:
  QComboBox *wireframe_type_;
};

class ModelSettings final : public SceneSettings {
  Q_OBJECT

 public:
  ModelSettings();

 public slots:
  void SpinBoxSlot();

 signals:
  void SpinBoxSignal(double value);

 private:
  void InitFields() override;
  void ConnectFields() override;
  void InitLayouts() override;

 private:
  QDoubleSpinBox *size_;
};
}  // namespace s21

#endif  // VIEW_SETTINGS_H_
