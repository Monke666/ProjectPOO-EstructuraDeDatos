#include "eenlazada.h"
#include "ui_eenlazada.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"

EEnlazada::EEnlazada(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EEnlazada)
{
    ui->setupUi(this);

}

EEnlazada::~EEnlazada()
{
    delete ui;
}

void EEnlazada::GenerarLista(QString Nombre, QString Nota)
{
        Nodo *nuevo;
        nuevo=Ingreso(Nombre,Nota);
        AbrirCSV(nuevo);

}

Nodo *EEnlazada::Ingreso(QString elemento1, QString elemento2)
{
    Nodo *nuevo;
    nuevo = new Nodo;
    nuevo->dat.Nombre = elemento1;
    nuevo->dat.Nota = elemento2;
    nuevo->adelante = 0;
    nuevo->atras = 0;
    return(nuevo);

}

void EEnlazada::AbrirCSV(Nodo *nuevo)
{
    if(Cabeza==0){
        Cabeza= nuevo;
        Fin=nuevo;
    }else{
        Fin->adelante=nuevo;
        nuevo->atras=Fin;
        Fin=nuevo;
    }
}


void EEnlazada::mostrarDatos()
{

    Nodo *temp=Cabeza;
    if(temp == 0){
        QMessageBox::information(this,"A V I S O","ARCHIVO SIN ELEMENTOS");
    }else{
        while(temp!=0){
            ui->listaEnlazada->insertPlainText("\n");
            ui->listaEnlazada->insertPlainText("Nota: ");
            ui->listaEnlazada->insertPlainText(temp->dat.Nota);
            ui->listaEnlazada->insertPlainText("\n");
            ui->listaEnlazada->insertPlainText("Nombre: ");
            ui->listaEnlazada->insertPlainText(temp->dat.Nombre);
            ui->listaEnlazada->insertPlainText("\n");
            ui->listaEnlazada->insertPlainText("Estudiante ("+QString::number(cont=cont+1)+")");
            ui->listaEnlazada->insertPlainText("\n");
            temp= temp->adelante;

        }
    }
}

void EEnlazada::on_btn_Abrir_clicked()
{
    QString nombre,transnot;
    int notaf = 0;
    int flag0 = 0;
    int flag2 = 4;
    int i = 0;

    ui->listaEnlazada->setPlainText("");
    ui->listaEnlazada->appendPlainText("LISTA DE ESTUDIANTES:\n");

    auto filename = QFileDialog::getOpenFileName(this, "Abrir",
        QDir::rootPath(), "CSV File (*.csv)");
    if (filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        auto elements = line.split(",");
        QList<QStandardItem *> standardItemsList;
        for (QString item : line.split(";")) {
             standardItemsList.append(new QStandardItem(item));
             if (i == flag0){
                 nombre = item;
                 flag0+= 5;
             }
             if(i == flag2){
                 transnot = item;
                 notaf = transnot.toInt();
                 flag2+= 5;
                 GenerarLista(nombre,transnot);
             }
            i = i+1;
        }

    }

    mostrarDatos();
}


void EEnlazada::on_btn_Cerrar_clicked()
{
    close();
}


void EEnlazada::on_btn_Guardar_clicked()
{
    QString nombreArchivo;
    QFile Archivo;
    QTextStream salida;

    nombreArchivo = QFileDialog::getSaveFileName(this, "G U A R D A R  C O M O");
    //Condicional para abrir los Archivos
    //Si el Archivo se encuentra Vacio:
    if(nombreArchivo.isEmpty()) return;
    Archivo.setFileName(nombreArchivo);
    Archivo.open(QIODevice::Text | QIODevice::WriteOnly);
    //Si el Archivo se encuentra Abierto o no es posible Abrirlo:
        if (!Archivo.isOpen()){
        QMessageBox::critical(this,"--ERROR--",Archivo.errorString());
        return;
    }
    salida.setDevice(&Archivo);
    salida << "Mensaje del Usuario: " <<  ui -> listaEnlazada -> toPlainText();
    //Apartado en el cual se establecen parametros "Por Defecto"
    Archivo.open(QIODevice::WriteOnly);
    if(!Archivo.isOpen());
    QDataStream salida2(&Archivo);
    //qDebug() << "Version:" << salida.version();
    salida2.setVersion(QDataStream::Qt_5_12); //INDICAR LA VERSION DE Qt
    QString texto = "\n\nDefault Message: H O L A";
    int num = 666;
    salida << texto;
    salida << "\n\nDefault Number: " << num;
    salida << "\n\nVersion del Compilador: " << "v" << salida2.version();
    Archivo.flush();
    Archivo.close();
}
