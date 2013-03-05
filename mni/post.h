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


#ifndef MNI_FUNCTION_NAME
#define MNI_FUNCTION_NAME mniFunction
#endif

template <typename Function, typename Tuple, typename... Args2, std::size_t I>
        typename mni::function_traits<Function>::result_type forward_to_function_impl(Tuple& tuple, Function& f, int_<I>, Args2... args2){
    return forward_to_function_impl(tuple, f, int_<I-1>(), std::get<I>(tuple), args2...);
}

template <typename Function, typename Tuple, typename... Args2>
        typename mni::function_traits<Function>::result_type forward_to_function_impl(Tuple& tuple, Function& f, int_<0>, Args2... args2){
    return f(std::get<0>(tuple), args2...);
}

template <typename Function, typename... Args>
        typename mni::function_traits<Function>::result_type forward_to_function(std::tuple<Args...>& tuple, Function& f){
    return forward_to_function_impl(tuple, f, int_<sizeof...(Args)-1>());
}

/* void return type */
template <typename Result_type,
        typename std::enable_if<std::is_void<Result_type>::value, int>::type = 0>
        Result_type mexFunctionImpl(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    typedef mni::function_traits<decltype(MNI_FUNCTION_NAME)>::args_type_tuple Parameters_type_tuple;
    
    Parameters_type_tuple params;
    
    convert_to_tuple(prhs, params);
    
    forward_to_function(params, MNI_FUNCTION_NAME);
    
    /*No returns.*/
}

//single result
template <typename Result_type,
        typename std::enable_if<!std::is_void<Result_type>::value && !mni::is_tuple<Result_type>::value, int>::type = 0>
        void mexFunctionImpl(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    typedef mni::function_traits<decltype(MNI_FUNCTION_NAME)>::args_type_tuple Parameters_type_tuple;
    
    Parameters_type_tuple params;
    
    convert_to_tuple(prhs, params);
    
    Result_type result = forward_to_function(params, MNI_FUNCTION_NAME);
    
    /*A unique return.*/
    
    //no need to test if nlhs >= 1 because there is always an "ans".
    convert_to_matlab(result, plhs[0]);
}

//tuple result
template <typename Result_type,
        typename std::enable_if<!std::is_void<Result_type>::value && mni::is_tuple<Result_type>::value, int>::type = 0>
        void mexFunctionImpl(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    typedef mni::function_traits<decltype(MNI_FUNCTION_NAME)>::args_type_tuple Parameters_type_tuple;
    
    Parameters_type_tuple params;
    
    convert_to_tuple(prhs, params);
    
    Result_type result = forward_to_function(params, MNI_FUNCTION_NAME);
    
    /*Handle the result.*/
    convert_tuple_to_matlab(result, plhs);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    
    typedef mni::function_traits<decltype(MNI_FUNCTION_NAME)>::result_type Result_type;
    
    mexFunctionImpl<Result_type>(nlhs, plhs, nrhs, prhs);
            
}


