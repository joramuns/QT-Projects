#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QObject>

#include "../model/model.h"
#include "../view/calcwindow.h"

namespace s21 {
class Controller : public QObject {
  Q_OBJECT

 public:
  Controller() = delete;
  Controller(CalcWindow *cview, Model *cmodel);
  Controller(const Controller &other) = delete;
  Controller(Controller &&other) = delete;
  Controller &operator=(const Controller &other) = delete;
  Controller &operator=(Controller &&other) = delete;

 public slots:
  void ClearButton() noexcept;
  void NumButton() noexcept;
  void OperButton() noexcept;
  void EvalButton() noexcept;
  void MakePlot();
  void VariableSet() noexcept;
  /* Credit calc */
  void CreditEvalButton() noexcept;
  /* Deposit calc */
  void DepositAddReplenishment() noexcept;
  void DepositRemoveReplenishment() noexcept;
  void DepositAddWithdrawal() noexcept;
  void DepositRemoveWithdrawal() noexcept;
  void DepositEvalButton() noexcept;

 private:
  void Render() const noexcept;
  void SetCreditData() noexcept;
  void RenderCredit() noexcept;
  void RenderReplenishment() const noexcept;
  void RenderWithdrawal() const noexcept;
  void SetDepositData() noexcept;
  void RenderDeposit() const noexcept;
  /* MVC */
  CalcWindow *view_;
  Model *model_;
};

}  // namespace s21
#endif  // CONTROLLER_CONTROLLER_H_
