#include "MainWindow.h"
#include "Core/Component.h"
#include "Core/Renderer.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_ellipseEntity.AddComponent(std::make_shared<CEllipse>(width()/2, height()/2));

    m_ellipseEntity.AddComponent(std::make_shared<CRectangle>(width()/3, height()/3, 20, 10));

    m_ellipseEntity.RemoveComponentOfType<CRectangle>();

//    m_ellipseEntity.AddComponent(std::make_shared<CCircle>(width()/2, height()/2, 50));

    m_ellipseEntity.AddComponent(std::make_shared<CPen>(Qt::red, 2));

    setMouseTracking(true);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent* e)
{
   // if (e->button() & Qt::LeftButton )
    {
        if (HaveCapability<Entity, CEllipse>(m_ellipseEntity))
        {
            auto m_ellipse = m_ellipseEntity.GetComponentOfType<CEllipse>();
            m_ellipse->update(e->pos().x(), e->pos().y());
            update();
        }
    }
  //  if (e->button() & Qt::RightButton )
    {
        if (HaveCapability<Entity, CSquare>(m_ellipseEntity))
        {
            auto m_ellipse = m_ellipseEntity.GetComponentOfType<CSquare>();
            m_ellipse->update(e->pos().x(), e->pos().y());
            update();
        }
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{

    QMainWindow::mouseMoveEvent(e);
}

void MainWindow::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    CPen pen;
    if (HaveCapability<Entity, CPen>(m_ellipseEntity))
    {
        pen = *m_ellipseEntity.GetComponentOfType<CPen>();
    }

    RenderComponentWithPositionCapability(painter, m_ellipseEntity, pen);

    //    RenderEllipse(painter, m_ellipseEntity, pen);
    //    RenderSquare(painter, m_ellipseEntity, pen);
}

void MainWindow::on_spinBoxPen_valueChanged(int arg1)
{
    if (HaveCapability<Entity, CPen>(m_ellipseEntity))
    {
        auto pen = m_ellipseEntity.GetComponentOfType<CPen>();
        pen->thikness = arg1;
        update();
    }
}


void MainWindow::on_spinBoxRadius_valueChanged(int arg1)
{
    if (HaveCapability<Entity, CEllipse>(m_ellipseEntity))
    {
        auto ellipse = m_ellipseEntity.GetComponentOfType<CEllipse>();
        ellipse->rx = arg1;
        ellipse->ry = arg1;
        update();
    }
    if (HaveCapability<Entity, CSquare>(m_ellipseEntity))
    {
        auto m_ellipse = m_ellipseEntity.GetComponentOfType<CSquare>();
        m_ellipse->side = arg1;
        update();
    }
}


void MainWindow::on_checkBoxSquareCap_toggled(bool checked)
{
    if (checked)
    {
        m_ellipseEntity.AddComponent(std::make_shared<CSquare>(width()/2, height()/2));
    }
    else
    {
        m_ellipseEntity.RemoveComponentOfType<CSquare>();
    }
    update();
}

