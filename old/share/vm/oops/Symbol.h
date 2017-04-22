//
// Created by GentlyGuitar on 12/20/2016.
//

#ifndef MAGNOLIA_SYMBOL_H
#define MAGNOLIA_SYMBOL_H

#include <string>

/* Example for legit names:
 * package.class.method([Ljava/lang/String;)V
 */

class LegitMethodName {
    std::string _value;
    std::string _klass;
    std::string _method;
    std::string _sig;
public:
    LegitMethodName(std::string cl, std::string m, std::string sig);
    std::string str();
    std::string getClassPart();
    std::string getMethodPart();
};

#endif //MAGNOLIA_SYMBOL_H
