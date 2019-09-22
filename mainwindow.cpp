#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    string sInput = ui->lineEdit->text().toStdString();
    MD5 *obj = new MD5(sInput);
    ui->lineEdit_2->setText(QString::fromStdString(obj->result()));
    delete obj;
}

void MainWindow::on_action_triggered()
{
    QFile file("C://Users//hp//Documents//QtProjects//SD2//input.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;
    QString line;
    QTextStream in(&file);
    while (!in.atEnd())
        line = in.readLine();
    ui->lineEdit->setText(line);
}

void MainWindow::on_action_2_triggered()
{
    QFile file("C://Users//hp//Documents//QtProjects//SD2//output.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;
    QTextStream out(&file);
    string sInput = ui->lineEdit->text().toStdString();
    MD5 *obj = new MD5(sInput);
    out << QString::fromStdString(obj->result());
    out << endl;
}

void MainWindow::on_action_3_triggered()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("TXT Files (*.txt)"));
    ui->lineEdit->setText(filename);
    MD5 *obj = new MD5(filename.toStdString());
    QString hashfile="d09099f68243132e30a42ad4d190c568";
    if(hashfile == QString::fromStdString(obj->result())){
        ui->lineEdit_2->setText("Хеш сума файлу співпадає із заданою.");
    } else {
        ui->lineEdit_2->setText("Хеш сума файлу не співпадає із заданою. Спробуйте ще раз.");
    }
}
