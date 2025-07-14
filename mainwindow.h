#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QMap>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// 包裹数据结构
struct Package {
    QString id;
    double weight;
    QString destination;
    int arrivalTime;
    int deadline;
};

// 地图节点
struct MapNode {
    QString name;
    QMap<QString, double> edges; // 邻接节点和距离
};

// 小车数据结构
struct DeliveryCar {
    double speed;
    double weight;
    double maxLoad;
    double currentLoad;
    QVector<Package> packages;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 路径规划相关方法
    void loadMapData(const QString &filePath);
    void loadPackageData(const QString &filePath);
    void calculateOptimalRoute();
    void displayResults();

private:
    Ui::MainWindow *ui;
    QVector<MapNode> map;
    QVector<Package> packages;
    DeliveryCar car;
    
    // UI元素
    QPushButton *btnLoadMap;
    QPushButton *btnLoadPackages;
    QPushButton *btnCalculate;
    QPushButton *btnDisplay;
    QTextEdit *txtResult;
};

#endif // MAINWINDOW_H
