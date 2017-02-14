//
//  IllegalParameterValue.hpp
//  DataStructures
//
//  Created by 刘微 on 17/2/14.
//  Copyright © 2017年 刘微. All rights reserved.
//

#ifndef IllegalParameterValue_hpp
#define IllegalParameterValue_hpp

#include <iostream>


/******************** 异常类  *******************/

namespace LWTL {

    class IllegalParameterValue {

    public:

        //构造函数
        IllegalParameterValue() : message("illegal parameter value") {};
        IllegalParameterValue(std::string theMessage) : message(theMessage) {};

        //输出错误信息
        void outputMessage() const;
        
    private:
        std::string message;
    };
}


#endif /* IllegalParameterValue_hpp */
