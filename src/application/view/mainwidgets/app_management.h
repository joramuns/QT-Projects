/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса AppManagement
*/
#ifndef VIEW_APP_MANAGEMENT_H_
#define VIEW_APP_MANAGEMENT_H_

#include <QFileDialog>
#include <QGroupBox>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace s21 {
/// @brief Класс отвечающий за инициализацию и добавление в интерфейс
/// пользователя core кнопок управления, а также кнопок скриншота и скринкаста
class AppManagement : public QGroupBox {
  Q_OBJECT

 public:
  AppManagement() = delete;

  /// @brief Констурктор класса с параметрами
  /// @param label Имя группы кнопок
  explicit AppManagement(const QString &label);

 signals:
  void AppOpenFileSignal(const QString &filename);
  void AppCloseFileSignal();
  void AppScreenshotSignal(const QString &filename);
  void AppGifSignal(const QString &filename);

 public slots:
  void AppOpenFileSlot();
  void AppCloseFileSlot();
  void AppScreenshotSlot();
  void AppGifSlot();

 private:
  /// @brief Инициализирует core кнопки
  void InitFields();

  /// @brief Связывает кнопки с обработчиком событий
  void ConnectFields();

  /// @brief  Добавляет core кнопки в интерфейс пользователя
  void InitLayouts();

 private:
  QPushButton *open_button_;  ///< указатель на объект кнопки отвечающей за
                              ///< открытие файла
  QPushButton *close_button_;  ///< указатель на объект кнопки отвечающей за
                               ///< закрытие файла
  QPushButton
      *shot_button_;  ///< указатель на объект кнопки отвечающей за скриншот
  QPushButton
      *cast_button_;  ///< указатель на объект кнопки отвечающей за скринкаст
};
}  // namespace s21

#endif  // VIEW_APP_MANAGEMENT_H_
