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
 **                         INT64 (std::int64_t)                        **
 *************************************************************************/

/*************************************************************************
 **                            MATLAB TO C++                            **
 *************************************************************************/

//bool case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, bool& t){
    std::int64_t *pr = (std::int64_t*)mxGetData(mx);
    if(*pr > 0){
        t = true;
    }else{
        t = false;
    }
    WARN_POSSIBLE_LOSS(mxINT64, bool)
}

//char case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, std::int8_t& t){
    convert_from_matlab_impl_common_case<mxINT64, std::int8_t>(mx,t);
}

//unsigned char case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, std::uint8_t& t){
    convert_from_matlab_impl_common_case<mxINT64, std::uint8_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxINT64, std::uint8_t)
}

//short int case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, std::int16_t& t){
    convert_from_matlab_impl_common_case<mxINT64, std::int16_t>(mx,t);
}

//unsigned short int case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, std::uint16_t& t){
    convert_from_matlab_impl_common_case<mxINT64, std::uint16_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxINT64, std::uint16_t)
}

//int case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, std::int32_t& t){
    convert_from_matlab_impl_common_case<mxINT64, std::int32_t>(mx,t);
}

//unsigned int case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, std::uint32_t& t){
    convert_from_matlab_impl_common_case<mxINT64, std::uint32_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxINT64, std::uint32_t)
}

//long int case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, std::int64_t& t){
    convert_from_matlab_impl_common_case<mxINT64, std::int64_t>(mx,t);
}

//unsigned long int case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, std::uint64_t& t){
    convert_from_matlab_impl_common_case<mxINT64, std::uint64_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxINT64, std::uint64_t)
}

//float case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, float& t){
    convert_from_matlab_impl_common_case<mxINT64, float>(mx,t);
}

//double case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, double& t){
    convert_from_matlab_impl_common_case<mxINT64, double>(mx,t);
}

//long double case
template <>
        void convert_from_matlab_impl<mxINT64>(const mxArray* mx, long double& t){
    convert_from_matlab_impl_common_case<mxINT64, long double>(mx,t);
}

/*************************************************************************
 **                            C++ TO MATLAB                            **
 *************************************************************************/

template <>
        void convert_to_matlab(const std::int64_t& t, mxArray*& mx){
    mwSize dims[2];
    dims[0] = 1;
    dims[1] = 1;
    mx = mxCreateNumericArray(2, dims, mxINT64_CLASS, mxREAL);
    std::int64_t* data = (std::int64_t*)mxGetData(mx);
    *data = t;
}