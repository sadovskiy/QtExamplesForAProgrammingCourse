/*
 *
 * Copyright (C) 2019 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2019 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
 * Московский Государственный строительный университет (МГСУ)
 *
 * Написана Садовским Б. С.
 *
 */

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QLibraryInfo>
#include <QLabel>

/**
 * Следует отметить, что файл с переводом "*.qm" подхватываемый и загружаемый
 * нашей программой формируется программой "lrelease",
 * а файл с текстом подлежащим переводу "*.ts" программой "lupdate".
 * Сам перевод выполняется в программе "linguist"
 * Последовательность действий.
 * 1. В исходном коде все сообщения, которые хотим, что бы были переведены
 * обрамляем функцией "tr()" и на английском языке.
 * 2. В файле управления проектом "*.pro" даём название файлам с переводом.
 * 3. Запускаем программу "lupdate".
 * 4. Запускаем программу "linguist",
 * в которой переводим все сообщения и тексты.
 * 5. Запускаем программу "lrelease".
 * 6. Полученные файлы "*.qm" подгружаем к нашему приложению.
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , languageActionGroup(nullptr)
  , label(new QLabel(this))
{
    ui->setupUi(this);

    /**
     * Для проверки смены языка в диалоговых окнах, создадим пару
     * диалоговых окон в соответствующих слотах.
     * Для начала создадим связь пунктов меню и этих слотов.
     * В первом случае будет вызваться окно типа "QFileDialog",
     * а во втором окно справки о Qt "aboutQt()"
     */
    connect(ui->actionOpen, &QAction::triggered,
            this, &MainWindow::open);
    connect(ui->actionExit, &QAction::triggered,
            this, &MainWindow::close);
    connect(ui->actionAboutQt, &QAction::triggered,
            qApp, &QApplication::aboutQt);

    /**
     * Подключим переменные, которые в будущем будут
     * содержать переводы к нашему приложению
     */
    qApp->installTranslator(&appTranslator);
    qApp->installTranslator(&qtTranslator);

    /**
     * Получаем путь к файлам переводов, которые должны лежать в
     * каталоге "translations". Для этого узнаём
     * где расположен наш исполняемый "*.exe" файл с
     * помощью "applicationDirPath()" и прибавляем название
     * каталога "/translations" с файлами перевода.
     * Ещё раз, этот каталог с файлами "*.qm" должен лежать вместе
     * с исполняемым "*.exe" файлом
     */
    qmPath = qApp->applicationDirPath() + "/translations";

    /**
     * Запускаем метод (функцию-член), где описано создание меню
     * со списком доступных переводов нашего приложения
     */
    createLanguageMenu();

    // Тут не рекомендуется создавать динамический объект,
    // так как потом наблюдаются проблемы с меню
//    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 10, 100, 100));
    label->setText(tr("Hello World!"));
}

MainWindow::~MainWindow()
{
    delete label;
    delete ui;
}

void MainWindow::open()
{
    /// Создаём диалоговое окно в динамической памяти
    QFileDialog *fdialog = new QFileDialog(this);
    fdialog->setAttribute(Qt::WA_DeleteOnClose);

    /**
     * Запрашиваем имя выбранного файла,
     * но ничего с ним не делаем (просто демонстрация диалогового окна)
     * Опция "DontUseNativeDialog" - это что бы не использовать родной диалог,
     * а использовать диалог из библиотеки Qt.
     */
    fdialog->getOpenFileName(this,
                             tr("Open Document"),
                             QDir::currentPath(),
                             QString(),
                             nullptr,
                             QFileDialog::DontUseNativeDialog);
}

void MainWindow::createLanguageMenu()
{
    /// Создаём список пунктов выбора языка в динамической памяти
    languageActionGroup = new QActionGroup(this);

    /// Ставим связь пунктов меню со слотом смены языка приложения
    connect(languageActionGroup, &QActionGroup::triggered,
            this, &MainWindow::switchLanguage);

    /// Определяем каталог, где лежат файлы переводов "*.qm"
    QDir dir(qmPath);

    /**
     * Получаем список файлов "*.qm" в каталоге, которые относятся
     * к нашей программе по шаблону "multilang_*.qm",
     * где "multilang" - название нашего приложения
     * "_" - разделитель
     * "*" - означает любой символ или группа символ произвольной длинны
     * ".qm" - расширение файла
     */
    QStringList fileNames =
            dir.entryList(QStringList("multilang_*.qm"));

    /**
     * Количество пунктов меню нам заранее не известно,
     * но так как оно зависит от количества файлов "*.qm"
     * в каталоге "translations",
     * то мы можем сформировать в меню столько пунктов,
     * сколько файлов у нас, используя цикл.
     */
    for (int i = 0; i < fileNames.size(); i++) {
        /// Получаем i-ую локаль
        QString locale = fileNames[i];
        /// Удаляем симыолы в строке сначала и по символ "_" включительно
        locale.remove(0, locale.indexOf('_') + 1);
        /// Удаляем симыолы в строке начиная с символа точки
        locale.truncate(locale.lastIndexOf('.'));

        /// Создаём временную переменную перевода для языкового пункта меню
        QTranslator translator;
        /// Загружаем перевод из файла перевода "*.qm"
        translator.load(fileNames[i], qmPath);

        /**
         * Создаём имя i-ого пункта меню с названием языка путём
         * перевода в linguist заменив English на соответствующий язык
         */
        QString language = translator.translate("MainWindow",
                                                "English");

        /**
         * Создаём пункт в меню с i-ым языком по маске "&%1 %2",
         * где "&" - символ быстрого доступа к пункту меню через сочетание
         * клавиш Alt+символ_перед_которым_стоит_&;
         * "%1" - номер i-ого пункта меню по порядку.
         * "%2" - название языка, которое будет отображаться в меню.
         */
        QAction *action = new QAction(tr("&%1 %2")
                                      .arg(i + 1)
                                      .arg(language),
                                      this);

        /**
         * Задаём свойства для i-ого пункта меню.
         * Возможность держать пункт меню выбранным
         * пока пользователем не будет выбран другой пункт меню.
         */
        action->setCheckable(true);
        // Задаём внутренние данные хранимые в i-ом пункте.
        // В нашем случае это локаль вида "ru_RU"
        action->setData(locale);

        /// Добавляем i-ый пункт в меню на нашей форме "mainwindow.ui"
        ui->menuLanguage->addAction(action);
        /// Добавляем i-ый пункт в единую группу пунктов
        languageActionGroup->addAction(action);

        /// Задаём  английский язык в качестве выбранного по умолчанию
        if (language == "English")
            action->setChecked(true);
    }
}

void MainWindow::switchLanguage(QAction *action)
{
    /**
     * Определяем локаль которую выбрал пользователь.
     * Например "ru_RU" для русского языка в России или
     * "en_US" для английского в США
     */
    QString locale = action->data().toString();

    /// Загружаем тот перевод который выбрал пользователь
    appTranslator.load("multilang_" + locale, qmPath);
    locale.chop(3);
    /**
     * Для переводов стандартных сообщений Qt можно запросить у системы
     * их местонахождение через вызов "QLibraryInfo::TranslationsPath"
     */
    qtTranslator.load("qt_" + locale + ".qm", QLibraryInfo::location(
                          QLibraryInfo::TranslationsPath));



    /**
     * Взываем "retranslateUi()" для обновления интерфейса приложения
     * используя загруженный из соответствующего файла "qm" язык
     */
    ui->retranslateUi(this);

    // Для элемента созданного динамический, но не на форме,
    // надо заново задать текст, который сработает при переключении языка
    label->setText(tr("Hello World!"));
}
