#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Declaro el vector para añadir las cadenas del token y error para luego imprimir en el plantext
    QVector<QString> vectorError = {},
                     vectorToken = {},
                     vectorPalabrasReservadas = {"and", "or", "not", "AND", "OR", "NOT", "IF", "WHILE", "ENDIF",
                                                 "UNTIL", "THEN", "BOOLEAN", "REPEAT", "VAR", "ELSE", "ENDO",
                                                 "FLOAT", "INT", "STRING", "CHAR", "if", "while", "endif", "until",
                                                 "then", "boolean", "repeat", "var", "else", "endo", "float", "int",
                                                 "string", "char"};



private slots:
    void on_btnAbrirDocumento_clicked();

    void on_btnCerrar_clicked();

    void on_btnLimpiar_clicked();

    void on_btnAnalizar_clicked();

private:
    Ui::MainWindow *ui;

private: void Token(int e, QString valor);
private: void Error(int e, QString valor);
private: void AnalisisLexico();
private: void AnalisisSintactico(int estado, QString valor);
};
#endif // MAINWINDOW_H

