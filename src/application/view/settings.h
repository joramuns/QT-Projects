#ifndef VIEW_SETTINGS_H_
#define VIEW_SETTINGS_H_

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

class CommonSettings final : public QWidget {
  Q_OBJECT

 public:
  CommonSettings();

 public:
  QComboBox *type_;
  QPushButton *color_;
};

class VertexSettings final : public QWidget {
  Q_OBJECT

 public:
  VertexSettings();

 public:
  QComboBox *type_;
  QDoubleSpinBox *size_;
  QPushButton *color_;
};

class EdgeSettings final : public QWidget {
  Q_OBJECT

 public:
  EdgeSettings();

 public:
  QCheckBox *type_;
  QDoubleSpinBox *size_;
  QPushButton *color_;
};

class SettingsTab final : public QTabWidget {
  Q_OBJECT

 public:
  SettingsTab();

 private:
  CommonSettings *common_settings_;
  VertexSettings *vertex_settings_;
  EdgeSettings *edge_settings_;
};

#endif  // VIEW_SETTINGS_H_
