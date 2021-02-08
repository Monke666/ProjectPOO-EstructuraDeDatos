#include "estudiante.h"
#include "mainwindow.h"

notas::notas(QObject *parent) : QObject(parent)
{
    m_nombre = "";
    m_apellido = "";
    m_nota1 = 0;
    m_nota2 = 0;
}

notas::notas(QString Nombre, QString Apellido, int Nota1, int Nota2){
    m_nombre = Nombre;
    m_apellido = Apellido;
    m_nota1 = Nota1;
    m_nota2 = Nota2;
}

QString notas::getNombre(){
    return m_nombre;
}

QString notas::getApellido(){
    return m_apellido;
}

int notas::getNota1(){
    return m_nota1;
}

int notas::getNota2(){
    return m_nota2;
}
