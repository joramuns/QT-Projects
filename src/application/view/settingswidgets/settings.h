/*!
\file
\brief Заголовочный файл с описанием классов настроек отображения

Данный файл содержит в себе определения классов настроек отображения
*/
#ifndef VIEW_SETTINGS_H_
#define VIEW_SETTINGS_H_

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace s21 {
/// @brief Базовый класс, описывающий стандартное поведение классов настроек
/// опций отображения
class ASettings : public QWidget {
  Q_OBJECT

 public:
  /// @brief Конструктор по умолчанию инициализирует "макет"
  ASettings();
  /// @brief  Виртуальный деструктор
  virtual ~ASettings() = default;

 public slots:
  /// @brief Подает сигнал о установке цвета
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

/// @brief Класс определяющий настройки отображения цвета сцены и проекции 3-х
/// мерного оъекта
class SceneSettings : public ASettings {
 public:
  /// @brief Конструктор по умолчанию
  SceneSettings();
  /// @brief Установка вариантов отображения
  /// @param labels вектор с именами типов отображения
  void SetComboBoxOptions(const QVector<QString> &labels);
  void SetComboBox(const int index);

 private:
  /// @brief Инициализация кнопок настроек отображения
  void InitFields() override;

  /// @brief Связывание сигналов с обработчиками
  void ConnectFields() override;

  /// @brief Расположение виджетов на макете
  void InitLayouts() override;

 private:
  QPushButton *color_;  ///<  указатель на виджет выбора цвета сцены
  QComboBox *type_;  ///< указатель на виджет выбора типа отображения 3-х
                     ///< мерного объекта
};

/// @brief Класс определяющий настройки типа отображения ребер 3-х мерного
/// объекта
class ExtraSceneSettings : public SceneSettings {
  Q_OBJECT

 public:
  /// @brief Конструктор по умолчанию
  ExtraSceneSettings();

  /// @brief Установка вариантов отображения ребер 3-х мерного объекта
  /// @param labels вектор с именами типов отображения
  void SetExtraComboBoxOptions(const QVector<QString> &labels);
  void SetExtraComboBox(const int index);

 public slots:
  void ExtraComboBoxSlot();

 signals:
  void ExtraComboBoxSignal(const int index);

 private:
  /// @brief Инициализация виджета выбора отображения ребер 3-х мерного объекта
  void InitFields() override;

  /// @brief Связывание сигналов с обработчиками
  void ConnectFields() override;

  /// @brief Расположения виджета на макете
  void InitLayouts() override;

 private:
  QComboBox *wireframe_type_;  ///< указатель на виджет выбора типа отображения
                               ///< ребер 3- мерного объекта
};

/// @brief Класс определяющий настройки размера и типа отображения вершин 3-х
/// мерного объекта
class ModelSettings final : public SceneSettings {
  Q_OBJECT

 public:
  /// @brief Конструктор по умолчанию
  ModelSettings();

  void SetSpinBox(const double value);

 public slots:
  void SpinBoxSlot();

 signals:
  void SpinBoxSignal(double value);

 private:
  /// @brief Инициализация виджетов управления размером и типом отоборажаемых
  /// вершин 3-х мерного объекта
  void InitFields() override;

  /// @brief Связывание сигналов управления с обработчиком
  void ConnectFields() override;

  /// @brief Расположение виджетов на макете
  void InitLayouts() override;

 private:
  QDoubleSpinBox *size_;  ///< указатель на виджет управления размером
                          ///< отображаемых вершин 3-х мерного объекта
};
}  // namespace s21

#endif  // VIEW_SETTINGS_H_
