#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

#include <vector>
#include<algorithm>
#include <iostream>

#include <stack>

using namespace std;
//int estado = 0, columna = 0;
//int contadorCadena = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------------------------------------
//Evento Botón Abrir Archivo
void MainWindow::on_btnAbrirDocumento_clicked()
{
    QString nombreArchivo = QFileDialog::getOpenFileName(this, "Abrir Archivo",
                            "C:\\Users\\danie\\OneDrive\\Documentos\\Analizador\\Archivos para analizar",
                            "Text files (*.lya)");
    QFile archivo(nombreArchivo);

    if(!archivo.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Peligro ALV", "Archivo no abierto.", nombreArchivo);
    }
    QTextStream in(&archivo);
    QString texto = in.readAll();
    ui->ptTexto->setPlainText(texto);//Lo que está en el archivo lo ponemos en el TextArea
    archivo.close();
}
//-------------------------------------------------------------------------------------------------------------------------
//Evento Botón Cerrar Frame
void MainWindow::on_btnCerrar_clicked()
{
    exit(1);
}
//-------------------------------------------------------------------------------------------------------------------------
//Evento Botón Limpiar Info de Text Plane (Documento, Token, Error)
void MainWindow::on_btnLimpiar_clicked()
{
    //Pon contenido vacío en mi textPlane Archivo
    ui ->ptTexto ->setPlainText("");
    //Pon contenido vacío en mi textPlane Tokne
    ui -> ptAnalisisToken ->setPlainText("");
    //Pon contenido vacío en mi textPlane Error
    ui -> ptAnalisisError ->setPlainText("");
    //Pon contenido vacío en mi textPlane Proceso Analisis
    ui -> ptProcesoAnalisis ->setPlainText("");
    //estado = 0;
    //columna = 0;
    //contadorCadena = 0;
}
//-------------------------------------------------------------------------------------------------------------------------
//Matriz
//int matriz[Estados][Columnas]
int matriz[20][31] =
{

    {1      ,106	,2  	,3  	,114   	,112	,110	,111	,113	,115	,116	,117	,119	,120	,121	,122	,123	,124	,12	    ,12	    ,14	    ,512	 ,12	,12	    ,8	    ,10	    ,0	    ,0	    ,0	    ,514 ,514}, //q0
    {100	,102	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100	,100 ,100}, //q1
    {105	,103	,104	,104	,104	,104	,104	,104	,104	,104	,104	,104	,104	,104	,104	,104	,104	,104	,127	,127	,104	,104	,104	,104	,104	,104	,104	,104	,104	,104 ,104}, //q2
    {118	,107	,118	,118	,118	,118	,118	,118	,118	,118	,118	,118	,118	,118	,118	,118	,118	,118	,127	,127	,118	,118	,118	,118	,118	,118	,118	,118	,118	,118 ,118}, //q3
    {114	,114	,114	,114	,5	    ,6	    ,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114	,114 ,114}, //q4
    {5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5      ,5      ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,5	    ,108	,5	    ,5   ,5  }, //q5
    {6	    ,6	    ,6	    ,6	    ,6	    ,7	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6      ,6      ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6	    ,6   ,6  }, //q6
    {510	,510	,510	,510	,109	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510	,510 ,510}, //q7
    {9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,9	    ,515	,9	    ,9	    ,9	    ,9	    ,9   ,515}, //q8
    {516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,516	,125	,516	,516	,516	,516	,516 ,516}, //q9
    {10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,10	    ,11	    ,10	    ,10	    ,10	    ,10  ,10}, //q10
    {126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,126	,10	    ,126	,126	,126	,126 ,126}, //q11
    {127	,127	,127	,127	,127	,127	,127	,127	,127	,127	,127	,127	,127	,127	,127	,127	,127	,127	,12	    ,12	    ,12	    ,13	    ,127	,127	,127	,127	,127	,127	,127	,127 ,127}, //q12
    {513	,513	,513	,513	,513	,513	,513	,513	,513	,513	,513	,513	,513	,513	,513	,513	,513	,513	,12	    ,12	    ,12	    ,513	,513	,513	,513	,513	,513	,513	,513	,513 ,513}, //q13
    {128	,128	,128	,128	,128	,128	,128	,128	,128	,128	,15	    ,128	,128	,128	,128	,128	,128	,128	,128	,128	,14	    ,128	,128	,128	,128	,128	,128	,128	,128	,128 ,128}, //q14
    {504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,504	,16	    ,504	,504	,504	,504	,504	,504	,504	,504	,504 ,504}, //q15
    {129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129	,129 	,129	,17	    ,17	    ,129	,129	,129	,129	,129	,129 ,129}, //q16
    {506	,506	,506	,506	,506	,506	,19	    ,19	    ,506	,506	,506	,506	,506	,506	,506	,506	,506	,506	,506	,506	,18	    ,506	,506	,506	,506	,506	,506	,506	,506	,506 ,506}, //q17
    {130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,130	,18	    ,130	,130	,130	,130	,130	,130	,130	,130	,130 ,130}, //q18
    {505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,505	,18	    ,505	,505	,505	,505	,505	,505	,505	,505	,505 ,505}  //q19
    //>	    =	    <	    :	    /	    *	    +	    -	    %	    ;	    .	    ,Coma	{	    }	    [	    ]	    (	    )	    L	    l	    d	    _	    E	    e	    '	    "	    \b	    \n	    \t	    Dif    EOF
    //0	    1	    2	    3	    4	    5	    6	    7	    8	    9	    10  	11	    12  	13	    14	    15	    16	    17	    18	    19	    20	    21	    22	    23	    24	    25	    26	    27	    28	    29     30
};

