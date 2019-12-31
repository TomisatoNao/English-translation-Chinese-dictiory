#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "redblacktree.h"
#include "binarysearchtree.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int changeFlag = 0;
    ui->setupUi(this);
    this->setWindowTitle("字典");
    ui->chinesevalue->setPlaceholderText("中文输入");
    ui->englishvalue->setPlaceholderText("英文输入");
    ui->datastruct->setAlignment(Qt::AlignCenter);
    ui->datastruct->setText("当前数据结构：红黑树");
    b = new RedBlackTree;

    connect(ui->find, &QPushButton::pressed, this, [=](){
        if (QString::compare(ui->englishvalue->text(), "") == 0) {
            QMessageBox::warning(this,"错误","文本框为空",QMessageBox::Ok);
        } else {
            ui->chinesevalue->setText(b->Find(ui->englishvalue->text().toStdString()));
            if (QString::compare(ui->chinesevalue->text(), "") == 0) {
                QMessageBox::warning(this, "提示", "未查到该单词，请输入其词性与汉语意思进行插入",QMessageBox::Ok);
            }
        }
    });

    connect(ui->remove, &QPushButton::pressed, this, [=] () {
        if (QString::compare(ui->englishvalue->text(), "")==0) {
            QMessageBox::warning(this,"错误","文本框为空",QMessageBox::Ok);
        } else {
            if (!b->Delete(ui->englishvalue->text().toStdString())) {
                QMessageBox::warning(this,"错误","删除单词不存在",QMessageBox::Ok);
            }
            ui->chinesevalue->setText("");
        }
    });

    connect(ui->add, &QPushButton::pressed, this, [=]() {
        if (QString::compare(ui->englishvalue->text(), "") == 0 || QString::compare(ui->chinesevalue->text(), "")==0) {
            QMessageBox::warning(this,"错误","文本框为空",QMessageBox::Ok);
        } else {
            if (!b->Insert(ui->englishvalue->text().toStdString(),ui->chinesevalue->text().toLocal8Bit().toStdString())) {
                QMessageBox::warning(this,"错误","该单词以存在",QMessageBox::Ok);
            }
        }
    });

    connect(ui->change, &QPushButton::pressed, this, [&]() {
        delete b;
        if(changeFlag%2==0) {
            b = new BinarySearchTree;
            ui->datastruct->setText("当前数据结构：二叉搜索树");
            changeFlag++;
        } else {
            b = new RedBlackTree;
            ui->datastruct->setText("当前数据结构：红黑树");
            changeFlag++;
        }
    });

    connect(ui->englishvalue, &QLineEdit::textChanged, this, [=] () {
        ui->chinesevalue->setText(b->Find(ui->englishvalue->text().toStdString()));
    });
}

MainWindow::~MainWindow()
{
    delete b;
}

