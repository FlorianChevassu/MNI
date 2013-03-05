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

/* Example on how to use the MNI framework. */


#include "mni/pre.h"



/* Example on how to extend the functionnalities with user defined classes */
class MyClass{
public:
    MyClass(){
    }
    
    int& get_i(){
        return _i;
    }
    
    int get_i() const{
        return _i;
    }
    
    int& get_j(){
        return _j;
    }
    
    int get_j() const{
        return _j;
    }
    
    void foo(){
        std::cout << "i = " << _i << " and j = " << _j << " !" << std::endl;
    }
private:
    int _i, _j;
};

// /* Function handling the conversion between a matlab array and an object of type MyClass. */
// CONVERT_FROM_MATLAB_STRUCT(MyClass & t){
//     CONVERT_FROM_MATLAB(GET_FIELD(i),t.get_i());
//     CONVERT_FROM_MATLAB(GET_FIELD(j),t.get_j());
// }
// 
// /* Function handling the conversion between an object of type MyClass anda matlab array. */
// CONVERT_TO_MATLAB_STRUCT(const MyClass & t){
//     SET_FIELD(i,t.get_i());
//     SET_FIELD(j,t.get_j());
// }

//equivalents of the above macro-based functions.
template <> void convert_from_matlab_impl<mxSTRUCT>(const mxArray* mx, MyClass & t){
    convert_from_matlab(mxGetField(mx, 0, "i"),t.get_i());
    convert_from_matlab(mxGetField(mx, 0, "j"),t.get_j());
}


template <> void convert_to_matlab(const MyClass & t, mxArray*& mx){
    {
        if(mx==nullptr){ 
            mx = mxCreateStructMatrix(1,1,0,nullptr);
        }
        if(!mxIsStruct(mx)){ 
            std::cout << "mxArray must be a structure array..." << std::endl;
        }else{ 
            if(mxGetFieldNumber(mx, "i") == -1){ 
                mxAddField(mx, "i"); 
            } 
            mxArray* mxField; 
            convert_to_matlab(t.get_i(),mxField); 
            mxSetField(mx, 0, "i", mxField); 
        }
    };
    {
        if(mx==nullptr){ 
            mx = mxCreateStructMatrix(1,1,0,nullptr);
        }
        if(!mxIsStruct(mx)){ 
            std::cout << "mxArray must be a structure array..." << std::endl;
        }else{ 
            if(mxGetFieldNumber(mx, "j") == -1){ 
                mxAddField(mx, "j"); 
            } 
            mxArray* mxField; 
            convert_to_matlab(t.get_j(),mxField); 
            mxSetField(mx, 0, "j", mxField); 
        }
    };
}

MyClass& mniFunction(MyClass& f){
    f.foo();
    return f;
}



/* To use a function that is not named mniFunction, define it via the MNI_FUNCTION_NAME macro */
#define MNI_FUNCTION_NAME mniFunction2
std::tuple<std::string,std::string> mniFunction2(const bool &b, std::string& f){
    std::cout << "f2 = " << f << std::endl;
    return std::make_tuple(f,f);
}

#include "mni/post.h"

