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
 **                          CHAR (std::string)                         **
 *************************************************************************/

/*************************************************************************
 **                            MATLAB TO C++                            **
 *************************************************************************/

//bool case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, bool& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  if(strcmp(buf,"true")==0){
        t = true;
  }else if(strcmp(buf,"false")==0){
        t = false;
  }else{
      mexWarnMsgTxt("Unable to convert matlab string to bool...");
  }
}

//char case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, std::int8_t& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atoi(buf);
}

//unsigned char case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, std::uint8_t& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atoi(buf);
}

//short int case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, std::int16_t& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atoi(buf);
}

//unsigned short int case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, std::uint16_t& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atoi(buf);
}

//int case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, std::int32_t& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atoi(buf);
}

//unsigned int case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, std::uint32_t& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atol(buf);//long case because max(uint32) > max(int)
}

//long int case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, std::int64_t& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atol(buf);
}

//unsigned long int case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, std::uint64_t& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atoll(buf);
}

//float case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, float& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atof(buf);
}

//double case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, double& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atof(buf);
}

//long double case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, long double& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = std::atof(buf);
}


//std::string case
template <>
        void convert_from_matlab_impl<mxCHAR>(const mxArray* mx, std::string& t){
  char *buf;
  mwSize buflen; 
  
  /* Allocate enough memory to hold the converted string. */ 
  buflen = mxGetNumberOfElements(mx) + 1;
  buf = (char *)mxCalloc(buflen, sizeof(char));
  
  /* Copy the string data from string_array_ptr and place it into buf. */ 
  if (mxGetString(mx, buf, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  t = buf;
}

/*************************************************************************
 **                            C++ TO MATLAB                            **
 *************************************************************************/

template <>
        void convert_to_matlab(const std::string& t, mxArray*& mx){
    mwSize dims[2];
    dims[0] = 1;
    dims[1] = 1;
    mx = mxCreateString(t.c_str());
}