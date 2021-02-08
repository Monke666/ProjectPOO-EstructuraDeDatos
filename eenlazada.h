#ifndef EEnlazada_H
#define EEnlazada_H
#include <QString>
#include <mainwindow.h>
#include <ingresarnotas.h>
#include <QWidget>
#include <QStandardItemModel>
#include <QKeyEvent>

class Dato{
    public:
    QString Nombre;
    QString Nota;
    Dato(){
        Nombre="no";
        Nota="no";

    }
};
class Nodo{
public:
    Dato dat;
    Nodo *adelante;
    Nodo *atras;
    Nodo(){
        adelante=atras=0;
    }
};

namespace Ui {
class EEnlazada;
}

class EEnlazada : public QWidget
{
    Q_OBJECT

public:
    explicit EEnlazada(QWidget *parent = nullptr);
    ~EEnlazada();
    Nodo *Ingreso(QString elemento1,QString elemento2);

    void AbrirCSV(Nodo *New);

    void GenerarLista(QString Nombre, QString Nota);

    void mostrarDatos();

    void Abrir();

    int cont = 0;

private slots:
    void on_btn_Abrir_clicked();

    void on_btn_Cerrar_clicked();

    void on_btn_Guardar_clicked();

private:
    Ui::EEnlazada *ui;
    Nodo *Cabeza = 0,*Fin = 0;
    QStandardItemModel *csvModel;
};

#endif // EEnlazada_H
