#include "LaplaceYoung.h"


template<>
InputParameters validParams<LaplaceYoung>()
{
  InputParameters p = validParams<Kernel>();
  return p;
}

LaplaceYoung::LaplaceYoung(const InputParameters & parameters) :
    Kernel(parameters)
{
}

Real
LaplaceYoung::computeQpResidual()
{
  Real k = 1.0 / std::sqrt(1 + std::abs(_grad_u[_qp] * _grad_u[_qp]));
  Real kappa = 1;
  return k * _grad_u[_qp] * _grad_test[_i][_qp] + kappa * _u[_qp] * _test[_i][_qp];
}

Real
LaplaceYoung::computeQpJacobian()
{
  return 0.0;
}