//-------------------------------------------------------------------------------------------------------------------------
//Método Relaciona
/*  Este método recibe un dato de tipo caracter que analiza para luego retornarnos un valor entero.*/
int Relaciona(char caracter)
{
    //Dígitos
    /*Si el caracter que recibe el método es un número entre el 0 y el 9,
     * entonces es un dígito y retorna el estado 0.*/
    if(caracter >= char(48) && caracter <= char(57)) //Código ASCII
    {
        return 20;
    }
    //Letra Minuscula
    /*Si el caracter que recibe el método es una letra minúscula entre la a y la z,
     * entonces es un L y retorna la columna 19.
       En este caso excluyo las letras E y e para que lo detecte la notación cinetífica, por eso
       el código ASCII va de un rango a otro excluyendolas.*/
    if (int(caracter) >= 97 && int(caracter) <= 122)
    {
        return 19;
    }
    //Letra Mayuscula
    /*Si el caracter que recibe el método es una letra mayúscula entre la A y la Z,
     * entonces es un L y retorna la columna 18.
       En este caso excluyo las letras E y e para que lo detecte la notación cinetífica, por eso
       el código ASCII va de un rango a otro excluyendolas.*/
    if (int(caracter) >= 65 && int(caracter) <= 90)
    {
        return 18;
    }

    //Mismo procesos pero para los siguientes caracteres.
    switch(caracter)
    {
        case '>':       //Si es un > Retorna la columna 0.
            return 0;
        break;
        case '=':       //Si es un = Retorna la columna 1.
            return 1;
        break;
        case '<':       //Si es un < Retorna la columna 2.
            return 2;
        break;
        case ':':       //Si es un : Retorna la columna 3.
            return 3;
        break;
        case '/':       //Si es un / Retorna la columna 4.
            return 4;
        break;
        case '*':       //Si es un * Retorna la columna 5.
            return 5;
        break;
        case '+':       //Si es un + Retorna la columna 6.
            return 6;
        break;
        case '-':       //Si es un - Retorna la columna 7.
            return 7;
        break;
        case '%':       //Si es un % Retorna la columna 8.
            return 8;
        break;
        case ';':       //Si es un ; Retorna la columna 9.
            return 9;
        break;
        case '.':       //Si es un . Retorna la columna 10.
            return 10;
        break;
        case ',':       //Si es un , Retorna la columna 11.
            return 11;
        break;
        case '{':       //Si es un { Retorna la columna 12.
            return 12;
        break;
        case '}':       //Si es un } Retorna la columna 13.
            return 13;
        break;
        case '[':       //Si es un [ Retorna la columna 14.
            return 14;
        break;
        case ']':       //Si es un ] Retorna la columna 15.
            return 15;
        break;
        case '(':       //Si es un ( Retorna la columna 16.
            return 16;
        break;
        case ')':       //Si es un ) Retorna la columna 17.
            return 17;
        break;
        case '_':       //Si es un _ Retorna la columna 21.
            return 21;
        break;
        case 'E':       //Si es un E Retorna la columna 22.
            return 22;
        break;
        case 'e':       //Si es un e Retorna la columna 23.
            return 23;
        break;
        //comilla simple
        case char(39):  //Si es un ' Retorna la columna 24.
            return 24;
        break;
        //comilla doble
        case char(34):  //Si es un " Retorna la columna 25.
            return 25;
        break;
        case char(32):      //Si es un \b Retorna la columna 26.
            return 26;
        break;
        case char(10):      //Si es un \n Retorna la columna 27.
            return 27;
        break;
        case char(9):      //Si es un \t Retorna la columna 28.
            return 28;
        break;
    }
    if(caracter == '\0'){
        return 30; // Si es algo diferente a lo que tengo establecido en mi lenguaje
                   //retorna el 30 valor númerico que representa el EOF (da fin al autómata).
    }    
    //Algo diferente que no sea EOF.
    return 29;
}
//-------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------
//Método de busqueda para palabras reservadas
bool existeEnVector(QVector<QString> v, QString valor)
{
    return find(v.begin(), v.end(), valor) != v.end();
}
//-------------------------------------------------------------------------------------------------------------------------
//Método Token
void MainWindow::Token(int estado, QString valor)
{        
    switch(estado)
    {        
        //Estado de aceptación 100: Signo mayor qué.
        case 100:            
            vectorToken.push_back("Gramema: Signo mayor qué - Lexema: " + valor);
        break;
        //Estado de aceptación 102: Signo menor qué.
        case 102:
            vectorToken.push_back("Gramema: Signo menor qué - Lexema: " + valor);
        break;
        //Estado de aceptación 103: Signo menor o igual qué.
        case 103:
            vectorToken.push_back("Gramema: Signo menor o igual qué - Lexema: " + valor);
        break;
        //Estado de aceptación 104: Signo menor qué.
        case 104:
            vectorToken.push_back("Gramema: Signo menor qué - Lexema: " + valor);
        break;
        //Estado de aceptación 105: Signo  diferente de.
        case 105:
            vectorToken.push_back("Gramema: Signo  diferente de - Lexema: " + valor);
        break;
        //Estado de aceptación 106: Signo igual.
        case 106:
            vectorToken.push_back("Gramema: Signo igual - Lexema: " + valor);
        break;
        //Estado de aceptación 107: Signo asignación.
        case 107:
            vectorToken.push_back("Gramema: Signo asignación - Lexema: " + valor);
        break;
        //Estado de aceptación 108: Comentario de línea.
        case 108:
            vectorToken.push_back("Gramema: Comentario de línea - Lexema: " + valor);
        break;
        //Estado de aceptación 109: Comentario de bloque.
        case 109:
            vectorToken.push_back("Gramema: Comentario de bloque - Lexema: " + valor);
        break;
        //Estado de aceptación 110: Suma.
        case 110:
            vectorToken.push_back("Gramema: Operador Aritmético Suma - Lexema: " + valor);
        break;
        //Estado de aceptación 111: Resta.
        case 111:
            vectorToken.push_back("Gramema: Operador Aritmético Resta - Lexema: " + valor);
        break;
        //Estado de aceptación 112: Multiplicación.
        case 112:
            vectorToken.push_back("Gramema: Operador Aritmético Multiplicación - Lexema: " + valor);
        break;
        //Estado de aceptación 113: Módulo.
        case 113:
            vectorToken.push_back("Gramema: Operador Aritmético Módulo - Lexema: " + valor);
        break;
        //Estado de aceptación 114: División.
        case 114:
            vectorToken.push_back("Gramema: Operador Aritmético División - Lexema: " + valor);
        break;
        //Estado de aceptación 115: Punto y coma.
        case 115:
            vectorToken.push_back("Gramema: Signo de Puntuación Punto y coma - Lexema: " + valor);
        break;
        //Estado de aceptación 116: Punto
        case 116:
            vectorToken.push_back("Gramema: Signo de Puntuación Punto - Lexema: " + valor);
        break;
        //Estado de aceptación 117: Coma
        case 117:
            vectorToken.push_back("Gramema: Signo de Puntuación Coma - Lexema: " + valor);
        break;
        //Estado de aceptación 118: Signo de puntuación.
        case 118:
            vectorToken.push_back("Gramema: Signo de Puntuación Dos Puntos - Lexema: " + valor);
        break;
        //Estado de aceptación 119: Llave que abre.
        case 119:
            vectorToken.push_back("Gramema: Signo de Agrupación Llave que abre  - Lexema: " + valor);
        break;
        //Estado de aceptación 120: Llave que cierra.
        case 120:
            vectorToken.push_back("Gramema: Signo de Agrupación Llave que cierra  - Lexema: " + valor);
        break;
        //Estado de aceptación 121: Corchete que abre.
        case 121:
            vectorToken.push_back("Gramema: Signo de Agrupación Corchete que abre  - Lexema: " + valor);
        break;
        //Estado de aceptación 122: Corchete que cierra.
        case 122:
            vectorToken.push_back("Gramema: Signo de Agrupación Corchete que cierra  - Lexema: " + valor);
        break;
        //Estado de aceptación 123: Parentesis que abre.
        case 123:
            vectorToken.push_back("Gramema: Signo de Agrupación Parentesis que abre  - Lexema: " + valor);
        break;
        //Estado de aceptación 124: Parentesis que cierra.
        case 124:
            vectorToken.push_back("Gramema: Signo de Agrupación Parentesis que cierra  - Lexema: " + valor);
        break;
        //Estado de aceptación 125: Cosntante caracter.
        case 125:
            vectorToken.push_back("Gramema: Constante Caracter  - Lexema: " + valor);
        break;
        //Estado de aceptación 126: Constante String.
        case 126:
            vectorToken.push_back("Gramema: Constante String  - Lexema: " + valor);
        break;
        //Estado de aceptación 127: Identificador.
        case 127:
        //Aqui verifico si es palabra reservada o id.
            if (existeEnVector(vectorPalabrasReservadas, valor))
            {
                vectorToken.push_back("Gramema: Palabra Reservada  - Lexema: " + valor);
            }
            else
            {
                vectorToken.push_back("Gramema: Identificador  - Lexema: " + valor);
            }
            //vectorToken.push_back("Gramema: Identificador  - Lexema: " + valor);
        break;
        //Estado de aceptación 128: Constante entera.
        case 128:
            vectorToken.push_back("Gramema: Constante Entera  - Lexema: " + valor);
        break;
        //Estado de aceptación 129: Constante Flotante.
        case 129:
            vectorToken.push_back("Gramema: Constante Flotante  - Lexema: " + valor);
        break;
        //Estado de aceptación 130: Constante N.C.
        case 130:
            vectorToken.push_back("Gramema: Constante N.C  - Lexema: " + valor);
        break;
    }
}
//-------------------------------------------------------------------------------------------------------------------------
//Método Error
void MainWindow::Error(int e, QString valor)
{
    switch(e)
    {
        //Error 504: Esperaba un dígito después del punto.
        case 504:
            vectorError.push_back("Error 504: El Lexema -> " + valor + ". Esperaba un dígito después del punto.");
        break;
        //Error 505: Esperaba un dígito después del + o un -.
        case 505:
            vectorError.push_back("Error 505: El Lexema -> " + valor + ". Esperaba un dígito después del + o un -.");
        break;
        //Error 506: Esperaba un dígito después de un signo + o -.
        case 506:
            vectorError.push_back("Error 506: El Lexema -> " + valor + ". Esperaba un dígito después de un signo + o -.");
        break;
        //Error 510: Esperaba una diagonal para terminar el comentario de bloque.
        case 510:
            vectorError.push_back("Error 510: El Lexema -> " + valor + ". Esperaba una diagonal para terminar el comentario de bloque.");
        break;
        //Error 512: Un identificador no puede iniciar con _.
        case 512:
            vectorError.push_back("Error 512: El Lexema -> " + valor + ". Un identificador no puede iniciar con _.");
        break;
        //Error 513: Esperaba una letra o un dígito.
        case 513:
            vectorError.push_back("Error 513: El Lexema -> " + valor + ". Esperaba una letra o un dígito.");
        break;
        //Error 514: Token invalido.
        case 514:
            vectorError.push_back("Error 514: El Lexema -> " + valor + ". Token invalido.");
        break;
        //Error 515: Después de la comilla simple debe venir algo más y finalizar con comilla simple.
        case 515:
            vectorError.push_back("Error 514: El Lexema -> " + valor + ". Después de la comilla simple debe venir algo más y finalizar con comilla simple.");
        break;
        //Error 516: Debe finalizar con comilla simple.
        case 516:
            vectorError.push_back("Error 514: El Lexema -> " + valor + ". Debe finalizar con comilla simple.");
        break;
    }

}
//-------------------------------------------------------------------------------------------------------------------------
//Analisis Sintactico
void MainWindow::AnalisisSintactico(int estado, QString valor)
{
    stack<int> pila; //pila de estados

    if(estado >= 100 && estado <= 499) //Estado de aceptación
    {
        pila.push(estado);
    }

    if(estado >= 100 && estado <= 499 && pila.empty())
    {
        ui -> ptAnalisisSintactico -> setPlainText("La cadena es válida: " + valor + "\n");
    }
    else
    {
        ui -> ptAnalisisSintactico -> setPlainText("La cadena no es válida: " + valor + "\n");
    }
}
//-------------------------------------------------------------------------------------------------------------------------
//Método Analiza
void MainWindow::AnalisisLexico()
{
    //Comienza
    //Primero guardaremos el texto que estará en nuestra planeText principal en un vector

    QString cadena;
    QVector<QString> vectorString;//Vector tipo string

    //Guardo en un String lo que está en mi planeText
    cadena = ui->ptTexto->toPlainText();
    for(int i = 0; i < cadena.size(); i++)
    {
        vectorString.push_back(cadena.at(i));
        //qDebug()<<vectorString;
    }

    //qDebug()<<vectorString;

    int estado = 0, columna = 0, estado_Anterior = estado;
    int contadorCadena = 0;

    QString qCaracter, auxiliar;
    QString stringEstado, stringEstado2, stringColumna, stringContadorCadena;
    QVector<QString> vectorProcesoAnalisis;
    //stringEstado lo uso para insertar texto en el planeText de Proceso de analisis, es para guiarme.

    vectorString.push_back(QString(QChar::fromLatin1('\0'))); //Añado espacio en blanco para que me analice el ultimo token del archivo
    qDebug()<<"longitud vector" <<vectorString.size();

    while(contadorCadena <= vectorString.size() -1)
    {
        estado = 0;
        vectorProcesoAnalisis.push_back("-------- Analisis del caracter " + stringContadorCadena + " --------");

        //Mando el estado a planText Proceso analisis
        stringEstado = QString::number(estado);
        vectorProcesoAnalisis.push_back("Estado: " + stringEstado);                

        //Mientras el estado sea menor o igual a 29 se ejecuta todo lo que está dentro de este while.
        while(estado <= 30)
        {
            //Asigno el caracter del vecto a la variable qCaracter
            qCaracter = vectorString[contadorCadena];

            //qDebug()<<"Antes de Caracter a Analizar \n"<<qCaracter;
            vectorProcesoAnalisis.push_back("Caracter a analizar: " + qCaracter);
            //qDebug()<<"Despues de Caracter a Analizar" <<qCaracter;

            //Según sea el caracter me asigna el número de columna
            columna = Relaciona(qCaracter.toStdString().c_str()[0]);
            stringColumna = QString::number(columna);
            vectorProcesoAnalisis.push_back("Columna: " + stringColumna);

            //Hace la busqueda en la matriz y asigna el estado al que va el autómata
            estado = matriz[estado][columna];

            stringEstado2 = QString::number(estado);
            vectorProcesoAnalisis.push_back("Estado x Columna: " + stringEstado2);            

            //Si el estado es menor a 100 y el caracter es diferente de EOF, entra a este if
            if(estado > 0 && estado < 100 && qCaracter != '\0')
            {
                qDebug()<<auxiliar;
                //Añado el caracter a una variable auxiliar
                auxiliar = auxiliar + qCaracter;
                qDebug()<<auxiliar;
                vectorProcesoAnalisis.push_back("Añado el caracter a una variable auxiliar: " + auxiliar);
            }            
            //Aumento el contador para recorrer la cadena en el vector
            contadorCadena = contadorCadena + 1;
            stringContadorCadena = QString::number(contadorCadena);
            vectorProcesoAnalisis.push_back("Aumento el contador para recorrer la cadena en el vector: " + stringContadorCadena);
            vectorProcesoAnalisis.push_back("------------------------------------------");                        

        }

        //Analiza Constantes Enteras, Flotantes, N.C
        //Si es un estado que está entre 128 y 130 es una constante Entera, Flotantes o N.C
        if(estado == 128 || estado == 129 || estado == 130)
        {
            auxiliar = auxiliar + qCaracter;

        }
        //-----------------------------------------------------------------------------------------------------------------
        //Analiza Operadores Relacionales
        if(estado == 100 || estado == 102 || estado == 103 || estado == 104 || estado == 105 || estado == 106 || estado == 107)
        {

            auxiliar = auxiliar + qCaracter;
            //contadorCadena = contadorCadena - 1; retosedo para analizar lo que seguia ejemplo id<id retocedo para analisar solamente < de aqui en adelante id
        }
        //-----------------------------------------------------------------------------------------------------------------
        //Analiza Comentarios de Línea // o Bloque /**/
        if(estado == 108 || estado == 109)
        {
            auxiliar = auxiliar + qCaracter;
        }
        //-----------------------------------------------------------------------------------------------------------------

        //Analiza Operadores Aritméticos Suma + Resta - Multi * y Div /

        if(estado == 110 || estado == 111 || estado == 112 || estado == 113 || estado == 114)
        {
            auxiliar = auxiliar + qCaracter;

        }
        //-----------------------------------------------------------------------------------------------------------------
        //Analiza Signos de puntuación ; . ,
        if(estado == 115 || estado == 116 || estado == 117 || estado == 118)
        {
            auxiliar = auxiliar + qCaracter;            
        }        
        //-----------------------------------------------------------------------------------------------------------------
        //Analiza Signos de Agrupación { } [ ] ( )
        if(estado == 119 || estado == 120 || estado == 121 || estado == 122 || estado == 123 || estado == 124)
        {
            auxiliar = auxiliar + qCaracter;            
        }
        //-----------------------------------------------------------------------------------------------------------------
        //Analiza Palabras Reservadas o Identificadores (id)
        if(estado == 127)
        {            
            contadorCadena = contadorCadena - 1;
        }
        //-----------------------------------------------------------------------------------------------------------------
        //Analiza Constantes Caracter
        if(estado == 125)
        {
            auxiliar = auxiliar + qCaracter;
        }
        //-----------------------------------------------------------------------------------------------------------------
        //Analiza Constantes String
        if(estado == 126)
        {
            auxiliar = auxiliar + qCaracter;
        }
        //-----------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
        //Terminado el proceso añadimos todo a la función Token
        if( estado >= 100 && estado <= 499)
        {
            //Estado de Aceptación
            Token(estado, auxiliar);
            //AnalisisSintactico(estado, auxiliar);
            auxiliar = "";            
        }
        else if(estado >= 500)
        {
            //Estado de Error
            Error(estado, auxiliar);
            auxiliar = "";
        }


    }

    QString token, error, cadProcesosAnalisis;
    for(int i =  0; i < vectorToken.size();i++)
    {
        token = token + vectorToken[i] + "\n";

        qDebug()<<token;
    }
    qDebug()<<vectorToken;
    for(int i =  0; i < vectorError.size();i++)
    {
        error = error + vectorError[i] + "\n";
    }
    for(int i =  0; i < vectorProcesoAnalisis.size();i++)
    {
        cadProcesosAnalisis = cadProcesosAnalisis + vectorProcesoAnalisis[i] + "\n";
    }

    ui -> ptAnalisisToken -> setPlainText(token);
    ui -> ptAnalisisError -> setPlainText(error);
    ui -> ptProcesoAnalisis -> setPlainText(cadProcesosAnalisis);
}
//-------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_btnAnalizar_clicked()
{
    AnalisisLexico();
}
//-------------------------------------------------------------------------------------------------------------------------
