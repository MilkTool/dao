/*
// Dao Virtual Machine
// http://www.daovm.net
//
// Copyright (c) 2006-2016, Limin Fu
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED  BY THE COPYRIGHT HOLDERS AND  CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED  WARRANTIES,  INCLUDING,  BUT NOT LIMITED TO,  THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS  BE LIABLE FOR ANY DIRECT,
// INDIRECT,  INCIDENTAL, SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES (INCLUDING,
// BUT NOT LIMITED TO,  PROCUREMENT OF  SUBSTITUTE  GOODS OR  SERVICES;  LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION)  HOWEVER CAUSED  AND ON ANY THEORY OF
// LIABILITY,  WHETHER IN CONTRACT,  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef DAO_TYPE_H
#define DAO_TYPE_H

#include"daoBase.h"
#include"daoConst.h"
#include"daoString.h"
#include"daoList.h"
#include"daoMap.h"
#include"daoStdtype.h"


/*
// Dao abstract type:
// type class for number, string, ... list<X>, ...
//
// for core types: number, string, complex, list, map, array
// eg:DaoType.name = "int", "float", "string", ...
//    DaoType.tid = DAO_INTEGER, DAO_STRING, ...
//
// for Dao class and routine types:
//    DaoType.name = "foo", "bar", ...
//    DaoType.count = 0;
//    DaoType.tid = DAO_CLASS, DAO_CDATA,
//    DaoType.aux = the Dao class or C type
//
// for item types: list<float>, map<string,float>, ...
//    DaoType.name = "list<float>", "map<string,float>", ...
//    DaoType.tid = DAO_LIST, DAO_MAP
//    DaoType.aux = NULL;
//    DaoType.args[] = item DaoType(s) : X<args[0],args[1],...>
//
// for routine type: routine(float,string):float
//    DaoType.name = "routine<float,string=>float>"
//    DaoType.tid = DAO_ROUTINE
//    DaoType.aux = returned type
//    DaoType.args[] = parameter DaoType(s) : (<args[0],...)
//
//    e.g.:
//        routine<float=>?>: foo( a : float ){}
//        routine<float=>float>: foo( a : float ) : float{}
//        routine<a:float=>?>: foo( a : float ){}
//        routine<a=float=>?>: foo( a = 1 ){}
//        routine<a:float,b=string=>?>: foo( a : float, b="abc" ){}
//        routine<a:float,b:?=>?>: foo( a : float, b ){}
//        routine<a:float,b:?=>?>: foo( a : float, b : @b ){}
//        routine<a:float,b:?=>?>: foo( a : float, b ) : @b{}
//
// for named parameter passing: name => value
//    DaoType.name = "string:type" or "string=type"
//    DaoType.tid = DAO_PAR_NAMED or DAO_PAR_DEFAULT
//    DaoType.aux = actual type
*/
struct DaoType
{
	DAO_VALUE_COMMON;

	uchar_t   tid;    /* type id; */
	uchar_t   subtid; /* subtype id; */
	uchar_t   attrib; /* attributes; */
	uchar_t   konst     : 1; /* const type; ::invar is also set to one; */
	uchar_t   invar     : 1; /* invar type; */
	uchar_t   var       : 1; /* var type; */
	uchar_t   valtype   : 1; /* value type */
	uchar_t   variadic  : 1; /* type for variadic tuple or routine */
	uchar_t   realnum   : 1; /* for type of int/float/double */
	uchar_t   noncyclic : 1; /* this type representing non-cyclic data */
	uchar_t   recursive : 1; /* recursive type */
	uchar_t   rntcount  : 4; /* real number type count */
	uchar_t   ffitype   : 4; /* for modules using ffi */
	DString  *name;   /* type name */
	DString  *fname;  /* field name, or parameter name, or original name for enum types */
	DList    *args;   /* type arguments */
	DList    *bases;  /* base types */
	DMap     *mapNames;
	DMap     *interfaces;

