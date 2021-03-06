#include "TadpoleApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

/*
 * Kernels
 */
#include "LaplaceYoung.h"

template<>
InputParameters validParams<TadpoleApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

TadpoleApp::TadpoleApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  TadpoleApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  TadpoleApp::associateSyntax(_syntax, _action_factory);
}

TadpoleApp::~TadpoleApp()
{
}

// External entry point for dynamic application loading
extern "C" void TadpoleApp__registerApps() { TadpoleApp::registerApps(); }
void
TadpoleApp::registerApps()
{
  registerApp(TadpoleApp);
}

// External entry point for dynamic object registration
extern "C" void TadpoleApp__registerObjects(Factory & factory) { TadpoleApp::registerObjects(factory); }
void
TadpoleApp::registerObjects(Factory & factory)
{
  /*
   * Kernels
   */
   registerKernel(LaplaceYoung);
}

// External entry point for dynamic syntax association
extern "C" void TadpoleApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { TadpoleApp::associateSyntax(syntax, action_factory); }
void
TadpoleApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
