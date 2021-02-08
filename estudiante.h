#ifndef NOTAS_H
#define NOTAS_H

#include <QObject>

class notas : public QObject
{
    Q_OBJECT

public:
    explicit notas(QObject *parent = nullptr);
    notas(QString Nombre, QString Apellido, int Nota1, int Nota2);
    QString getNombre();
    QString getApellido();
    int getNota1();
    int getNota2();
    int getCalculo();


private:
    QString m_nombre;
    QString m_apellido;
    int m_nota1;
    int m_nota2;
    int m_Calculo;
};

#endif // NOTAS_H
