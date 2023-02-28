%module rldp

%rename(propertys) property;

%{
#include "../submodule/OpenDP/src/circuit.h"
#include "../include/RLDP.h"
%}
%{
#define SWIG_PYTHON_EXTRA_NATIVE_CONTAINERS
%}
%include <std_string.i>
%include <std_vector.i>
%include "../submodule/OpenDP/src/circuit.h"
%include "../include/RLDP.h"

%template(CellVector) std::vector< RL_LEGALIZER::instance >;
%template(CellVectorVector) std::vector< std::vector< RL_LEGALIZER::instance > >;
%template(TruffleVector) std::vector< RL_LEGALIZER::truffle >;

%typemap(out) std::vector< std::vector< RL_LEGALIZER::instance > >::value_type & {
$result = SWIG_NewPointerObj(SWIG_as_voidptr($1), $descriptor(std::vector< RL_LEGALIZER::instance >), 0 |  0 );
}