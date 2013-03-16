// Copyright 2013, CHEVASSU Florian <chevassu.florian at gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "mex.h"
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <type_traits>
#include <string>
#include <cstring>
#include <cstdint>//for fixed width integer types


/*************************************************************************
 **                       MATLAB DATA TYPES                             **
 *************************************************************************/

struct mxINT8{
    typedef std::int8_t CType;
    static const std::string name;
};
const std::string mxINT8::name = "mxINT8";

struct mxUINT8{
    typedef std::uint8_t CType;
    static const std::string name;
};
const std::string mxUINT8::name = "mxUINT8";

struct mxINT16{
    typedef std::int16_t CType;
    static const std::string name;
};
const std::string mxINT16::name = "mxINT16";

struct mxUINT16{
    typedef std::uint16_t CType;
    static const std::string name;
};
const std::string mxUINT16::name = "mxUINT16";

struct mxINT32{
    typedef std::int32_t CType;
    static const std::string name;
};
const std::string mxINT32::name = "mxINT32";

struct mxUINT32{
    typedef std::uint32_t CType;
    static const std::string name;
};
const std::string mxUINT32::name = "mxUINT32";

struct mxINT64{
    typedef std::int64_t CType;
    static const std::string name;
};
const std::string mxINT64::name = "mxINT64";

struct mxUINT64{
    typedef std::uint64_t CType;
    static const std::string name;
};
const std::string mxUINT64::name = "mxUINT64";

struct mxSINGLE{
    typedef float CType;
    static const std::string name;
};
const std::string mxSINGLE::name = "mxSINGLE";

struct mxDOUBLE{
    typedef double CType;
    static const std::string name;
};
const std::string mxDOUBLE::name = "mxDOUBLE";

struct mxLOGICAL{
    typedef bool CType;
    static const std::string name;
};
const std::string mxLOGICAL::name = "mxLOGICAL";

struct mxCHAR{
    typedef std::string CType;
    static const std::string name;
};
const std::string mxCHAR::name = "mxCHAR";

struct mxSTRUCT{
    typedef void CType;//?
    static const std::string name;
};
const std::string mxSTRUCT::name = "mxSTRUCT";

struct mxCELL{
    typedef void CType;//?
    static const std::string name;
};
const std::string mxCELL::name = "mxCELL";

struct mxUNKNOWN{
    typedef void CType;//?
    static const std::string name;
};
const std::string mxUNKNOWN::name = "mxUNKNOWN";

/*  TUPLE CONVERSION HANDLING    */

//compile time integer
template<std::size_t> struct int_{};

template <typename... Args, std::size_t I>
void convert_to_tuple_impl(const mxArray *prhs[], std::tuple<Args...>& tuple, int_<I>){
    convert_to_tuple_impl(prhs, tuple, int_<I-1>());
    convert_from_matlab(prhs[I], std::get<I>(tuple));
}

template <typename... Args>
void convert_to_tuple_impl(const mxArray *prhs[], std::tuple<Args...>& tuple, int_<0>){
    convert_from_matlab(prhs[0], std::get<0>(tuple));
}

template <typename... Args>
void convert_to_tuple(const mxArray *prhs[], std::tuple<Args...>& tuple){
    convert_to_tuple_impl(prhs, tuple, int_<sizeof...(Args)-1>());
}

/*************************************************************************
 **                        CONVERT FUNCTIONS                            **
 *************************************************************************/

//general case : we do not have a correct conversion available...
template <class M, class C>
        void convert_from_matlab_impl(const mxArray* mx, C& t){
    std::ostringstream oStream;
    oStream << "Cannot convert a Matlab " << M::name << " to a C++ " << typeid(C).name() << "." << std::endl;
    mexErrMsgTxt(oStream.str().c_str());
}



//Case working in general case, when implicit conversion between T and C_type works.
template <typename M, typename T>
        void convert_from_matlab_impl_common_case(const mxArray* mx, T& t){
    typedef typename M::CType C_type ;
    C_type *pr = (C_type *)mxGetData(mx);
    t = *pr;
}

template <typename T>
        void convert_to_matlab(const T& t, mxArray*& mx){
    std::ostringstream oStream;
    oStream << "Cannot convert a C++ " << typeid(T).name() << " to a Matlab type." << std::endl;
    mexWarnMsgTxt(oStream.str().c_str());
}



template <typename... Args, std::size_t I>
void convert_tuple_to_matlab_impl(const std::tuple<Args...>& tuple, mxArray *plhs[], int_<I>){
    convert_tuple_to_matlab_impl(tuple, plhs, int_<I-1>());
    convert_to_matlab(std::get<I>(tuple), plhs[I]);
}

template <typename... Args>
void convert_tuple_to_matlab_impl(const std::tuple<Args...>& tuple, mxArray *plhs[], int_<0>){
    convert_to_matlab(std::get<0>(tuple), plhs[0]);
}

