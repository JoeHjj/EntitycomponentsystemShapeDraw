#pragma once

#include <QMouseEvent>
#include <QPaintEvent>
#include <QMainWindow>
#include "Core/Entity.h"

class EllipseEntity : public Entity
{
public :
    EllipseEntity() = default;
  };

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mouseReleaseEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *event) override;


private slots:
    void on_spinBoxPen_valueChanged(int arg1);

    void on_spinBoxRadius_valueChanged(int arg1);

    void on_checkBoxSquareCap_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    EllipseEntity m_ellipseEntity;
};
