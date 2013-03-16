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
 **                            SINGLE (float)                           **
 *************************************************************************/

/*************************************************************************
 **                            MATLAB TO C++                            **
 *************************************************************************/

//bool case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, bool& t){
    float *pr = (float *)mxGetData(mx);
    if(*pr > 0){
        t = true;
    }else{
        t = false;
    }
    WARN_POSSIBLE_LOSS(mxSINGLE, bool)
}

//char case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, std::int8_t& t){
    convert_from_matlab_impl_common_case<mxSINGLE, std::int8_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxSINGLE, std::int8_t)
}

//unsigned char case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, std::uint8_t& t){
    convert_from_matlab_impl_common_case<mxSINGLE, std::uint8_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxSINGLE, std::uint8_t)
}

//short int case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, std::int16_t& t){
    convert_from_matlab_impl_common_case<mxSINGLE, std::int16_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxSINGLE, std::int16_t)
}

//unsigned short int case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, std::uint16_t& t){
    convert_from_matlab_impl_common_case<mxSINGLE, std::uint16_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxSINGLE, std::uint16_t)
}

//int case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, std::int32_t& t){
    convert_from_matlab_impl_common_case<mxSINGLE, std::int32_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxSINGLE, std::int32_t)
}

//unsigned int case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, std::uint32_t& t){
    convert_from_matlab_impl_common_case<mxSINGLE, std::uint32_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxSINGLE, std::uint32_t)
}

//long int case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, std::int64_t& t){
    convert_from_matlab_impl_common_case<mxSINGLE, std::int64_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxSINGLE, std::int64_t)
}

//unsigned long int case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, std::uint64_t& t){
    convert_from_matlab_impl_common_case<mxSINGLE, std::uint64_t>(mx,t);
    WARN_POSSIBLE_LOSS(mxSINGLE, std::uint64_t)
}

//float case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, float& t){
    convert_from_matlab_impl_common_case<mxSINGLE, float>(mx,t);
}

//double case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, double& t){
    convert_from_matlab_impl_common_case<mxSINGLE, double>(mx,t);
}

//long double case
template <>
        void convert_from_matlab_impl<mxSINGLE>(const mxArray* mx, long double& t){
    convert_from_matlab_impl_common_case<mxSINGLE, long double>(mx,t);
}

/*************************************************************************
 **                            C++ TO MATLAB                            **
 *************************************************************************/

template <>
        void convert_to_matlab(const float& t, mxArray*& mx){
    mwSize dims[2];
    dims[0] = 1;
    dims[1] = 1;
    mx = mxCreateNumericArray(2, dims, mxSINGLE_CLASS, mxREAL);
    float* data = (float*)mxGetData(mx);
    *data = t;
}