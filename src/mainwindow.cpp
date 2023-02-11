#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar * menuBar = QMainWindow::menuBar();
    QMenu * menuFichier = menuBar->addMenu("&Fichier");
    QMenu * menuOptions = menuBar->addMenu("&Options");
    QMenu * menuAide = menuBar->addMenu("&Aide");
    QAction * actionQuitter = menuFichier->addAction("&Quitter");
    actionQuitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    connect(actionQuitter, SIGNAL(triggered()), this, SLOT(quitApp()));
    QAction * actionAfficherSuffixe = menuOptions->addAction("Afficher &suffixe");
    actionAfficherSuffixe->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actionAfficherSuffixe->setCheckable(true);
    QAction * actionAPropos = menuAide->addAction("A &propos");
    actionAPropos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    connect(actionAPropos, SIGNAL(triggered()), this, SLOT(displayAPropos()));
    QWidget * mainWidget = new MainWidget(this);
    connect(actionAfficherSuffixe, SIGNAL(toggled(bool)), mainWidget, SLOT(displaySuffixe(bool)));
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::quitApp()
{
    close();
}

void MainWindow::displayAPropos()
{
    QMessageBox::about(this, "A propos de Calculatrice", "Calculatrice \n(c) Colin Hartvick\n     Mohamed Chergui");
}
