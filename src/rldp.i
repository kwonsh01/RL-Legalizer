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

%template(IntVector) std::vector< int >;
%template(CellVector) std::vector< RL_LEGALIZER::Instance >;
%template(CellVectorVector) std::vector< std::vector< RL_LEGALIZER::Instance > >;
%template(TruffleVector) std::vector< RL_LEGALIZER::truffle >;

%typemap(out) std::vector< std::vector< RL_LEGALIZER::Instance > >::value_type & {
$result = SWIG_NewPointerObj(SWIG_as_voidptr($1), $descriptor(std::vector< RL_LEGALIZER::Instance >), 0 |  0 );
}