//here, I represents nlhs
template <typename... Args, std::size_t NLHS>
        void convert_tuple_to_matlab(const std::tuple<Args...>& tuple, mxArray**& plhs, int_<NLHS>){
    convert_tuple_to_matlab_impl(tuple, plhs, int_<(sizeof...(Args)>NLHS) ? NLHS-1 : sizeof...(Args)-1>());
}

/*          WARNING UTILITIES           */

#define WARN(text) mexWarnMsgTxt(#text);

/*      warn conversions that may loss data, e.g. 
 *      convert<mxSINGLE>(int&, mxArray*);, as a float is more precise than an int.
 */
#define WARN_POSSIBLE_LOSS_IN_CONVERSION

#ifdef WARN_POSSIBLE_LOSS_IN_CONVERSION
#define WARN_POSSIBLE_LOSS(mtype,ctype) WARN(WARNING : Converting a Matlab mtype to a C++ ctype : possible loss of data)
#else
#define WARN_POSSIBLE_LOSS(mtype,ctype)
#endif



#define CONVERT_FROM_MATLAB_STRUCT(Cpp_class_def) \
template <> void convert_from_matlab_impl<mxSTRUCT>(const mxArray* mx, Cpp_class_def)

#define GET_FIELD(field_name) mxGetField(mx, 0, #field_name)
#define CONVERT_FROM_MATLAB(...) convert_from_matlab(__VA_ARGS__)


#define CONVERT_TO_MATLAB_STRUCT(Cpp_class_def)\
template <> void convert_to_matlab(Cpp_class_def, mxArray*& mx)

#define CREATE_MATLAB_STRUCT() mx = mxCreateStructMatrix(1,1,0,nullptr)

#define CREATE_FIELD(name) mxAddField(mx, #name)

#define SET_FIELD(name, value) {\
if(mx==nullptr){\
    mx = mxCreateStructMatrix(1,1,0,nullptr);\
}\
if(!mxIsStruct(mx)){\
        std::cout << "mxArray must be a structure array..." << std::endl;\
}else{\
    if(mxGetFieldNumber(mx, #name) == -1){\
        mxAddField(mx, #name);\
    }\
    mxArray* mxField;\
    convert_to_matlab(value,mxField);\
    mxSetField(mx, 0, #name, mxField);\
    }\
}


#include "convert/logicals.h"
#include "convert/int8.h"
#include "convert/uint8.h"
#include "convert/int16.h"
#include "convert/uint16.h"
#include "convert/int32.h"
#include "convert/uint32.h"
#include "convert/int64.h"
#include "convert/uint64.h"
#include "convert/single.h"
#include "convert/double.h"
#include "convert/string.h"



/*************************************************************************
 **                    General switch statement                         **
 *************************************************************************/
template <typename T>
        void convert_from_matlab(const mxArray* mx, T& t){
    mxClassID category = mxGetClassID(mx);
    switch (category){
        case mxLOGICAL_CLASS:
            convert_from_matlab_impl<mxLOGICAL, T>(mx, t);
            break;
        case mxINT8_CLASS:
            convert_from_matlab_impl<mxINT8, T>(mx, t);
            break;
        case mxUINT8_CLASS:
            convert_from_matlab_impl<mxUINT8, T>(mx, t);
            break;
        case mxINT16_CLASS:
            convert_from_matlab_impl<mxINT16, T>(mx, t);
            break;
        case mxUINT16_CLASS:
            convert_from_matlab_impl<mxUINT16, T>(mx, t);
            break;
        case mxINT32_CLASS:
            convert_from_matlab_impl<mxINT32, T>(mx, t);
            break;
        case mxUINT32_CLASS:
            convert_from_matlab_impl<mxUINT32, T>(mx, t);
            break;
        case mxINT64_CLASS:
            convert_from_matlab_impl<mxINT64, T>(mx, t);
            break;
        case mxUINT64_CLASS:
            convert_from_matlab_impl<mxUINT64, T>(mx, t);
            break;
        case mxSINGLE_CLASS:
            convert_from_matlab_impl<mxSINGLE, T>(mx, t);
            break;
        case mxDOUBLE_CLASS:
            convert_from_matlab_impl<mxDOUBLE, T>(mx, t);
            break;
        case mxCHAR_CLASS:    
            convert_from_matlab_impl<mxCHAR, T>(mx, t);   
            break;
        case mxSTRUCT_CLASS:
            convert_from_matlab_impl<mxSTRUCT,T>(mx, t);  
            break;
        case mxCELL_CLASS:    
//             convert_from_matlab_impl<mxCELL,T>(mx, t);       
            break;
        case mxUNKNOWN_CLASS:
            mexWarnMsgTxt("On connait pas la classe... ca craint");
            mexWarnMsgIdAndTxt("MATLAB:explore:unknownClass", "Unknown class.");                       
            break;
        default:
            mexWarnMsgTxt("Matlab type not valid...");
            break;
    }
    
}