	/*
	// Auxiliary data for the type:
	// aux can be the returned type in a routine type;
	// aux can be the parameter type in a named parameter type;
	// aux can be the class object in class or object type;
	// aux can be the DaoCdata type object (DAO_CTYPE) in wrapped C type;
	// aux can be the constant value in a constant value type.
	*/
	DaoValue  *aux;
	DaoValue  *value;    /* default value for the type; */
	DaoType   *quadtype; /* base/const/invar/var type; */
	DaoType   *cbtype;   /* extra type for code block; */

	DaoTypeKernel  *kernel; /* type kernel of built-in or C types; */
	DaoTypeCore    *core;   /* type core; */ 
};

DAO_DLL DaoType *dao_type_none;
DAO_DLL DaoType *dao_type_udf;
DAO_DLL DaoType *dao_type_tht;
DAO_DLL DaoType *dao_type_any;
DAO_DLL DaoType *dao_type_bool;
DAO_DLL DaoType *dao_type_int;
DAO_DLL DaoType *dao_type_float;
DAO_DLL DaoType *dao_type_complex;
DAO_DLL DaoType *dao_type_string;
DAO_DLL DaoType *dao_type_enum;
DAO_DLL DaoType *dao_type_tuple;
DAO_DLL DaoType *dao_type_array;
DAO_DLL DaoType *dao_type_array_empty;
DAO_DLL DaoType *dao_type_list;
DAO_DLL DaoType *dao_type_list_empty;
DAO_DLL DaoType *dao_type_list_any;
DAO_DLL DaoType *dao_type_map;
DAO_DLL DaoType *dao_type_map_empty;
DAO_DLL DaoType *dao_type_map_any;
DAO_DLL DaoType *dao_type_routine;
DAO_DLL DaoType *dao_type_cdata;
DAO_DLL DaoType *dao_type_iterator_int;
DAO_DLL DaoType *dao_type_iterator_any;
DAO_DLL DaoType *dao_type_exception;
DAO_DLL DaoType *dao_type_warning;
DAO_DLL DaoType *dao_type_error;
DAO_DLL DaoType *dao_array_types[DAO_COMPLEX+1];

DAO_DLL DaoType* DaoType_New( const char *name, int tid, DaoValue *aux, DList *args );
DAO_DLL DaoType* DaoType_Copy( DaoType *self );
DAO_DLL void DaoType_Delete( DaoType *self );

DAO_DLL void DaoType_InitDefault( DaoType *self );
DAO_DLL void DaoType_CheckAttributes( DaoType *self );

DAO_DLL DaoType* DaoType_GetBaseType( DaoType *self );
DAO_DLL DaoType* DaoType_GetConstType( DaoType *self );
DAO_DLL DaoType* DaoType_GetInvarType( DaoType *self );
DAO_DLL DaoType* DaoType_GetVarType( DaoType *self );

/* if "self" match to "type": */
DAO_DLL int DaoType_CheckInvarMatch( DaoType *self, DaoType *type, int enforePrimitive );
DAO_DLL int DaoType_MatchTo( DaoType *self, DaoType *type, DMap *defs );
DAO_DLL int DaoType_MatchValue( DaoType *self, DaoValue *value, DMap *defs );
DAO_DLL int DaoType_MatchValue2( DaoType *self, DaoValue *value, DMap *defs );

/* define @X */
DAO_DLL DaoType* DaoType_DefineTypes( DaoType *self, DaoNamespace *ns, DMap *defs );
DAO_DLL DaoType* DaoType_GetCommonType( int type, int subtype );

/* all DAO_THT: @T ... */
DAO_DLL void DaoType_ResetTypeHolders( DaoType *self, DMap *types );
DAO_DLL void DaoType_GetTypeHolders( DaoType *self, DMap *types );
DAO_DLL void DaoType_SetupRecursive( DaoType *self, DaoType *tht, DaoType *root );
DAO_DLL void DaoType_ExportArguments( DaoType *self, DList *args, int noname );

DAO_DLL DaoType* DaoType_GetVariantItem( DaoType *self, int tid );

