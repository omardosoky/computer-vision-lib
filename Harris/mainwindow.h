#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include<QFileDialog>
#include <qmessagebox.h>
#include<QString>
#include <string.h>
#include <memory>
#include <stdexcept>
#include<cvQTconvert.h>
namespace Ui { class MainWindow; }
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void openImage();
    void openTemplateImage();
    void setView1(cv::Mat);
    void setView2(cv::Mat);
public:
    cv::Mat image;
    cv::Mat matchingImage;


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
