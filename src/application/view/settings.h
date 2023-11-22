#ifndef VIEW_SETTINGS_H_
#define VIEW_SETTINGS_H_

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

class ASettings : public QWidget {
  Q_OBJECT

 public:
  ASettings();
  virtual ~ASettings() = default;

 protected:
  QVBoxLayout *layout_;

 private:
  virtual void InitFields() = 0;
  virtual void InitLayouts() = 0;
};

class SceneSettings : public ASettings {
 public:
  SceneSettings();
  void SetComboBoxOptions(const QVector<QString> &labels);

 private:
  void InitFields() override;
  void InitLayouts() override;

 private:
  QPushButton *color_;
  QComboBox *type_;
};

class ModelSettings final : public SceneSettings {
  Q_OBJECT

 public:
  ModelSettings();

 private:
  void InitFields() override;
  void InitLayouts() override;

 private:
  QDoubleSpinBox *size_;
};

class SettingsTab final : public QTabWidget {
  Q_OBJECT

 public:
  SettingsTab();

 private:
  SceneSettings *scene_settings_;
  ModelSettings *vertex_settings_;
  ModelSettings *edge_settings_;
};

#endif  // VIEW_SETTINGS_H_
