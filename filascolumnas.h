#ifndef FILASCOLUMNAS_H
#define FILASCOLUMNAS_H

#include <QDialog>

namespace Ui {
class FilasColumnas;
}
class QSpinBox;
class FilasColumnas : public QDialog
{
    Q_OBJECT

public:
    explicit FilasColumnas(QWidget *parent = nullptr);
    ~FilasColumnas();
    int getNumeroDeFilas()const;
    int getNumeroDeColumnas()const;

private slots:
    void on_btn_Crear_accepted();


    void on_btn_Crear_rejected();

private:
    Ui::FilasColumnas *ui;
    void SpinBox(QSpinBox *spinBox, int min, int max) const;
};

#endif // FILASCOLUMNAS_H
