#include "dialog.h"

#include <QApplication>
#include "/home/viktor/my_projects_qt_2/klass_droby/fraction.h"
using namespace std;
#include <stdexcept>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
//--------------------------------------------------------------------------------------------------------------------
/*    try {
        Fraction f1(1, 88);
        Fraction f2(3, 77);
        Fraction result = f1 + f2;
        //   Fraction result2=std::sqrt(f1);
        std::cout << "Результат сложения: " << result.getNumerator() << "/" << result.getDenominator() << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }  
    */  
//--------------------------------------------------------------------------------------------------------------------   
/*--------------------------------------------------------------------------------------------------------------------*/
    return a.exec();
}
