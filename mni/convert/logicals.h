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


/*************************************************************************
 **                           LOGICALS (bool)                           **
 *************************************************************************/

/*************************************************************************
 **                            MATLAB TO C++                            **
 *************************************************************************/

//bool case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, bool& t){
    convert_from_matlab_impl_common_case<mxLOGICAL, bool>(mx,t);
}

//char case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, std::int8_t& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1;
    }else{
        t = 0;
    }
    WARN_BAD_TYPE(mxLOGICAL, std::int8_t)
}

//unsigned char case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, std::uint8_t& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1;
    }else{
        t = 0;
    }
    WARN_BAD_TYPE(mxLOGICAL, std::uint8_t)
}

//short int case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, std::int16_t& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1;
    }else{
        t = 0;
    }
    WARN_BAD_TYPE(mxLOGICAL, std::int16_t)
}

//unsigned short int case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, std::uint16_t& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1;
    }else{
        t = 0;
    }
    WARN_BAD_TYPE(mxLOGICAL, std::uint16_t)
}

//int case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, std::int32_t& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1;
    }else{
        t = 0;
    }
    WARN_BAD_TYPE(mxLOGICAL, std::int32_t)
}

//unsigned int case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, std::uint32_t& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1;
    }else{
        t = 0;
    }
    WARN_BAD_TYPE(mxLOGICAL, std::uint32_t)
}

//long int case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, std::int64_t& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1;
    }else{
        t = 0;
    }
    WARN_BAD_TYPE(mxLOGICAL, std::int64_t)
}

//unsigned long int case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, std::uint64_t& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1;
    }else{
        t = 0;
    }
    WARN_BAD_TYPE(mxLOGICAL, std::uint64_t)
}

//float case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, float& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1.0f;
    }else{
        t = 0.0f;
    }
    WARN_BAD_TYPE(mxLOGICAL, float)    
}

//double case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, double& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1.0;
    }else{
        t = 0.0;
    }
    WARN_BAD_TYPE(mxLOGICAL, double)
}

//long double case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, long double& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = 1.0;
    }else{
        t = 0.0;
    }
    WARN_BAD_TYPE(mxLOGICAL, long double)
}

//string case
template <>
        void convert_from_matlab_impl<mxLOGICAL>(const mxArray* mx, std::string& t){
    mxLogical *pr = (mxLogical *)mxGetData(mx);
    if (*pr){
        t = "true";
    }else{
        t = "false";
    }
    WARN_BAD_TYPE(mxLOGICAL, std::string)
}

/*************************************************************************
 **                            C++ TO MATLAB                            **
 *************************************************************************/

template <>
        void convert_to_matlab(const bool& t, mxArray*& mx){
    mwSize dims[2];
    dims[0] = 1;
    dims[1] = 1;
    mx = mxCreateNumericArray(2, dims, mxLOGICAL_CLASS, mxREAL);
    bool* data = (bool*)mxGetData(mx);
    *data = t;
}