#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openImage1, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(ui->openImage2, SIGNAL(triggered()), this, SLOT(openTemplateImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage(){
    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "C://", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
    this->image = cv::imread(fileName.toStdString(),0);
    setView1(image);

}
void MainWindow::openTemplateImage(){
    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "C://", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
    this->matchingImage = cv::imread(fileName.toStdString(),0);
    setView2(matchingImage);

}
void MainWindow::setView1(cv::Mat image){
    QPixmap im = ASM::cvMatToQPixmap(image);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(im);
    ui->view1->setScene(scene);
    ui->view1->fitInView(scene->sceneRect(),Qt::IgnoreAspectRatio);
}
void MainWindow::setView2(cv::Mat image){
    QPixmap im = ASM::cvMatToQPixmap(image);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(im);
    ui->view2->setScene(scene);
    ui->view2->fitInView(scene->sceneRect(),Qt::IgnoreAspectRatio);
}