DAO_DLL int DaoType_IsImmutable( DaoType *self );
DAO_DLL int DaoType_IsPrimitiveOrImmutable( DaoType *self );
DAO_DLL int DaoType_ChildOf( DaoType *self, DaoType *other );
DAO_DLL DaoValue* DaoType_CastToParent( DaoValue *object, DaoType *parent );
DAO_DLL DaoValue* DaoType_CastToDerived( DaoValue *object, DaoType *derived );

DAO_DLL DaoValue* DaoType_FindValue( DaoType *self, DString *name );
DAO_DLL DaoValue* DaoType_FindValueOnly( DaoType *self, DString *name );
DAO_DLL DaoRoutine* DaoType_GetInitor( DaoType *self );
DAO_DLL DaoRoutine* DaoType_GetCastor( DaoType *self );
DAO_DLL DaoRoutine* DaoType_FindFunction( DaoType *self, DString *name );
DAO_DLL DaoRoutine* DaoType_FindFunctionChars( DaoType *self, const char *name );
DAO_DLL DaoRoutine* DaoType_FindOperator( DaoType *self, int opcode );

DAO_DLL DaoType* DaoType_CheckGetField( DaoType *self, DaoString *name );
DAO_DLL DaoValue* DaoType_DoGetField( DaoType *self, DaoValue *object, DaoString *name, DaoProcess *proc );
DAO_DLL int DaoType_CheckSetField( DaoType *self, DaoString *name, DaoType *value );
DAO_DLL int DaoType_DoSetField( DaoType *self, DaoValue *object, DaoString *name, DaoValue *value, DaoProcess *proc );

DAO_DLL DaoTypeCore* DaoType_GetTypeCore( DaoType *self );



/*
// Structure DaoTypeKernel will contain generated wrapping data for the type.
// It is GC collectable, so that it will be automatically deleted once it is
// no longer used, which make it possible to unload external modules automatically.
// Its reference counting is handled and only handled by DaoType.
*/
struct DaoTypeKernel
{
	DAO_VALUE_COMMON;

	uint_t         attribs;
	DMap          *values;
	DMap          *methods;
	DaoType       *abtype; /* The template cdata type for a specialized type; */
	DaoRoutine    *initRoutines;
	DaoNamespace  *nspace;
	DaoTypeTree   *sptree;

	int (*SetupValues) ( DaoNamespace *self, DaoTypeCore *core );
	int (*SetupMethods)( DaoNamespace *self, DaoTypeCore *core );
};

DaoTypeKernel* DaoTypeKernel_New( DaoTypeCore *core );
void DaoTypeKernel_InsertInitor( DaoTypeKernel *self, DaoNamespace *ns, DaoType *host, DaoRoutine *routine );
void DaoTypeKernel_InsertCastor( DaoTypeKernel *self, DaoNamespace *ns, DaoType *host, DaoRoutine *routine );





typedef struct DaoTypeNode DaoTypeNode;

/* Template type parameters structured into a trie: */
struct DaoTypeNode
{
	DaoTypeTree *tree;

	DaoType  *type;   /* parameter type; */
	DaoType  *sptype; /* specialized type; */

	DaoTypeNode  *first; /* the first child node; */
	DaoTypeNode  *last;  /* the last child node; */
	DaoTypeNode  *next;  /* the next sibling node; */
};



/* Template type specialization tree: */
struct DaoTypeTree
{
	DaoTypeNode  *root;

	DList  *holders;  /* type holders; */
	DList  *defaults; /* default types; */
	DList  *sptypes;  /* for GC; */
};

DaoTypeTree* DaoTypeTree_New();
void DaoTypeTree_Delete( DaoTypeTree *self );

int DaoTypeTree_Test( DaoTypeTree *self, DaoType *types[], int count );
void DaoTypeTree_Add( DaoTypeTree *self, DaoType *types[], int count, DaoType *sptype );
DaoType* DaoTypeTree_Get( DaoTypeTree *self, DaoType *types[], int count );

DAO_DLL DaoType* DaoType_Specialize( DaoType *self, DaoType *types[], int count );
DAO_DLL void DaoType_SpecializeMethods( DaoType *self );


#endif
