#include "graficararbol.h"
#include "ui_graficararbol.h"
#include "ingresarnotas.h"
#include "ui_ingresarnotas.h"
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QStandardItem>
#include <QString>

GraficarArbol::GraficarArbol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraficarArbol)
{
    ui->setupUi(this);
    pixmap = QPixmap(ui->imagen->size());
    pixmap.fill(Qt::white);
    ui->imagen->setPixmap(pixmap);
    inicio(300,300);
}

GraficarArbol::~GraficarArbol()
{
    delete ui;
}

ABB GraficarArbol::crearNodo(int x,QString nombreArbol)
{
    ABB nuevoNodo = new(struct nodo);
    nuevoNodo->nombreAr = nombreArbol;
    nuevoNodo->num = x;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

void GraficarArbol::insertar(ABB &Arbol, int x, QString nombreArbol)
{
    if(Arbol==NULL)
    {
       Arbol = crearNodo(x,nombreArbol);
    }
    else if(x < Arbol->num)
        insertar(Arbol->izq, x,nombreArbol);

    else if(x > Arbol->num)
        insertar(Arbol->der, x,nombreArbol);

}

void GraficarArbol::preOrden(ABB Arbol)
{
    if(Arbol!=NULL)
    {
         ui->nodos->insertPlainText(Arbol->nombreAr+"<->"+QString::number(Arbol->num)+"  ");
         preOrden(Arbol->izq);
         preOrden(Arbol->der);
    }
}
void GraficarArbol::enOrden(ABB Arbol)
{
    if(Arbol!=NULL){

        enOrden(Arbol->izq);
        ui->nodos->insertPlainText(Arbol->nombreAr+"<->"+QString::number(Arbol->num)+"  ");
        enOrden(Arbol->der);
    }
}
void GraficarArbol::postOrden(ABB Arbol)
{
    if(Arbol!=NULL)
    {
         postOrden(Arbol->izq);
         postOrden(Arbol->der);
         ui->nodos->insertPlainText(Arbol->nombreAr+"<->"+QString::number(Arbol->num)+"  ");
    }
}

void GraficarArbol::verArbol(ABB Arbol, int n)
{
    if(Arbol==NULL)
           return;

       verArbol(Arbol->der, n+1);
       ui->nodos->appendPlainText("");
       incrementox=0;
       for(int i = 0; i < n; i++){
         ui->nodos->insertPlainText("           ");
         incrementox=incrementox+30;
      }
      ui->nodos->insertPlainText(Arbol->nombreAr+"=>"+QString::number(Arbol->num));
      circulo(radio,x1,y1,incrementox,incrementoy,QString::number(Arbol->num),Qt::cyan,Qt::black);
      incrementox=incrementox-40;
      incrementoy=incrementoy+30;
      verArbol(Arbol->izq, n+1);
}

void GraficarArbol::inicio(int alto, int ancho)
{
    ui->imagen->resize(alto + 100, ancho + 150);
    pixmap= QPixmap(ui->imagen->size());
    pixmap.fill(Qt::white);
    ui->imagen->setPixmap(pixmap);
}

void GraficarArbol::circulo(int radio, int x, int y, int incrementox, int incrementoy, QString texto, QColor colorfondo, QColor colorlinea)
{
    QPainter painter(&pixmap);
    if (incrementox==0)
        painter.setBrush(colorfondo);
    else
        painter.setBrush(Qt::yellow);
    QPen pen(colorlinea);
    painter.setPen(pen);
    painter.drawEllipse(x+incrementox,y+incrementoy,radio,radio);
    painter.setPen(pen);
    painter.drawText(x+incrementox+12,y+incrementoy+20,texto);
    ui->imagen->setPixmap(pixmap);
}

int GraficarArbol::promedio()
{
    int i=0;
    int flag0 = 0;
    int flag2 = 4;
    int nota = 0;
    int cont = 0;
    int contd = 0;
    float promedioc;
    QString nombre;
    QString notaf;
    QString nombreArchivo = QFileDialog::getOpenFileName(this, "A B R I R", QDir::rootPath(), "CSV File (*.csv)");
    QFile file;
    file.setFileName(nombreArchivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QMessageBox::information(this,"A V I S O","Archivo no Creado");
            }else{
        }
    QTextStream in(&file);

    while (!in.atEnd()){
      QString line = in.readLine();
      auto elements = line.split(",");
      QList<QStandardItem *> standardItemsList;
      for (QString item : line.split(";")) {
           standardItemsList.append(new QStandardItem(item));
           if (i == flag0){
                nombre = item;
                flag0+= 5;
           }
             if(i==flag2){
             cont = cont+1;
             notaf = item;
             nota = notaf.toInt();
             contd += nota;
             promedioc=contd/cont;
             flag2+= 5;
           }
             i=i+1;
    }
  }
    return promedioc;
}

void GraficarArbol::on_btn_Abrir_clicked()
{
    ui->nodos->setPlainText("");
    int i = 0;
    int flag0 = 0;
    int flag2 = 4;
    int nota = 0;
    int cont = 0;
    int contd = 0;
    insertar(arbol,promedio(),"Promedio");
    QString nombre,notaf;
    QString nombreArchivo = QFileDialog::getOpenFileName(this, "A B R I R", QDir::rootPath(), "CSV File (*.csv)");
    QFile file;
    file.setFileName(nombreArchivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QMessageBox::information(this,"A V I S O","Archivo no Creado");
            }else{
        }
    QTextStream in(&file);

    while (!in.atEnd()){
      QString line = in.readLine();
      auto elements = line.split(",");
      QList<QStandardItem *> standardItemsList;
      for (QString item : line.split(";")) {
           standardItemsList.append(new QStandardItem(item));
           if (i==flag0){
                nombre = item;
                flag0+=5;
           }
             if(i==flag2){
             cont=cont+1;
             notaf=item;
             nota=notaf.toInt();
             contd += nota;
             insertar(arbol,nota,nombre);
             flag2+=5;
           }
             i=i+1;
    }
  }
    ui->nodos->appendPlainText("RECORRIDOS:");
    ui->nodos->insertPlainText("\n\n");
    ui->nodos->appendPlainText("EN-ORDEN");
    ui->nodos->insertPlainText("\n\n");
    enOrden(arbol);
    ui->nodos->insertPlainText("\n\n");
    ui->nodos->appendPlainText("PRE-ORDEN");
    ui->nodos->insertPlainText("\n\n");
    preOrden(arbol);
    ui->nodos->insertPlainText("\n\n");
    ui->nodos->appendPlainText("POST-ORDEN");
    ui->nodos->insertPlainText("\n\n");
    postOrden(arbol);
     ui->nodos->insertPlainText("\n\n");
    ui->nodos->insertPlainText("REPRESENTACION GRAFICA");
    verArbol(arbol,0);
}

void GraficarArbol::on_btn_Guardar_clicked()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,"Guardar imagen",QString(),"Imagenes (*.png)");
        if (!nombreArchivo.isEmpty()){
             if (pixmap.save(nombreArchivo)){
                  QMessageBox::information(
                              this,"Guardar imagen","Archivo almacenado en: " + nombreArchivo);
             }else{
                 QMessageBox::warning(
                             this,"Guardar imagen","No se pudo guardar el archivo");
             }
        }
}

void GraficarArbol::on_btn_Cerrar_clicked()
{
    close();
}


