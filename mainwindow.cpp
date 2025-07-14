#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 初始化小车参数
    car.speed = 1.0;
    car.weight = 100.0;
    car.maxLoad = 500.0;
    car.currentLoad = 0.0;
    
    // 连接信号槽
    connect(ui->btnLoadMap, &QPushButton::clicked, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "选择地图文件", "", "文本文件 (*.txt)");
        if (!filePath.isEmpty()) {
            loadMapData(filePath);
        }
    });
    
    connect(ui->btnLoadPackages, &QPushButton::clicked, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "选择包裹文件", "", "文本文件 (*.txt)");
        if (!filePath.isEmpty()) {
            loadPackageData(filePath);
        }
    });
    
    connect(ui->btnCalculate, &QPushButton::clicked, this, &MainWindow::calculateOptimalRoute);
    connect(ui->btnDisplay, &QPushButton::clicked, this, &MainWindow::displayResults);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadMapData(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开地图文件");
        return;
    }

    QTextStream in(&file);
    int n, m;
    
    // 首先读取n和m
    in >> n >> m;
    
    // 添加调试输出
    qDebug() << "开始读取地图数据";
    
    qDebug() << "节点数:" << n << "边数:" << m;
    
    if (n <= 0 || m <= 0) {
        QMessageBox::warning(this, "错误", QString("无效的地图数据: 节点数=%1 边数=%2").arg(n).arg(m));
        return;
    }
    
    map.resize(n);
    for (int i = 0; i < n; ++i) {
        if (in.atEnd()) {
            QMessageBox::warning(this, "错误", QString("文件过早结束，缺少节点名称，已读取%1个节点").arg(i));
            return;
        }
        in >> map[i].name;
        qDebug() << "节点" << i << ":" << map[i].name;
    }
    
    for (int i = 0; i < m; ++i) {
        if (in.atEnd()) {
            QMessageBox::warning(this, "错误", QString("文件过早结束，缺少边数据，已读取%1条边").arg(i));
            return;
        }
        
        int u, v;
        double w;
        in >> u >> v >> w;
        qDebug() << "边" << i << ":" << u << v << w;
        
        // 调整节点索引从1开始的情况
        u--;
        v--;
        
        // 检查节点索引是否有效
        if (u < 0 || u >= n || v < 0 || v >= n) {
            QMessageBox::warning(this, "错误", QString("无效的节点索引: %1-%2 (有效范围: 0-%3)").arg(u+1).arg(v+1).arg(n-1));
            continue;
        }
        
        map[u].edges[map[v].name] = w;
        map[v].edges[map[u].name] = w; // 无向图
    }
    
    file.close();
    qDebug() << "地图数据加载完成";
}

void MainWindow::loadPackageData(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开包裹文件");
        return;
    }

    QTextStream in(&file);
    Package pkg;
    while (!in.atEnd()) {
        in >> pkg.id >> pkg.weight >> pkg.destination >> pkg.arrivalTime >> pkg.deadline;
        packages.append(pkg);
    }
    
    file.close();
}

void MainWindow::calculateOptimalRoute()
{
    if (map.isEmpty() || packages.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先加载地图和包裹数据");
        return;
    }
    
    // 任务三：基本送货路径规划
    double totalCost = 0.0;
    int latePackages = 0;
    
    // 按目的地分组包裹
    QMap<QString, QVector<Package>> destinationGroups;
    for (const Package &pkg : packages) {
        destinationGroups[pkg.destination].append(pkg);
    }
    
    // 对每个目的地规划路线
    for (auto it = destinationGroups.begin(); it != destinationGroups.end(); ++it) {
        const QString &dest = it.key();
        const QVector<Package> &pkgs = it.value();
        
        // 计算总重量
        double totalWeight = 0.0;
        for (const Package &pkg : pkgs) {
            totalWeight += pkg.weight;
        }
        
        // 简单路径：从驿站直接到目的地
        // TODO: 实现更智能的路径规划算法
        double distance = map[0].edges.value(dest, 0.0);
        if (distance > 0) {
            totalCost += distance * (car.weight + totalWeight);
            
            // 检查是否超时
            double travelTime = distance / car.speed;
            for (const Package &pkg : pkgs) {
                if (travelTime > pkg.deadline) {
                    latePackages++;
                }
            }
        }
    }
    
    // 显示结果
    ui->txtResult->append(QString("总运输成本: %1").arg(totalCost));
    ui->txtResult->append(QString("超时包裹数量: %1").arg(latePackages));
}

void MainWindow::displayResults()
{
    if (map.isEmpty() || packages.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先加载地图和包裹数据并计算路径");
        return;
    }
    
    ui->txtResult->clear();
    
    // 显示地图信息
    ui->txtResult->append("=== 地图信息 ===");
    ui->txtResult->append(QString("节点数量: %1").arg(map.size()));
    ui->txtResult->append("节点列表:");
    for (const MapNode &node : map) {
        ui->txtResult->append(QString("  - %1").arg(node.name));
    }
    
    // 显示包裹信息
    ui->txtResult->append("\n=== 包裹信息 ===");
    ui->txtResult->append(QString("包裹数量: %1").arg(packages.size()));
    for (const Package &pkg : packages) {
        ui->txtResult->append(QString("包裹ID: %1, 重量: %2, 目的地: %3, 到达时间: %4, 截止时间: %5")
                            .arg(pkg.id).arg(pkg.weight).arg(pkg.destination)
                            .arg(pkg.arrivalTime).arg(pkg.deadline));
    }
    
    // 显示小车信息
    ui->txtResult->append("\n=== 小车信息 ===");
    ui->txtResult->append(QString("速度: %1, 自重: %2, 最大载重: %3, 当前载重: %4")
                        .arg(car.speed).arg(car.weight).arg(car.maxLoad).arg(car.currentLoad));
}
