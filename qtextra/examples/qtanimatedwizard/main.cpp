
#include <QApplication>
#include <QtWidgets>
#include <QLocale>
#include <QDebug>
#include <QtSlideController>
QWizardPage *createIntroPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle("Introduction");
    page->setSubTitle("Welcome to Trivial Wizard!");
    QLabel *label = new QLabel("This wizard will help you register your copy "
                               "of Super Product Two.");
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);

    return page;
}

QWizardPage *createRegistrationPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle("Registration");
    page->setSubTitle("Please fill both fields.");

    QLabel *nameLabel = new QLabel("Name:");
    QLineEdit *nameLineEdit = new QLineEdit;

    QLabel *emailLabel = new QLabel("Email address:");
    QLineEdit *emailLineEdit = new QLineEdit;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    page->setLayout(layout);

    return page;
}

QWizardPage *createConclusionPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle("Conclusion");
    page->setSubTitle("Registration complete");

    QLabel *label = new QLabel("You are now successfully registered. Have a "
                               "nice day!");
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);

    return page;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle("Fusion");

    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, Qt::white);
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, Qt::white);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(240,240,240));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::Highlight, QColor(76,163,224));
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);

    a.setPalette(lightPalette);

    QWizard wizard;
    wizard.addPage(createIntroPage());
    wizard.addPage(createRegistrationPage());
    wizard.addPage(createConclusionPage());
    wizard.setWindowTitle("Trivial Wizard");

    wizard.setStyleSheet(
        "QWizard { background-color: white; color: black; }"
        "QWizardPage { background-color: white; }"
        "QLabel { color: black; }"
        "QLineEdit { background-color: #f0f0f0; color: black; }"
        "QPushButton { background-color: #e0e0e0; color: black; }"
        );
    QtSlideController controller(&a);
    controller.setWidget(&wizard);
    controller.setEffects(QtSlideController::RollEffect);
    controller.setSlideDirection(QtSlideController::SlideLeft);
    controller.setDuration(800);
    controller.setFaded(true);
    wizard.show();
    return a.exec();
}
