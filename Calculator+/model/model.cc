#include "model.h"

namespace s21 {
void Model::Convert() {
  for (const auto &item : GetInfixData()) {
    if (item.IsOperator()) {
      AddOperator(item);
    } else {
      AddOperand(item);
    }
  }
  Finalize();
}

/* Debug output */
void Model::OutputModel() {
  std::cout << "Infix notation: ";
  for (const auto &item : GetInfixData()) {
    std::cout << item << " ";
  }
  std::cout << std::endl << "Polish notation: ";
  for (const auto &item : GetStack()) {
    std::cout << item << " ";
  }
  if (GetQueue().size()) {
    std::cout << std::endl << "Queue stack: ";
    for (const auto &item : GetQueue()) {
      std::cout << item << " ";
    }
  }
}
}  // namespace s21
