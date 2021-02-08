#include "ingresarnotas.h"
#include "ui_ingresarnotas.h"
#include "estudiante.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextStream>
#include <QDebug>

ingresarNotas::ingresarNotas(QList<notas*> m_notas, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ingresarNotas)
{
    ui->setupUi(this);
    QStringList etiqueta;
    etiqueta << "NOMBRE" << "APELLIDO" << "NOTA 1er PARCIAL" << "NOTA 2do PARCIAL" << "NOTA FINAL";
    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(5);
    csvModel->setHorizontalHeaderLabels(etiqueta);
    ui->tableView->setModel(csvModel);
    int index = csvModel->rowCount();

    for(int i = 0; i < m_notas.length(); i++){
        csvModel->insertRows(index,1);
        csvModel->setData(csvModel->index(index,0),m_notas.at(i)->getNombre());
        csvModel->setData(csvModel->index(index,1),m_notas.at(i)->getApellido());
        csvModel->setData(csvModel->index(index,2),0);
        csvModel->setData(csvModel->index(index,3),0);
        csvModel->setData(csvModel->index(index,4),0);
        csvModel->item(index,4)->setEnabled(false);


    }
    connect(csvModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(Promedio(QModelIndex)));
}

ingresarNotas::~ingresarNotas()
{
    delete ui;
}


void ingresarNotas::Promedio(const QModelIndex &index){

        int error = 0;
        double promT = 0;
        double Fila = csvModel->rowCount();

        //DEFINICION DE VARIABLES

        QString Elemento1 = csvModel->item(index.row(),2)->text();
        double nota1 = Elemento1.toDouble();

        QString Elemento2 = csvModel->item(index.row(),3)->text();
        double nota2 = Elemento2.toDouble();

        QString sumaT = csvModel->item(index.row(),index.column())->text();
        double suma = sumaT.toDouble();

        //CONDICIONAL MENORES E IGUALES DE 50

        if (nota1 > 50){
            QMessageBox::information(this,"Aviso","\nNO SE PUEDE VALIDAR\nVALORES MAXIMOS HASTA: 50");
            error = 0;
            csvModel->setData(csvModel->index(index.row(),index.column()),error);

        }else{

        if (nota2 > 50){
             QMessageBox::information(this,"Aviso","\nNO SE PUEDE VALIDAR\nVALORES MAXIMOS HASTA: 50");
             error = 0;
             csvModel->setData(csvModel->index(index.row(),index.column()),error);

        }else{

        //OBTENCION DE DATOS DE CADA CELDA Y POSTERIOR SUMA

        if(index.column() == 2){
            QString dato1 = csvModel->item(index.row(),2)->text();
            nota2 = dato1.toDouble();
        }
        if (index.column() == 3){
            QString dato1 = csvModel->item(index.row(),3)->text();
            nota2 = dato1.toDouble();
        }
        suma = nota1 + nota2;
        csvModel->setData(csvModel->index(index.row(),4),suma);
        }

        //PROMEDIO

        for(int i = 0; i < Fila; i++){
            QString dato = csvModel->item(i,4)->text();
            promT += dato.toDouble();
            ui->txt_Promedio->setText(QString::number(promT/Fila));
                 }

            }
        }

void ingresarNotas::on_btn_Guardar_clicked()
    {
           QString nombreArchivo;
           QFile file;
           nombreArchivo = QFileDialog::getSaveFileName(this, "G U A R D A R  C O M O", QDir::rootPath(), "CSV File (*.csv)");
           file.setFileName(nombreArchivo);
           if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
              QMessageBox::information(this,"A V I S O","Archivo no Creado");
           }else{
                QTextStream in(&file);
                int n = csvModel->rowCount();
                int m = csvModel->columnCount();
                QString line;
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < m; j++){
                        if (j!=(m - 1)){
                            line = csvModel->item(i,j)->text()+";";
                        }else{
                            line = csvModel->item(i,j)->text();
                        }
                        in<<line;

               }
               in<<"\n";
           }
           QMessageBox::information(this,"A V I S O","Archivo Guardado con Exito");
           file.close();
       }
    }


void ingresarNotas::on_btn_Anadir_clicked()
{
      QString nombreArchivo;
      QTextStream entrada;
      QFile file;
      nombreArchivo = QFileDialog::getOpenFileName(this, "A B R I R", QDir::rootPath(), "CSV File (*.csv)");
      file.setFileName(nombreArchivo);
      if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
          QMessageBox::critical(this,"Error",file.errorString());
          return;
      }
      QTextStream in(&file);
      while (!in.atEnd()){
      QString line = in.readLine();
      QList<QStandardItem *> standardItemsList;
      for (QString item : line.split(";")) {
          standardItemsList.append(new QStandardItem(item));
        }
       csvModel->insertRow(csvModel->rowCount(), standardItemsList);
      }
  }


void ingresarNotas::on_btn_Cerrar_clicked()
{
    close();
}

