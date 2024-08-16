#include "dialog.h"
#include "ui_dialog.h"
#include "/home/viktor/my_projects_qt_2/klass_droby/fraction.h"
#include <fstream>
#include <iostream>
#include <QFileDialog>
//--------------------------------------------------------------------------------------------------------------------
// переменные:
std::vector<Fraction> list_of_neurons(0 );

std::vector<Fraction> list_of_synapses(0 );
//--------------------------------------------------------------------------------------------------------------------
// функции:

// 1. Функция чтения из бинарного файла в вектор

std::vector<Fraction> readFractionsFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for reading");
    }

    std::vector<Fraction> fractions;
    int numerator, denominator;
    while (file.read(reinterpret_cast<char*>(&numerator), sizeof(numerator))) {
        file.read(reinterpret_cast<char*>(&denominator), sizeof(denominator));
        fractions.emplace_back(numerator, denominator);
    }

    return fractions;
}

/*--------------------------------------------------------------------------------------------------------------------*/
// 2. Функция записи вектора в бинарный файл.
void writeFractionsToFile(const std::string &filename, const std::vector<Fraction> &fractions) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Невозможно открыть файл для записи.");
    }

    for (const auto &fraction : fractions) {
        int numerator = fraction.getNumerator();
        int denominator = fraction.getDenominator();
        file.write(reinterpret_cast<const char*>(&numerator), sizeof(numerator));
        file.write(reinterpret_cast<const char*>(&denominator), sizeof(denominator));
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // перенаправляем вывод из консоли в лог файл
void redirectOutputToFile2(const QString &filePath) {
    // Открываем файл для записи и очищаем его содержимое
    FILE *file = freopen(filePath.toStdString().c_str(), "w", stdout);
    if (!file) {
        std::cerr << "Failed to redirect stdout to file" << std::endl;
        return;
    }

    // Перенаправляем stderr тоже, если нужно
    file = freopen(filePath.toStdString().c_str(), "w", stderr);
    if (!file) {
        std::cerr << "Failed to redirect stderr to file" << std::endl;
        return;
    }

    std::cout << "Console output is now redirected to the log file." << std::endl;
    std::cerr << "Error output is also redirected to the log file." << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*----------------------- конец объявлений функций -------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
/*--------------------------------------------------------------------------------------------------------------------*/
 redirectOutputToFile2("/home/viktor/my_projects_qt_2/Funktsiya_Resheniya_7_drobi/log.log");
/*--------------------------------------------------------------------------------------------------------------------*/
 // NOTE: Диалог выбора файла нейронов
    // Вызов диалога выбора файла
    QString fileName_neyroni = QFileDialog::getOpenFileName(nullptr, "Выберите файл",
                                               "/home/viktor/1_rukoy_GMP/"
                                                            ,  "bin Files (*.bin)");

    // Проверка, был ли файл выбран
    if (!fileName_neyroni.isEmpty()) {
        qDebug() << "Выбранный файл:" << fileName_neyroni;
        // fileName_neyroni
         std::cout << "Выбранный файл:" << fileName_neyroni.toStdString() << std::endl;
    } else {
        qDebug() << "Файл не был выбран.";
    }
    // Преобразование QString в std::string
    std::string stdFileName_neyroni = fileName_neyroni.toStdString();
stdFileName_neyroni="/home/viktor/my_projects_qt_2/sgenerirovaty_neyroni_drobi/neyroni_drobi.bin";
/*--------------------------------------------------------------------------------------------------------------------*/
    // Чтение из файла
    std::vector<Fraction> list_of_neurons =
     readFractionsFromFile(
    // "/home/viktor/my_projects_qt_2/sgenerirovaty_neyroni_drobi/neyroni_drobi.bin"
    stdFileName_neyroni
     );

 int nomer_stroki=0;
     for (const auto &fraction : list_of_neurons) {
        std::cout << "Fraction нейроны"<< nomer_stroki << ": " << fraction.getNumerator() << "/" << fraction.getDenominator() << std::endl;
        nomer_stroki++;
    }
        qDebug() << "Размер list_of_neurons:" << list_of_neurons.size();
    std::cout << "конец чтения нейронов в вектор" << std::endl;
  std::vector<Fraction> list_of_synapses =
     readFractionsFromFile("/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi_drobi/sinapsi_drobi.bin");    
   nomer_stroki=0;  
     for (const auto &fraction : list_of_synapses) {
        std::cout << "Fraction синапсы "<< nomer_stroki << ": " << fraction.getNumerator() << "/" << fraction.getDenominator() << std::endl;
        nomer_stroki++;
    }    
          qDebug() << "Размер list_of_synapses:" << list_of_synapses.size();
    std::cout << "Конец чтения синапсов в вектор." << std::endl;  
/*--------------------------------------------------------------------------------------------------------------------*//*
 * // NOTE: отладка-проверка
Fraction f1(186, -8882); // Создаем дробь 1/2

    Fraction result = f1.sigmoid(); // Вызываем сигмоидальную функцию

    std::cout << "Сигмоид " << f1.getNumerator() << "/" << f1.getDenominator() 
              << " примерно равен " << result.getNumerator() << "/" << result.getDenominator() << std::endl; */   
    
/*--------------------------------------------------------------------------------------------------------------------*/    
}

Dialog::~Dialog()
{
    delete ui;
}
