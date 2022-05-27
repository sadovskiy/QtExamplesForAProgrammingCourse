/*
 *
 * Copyright (C) 2021 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2021 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
 * Московский Государственный строительный университет (МГСУ)
 *
 * Написана Садовским Б. С.
 *
 */

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "textsyntaxhighlighter.hpp"

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>

// Пример состоит из двух других примеров по работе с регулярными выражениям.
// Первый пример показывает работу валидатора, а второй поиска в тексте

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    // Создаём объект highlighter в динамической памяти
    , highlighter(new TextSyntaxHighlighter(this))
{
    ui->setupUi(this);

    // 1. Настройки для вкладки Validator.
    // Устанавливаем объекту ввода QLineEdit,
    // в качестве валидатора QRegularExpressionValidator
    ui->lineEditValidate->setValidator(
                        new QRegularExpressionValidator(ui->lineEditValidate));

    // 2. Настройки для вкладки Find Pattern.
    // Подсоединяем наш объект поиска и подсветки найденного текста
    // к объекту, где расположен сам текст
    highlighter->setDocument(ui->plainTextEdit->document());

    // Поскольку надо получать и выводить сообщения об ошибках,
    // то подключаем созданный в файлах textsyntaxhighlighter.hpp/cpp
    // сигнал, с текстом ошибки, к слоту вывода сообщения statusbar,
    // расположенным в низу окна через строку состояния
    connect(highlighter, &TextSyntaxHighlighter::error,
            ui->statusbar, &QStatusBar::showMessage);
}

MainWindow::~MainWindow()
{
    delete highlighter; // Не забываем удалить
    delete ui;
}

// 1. Методы для вкладки Validator.
// Метод задаёт шаблон из поля lineEditPattern
// полю lineEditValidate
void MainWindow::on_pushButtonApply_clicked()
{
    // Очистим поле, в котором делаем проверку на правильность ввода
    // и метку с сообщением о правильности этого ввода
    ui->lineEditValidate->clear();
    ui->labelResult->clear();

    // Поскольку в конструкторе память была выделена под
    // динамический объект QRegularExpressionValidator,
    // то для работы с ним надо получить его адрес.
    // Это можно сделать через вызов метода validator()
    // и сделав приведение типа в стиле C++
    const QRegularExpressionValidator *regExpValConst =
            qobject_cast<const QRegularExpressionValidator *>
            (ui->lineEditValidate->validator());

    // Следует отметить, что метод validator() вернул указатель
    // на объект QRegularExpressionValidator как const,
    // а значит его модификация невозможна, хотя она нам и нужна.
    // Проблему можно решить с помощью привидения типа const_cast,
    // которое может отменить константность этого указателя,
    // но прежде надо проверить удалось ли получить указатель
    // на предыдущем приведении типа с помощью qobject_cast
    if (regExpValConst) {
        QRegularExpressionValidator *regExpVal =
                const_cast<QRegularExpressionValidator *>(regExpValConst);
        // Теперь можно спокойно задать новый объект QRegularExpression
        // и передать ему шаблон регулярного выражения
        // из объекта lineEditPattern
        regExpVal->setRegularExpression(
                    QRegularExpression(ui->lineEditPattern->text()));

        // Теперь проверим на правильность шаблон и если в нём будет ошибка,
        // то выведем об этом сообщение через нижнюю панель программы
        if (!regExpVal->regularExpression().isValid()) {
            QString errorString = regExpVal->regularExpression().errorString();
            ui->statusbar->showMessage(tr("Expression error: %1")
                                       .arg(errorString));
            // Так как шаблон с ошибкой, то дальше нет смысла
            // делать по нему поиск и можно выйти
            return;
        }
        else
            // Если всё правильно, то на всякий случай
            // очистим строку в нижней панели statusbar
            ui->statusbar->clearMessage();
    }
}

// Метод вызывается при редактировании поля lineEditValidate
// и показывает его корректность в соответствии
// с заданным шаблоном в поле lineEditPattern
void MainWindow::on_lineEditValidate_textChanged(const QString &arg1)
{
    // Если текста нет, то очищаем метку labelResult
    if (arg1.isEmpty())
        ui->labelResult->clear();

    // Получаем текущие настройки палитры метки labelResult
    QPalette palette = ui->labelResult->palette();
    // Проверяем, соответствует ли поле ввода шаблону
    if (ui->lineEditValidate->hasAcceptableInput()) {
        // Если да, то изменяем исходную палитру текста на зелёный
        palette.setColor(ui->labelResult->foregroundRole(), Qt::green);
        // и выводим сообщение о правильности введённого текста
        ui->labelResult->setText("Right");
    }
    else {
        // Если нет, то изменяем исходную палитру текста на красный
        palette.setColor(ui->labelResult->foregroundRole(), Qt::red);
        // и выводим сообщение о неправильности введённого текста
        ui->labelResult->setText("Wrong");
    }

    // Задаём новую палитру метке labelResult
    ui->labelResult->setPalette(palette);
}

// 2. Методы для вкладки Find Pattern.
// Метод ищет в тексте plainTextEdit по шаблону из lineEditSearchPattern
void MainWindow::on_pushButtonFind_clicked()
{
    // Задаём шаблон для поиска с подсветкой найденного фрагмента
    highlighter->setPattern(ui->lineEditSearchPattern->text());

    // Обновляем подсветку
    highlighter->rehighlight();
}

// Метод делает замену в найденных фрагментах текста
// по шаблону замены из поля lineEditReplacePattern
void MainWindow::on_pushButtonReplace_clicked()
{
    // Создадим объект обработки регулярных выражений
    // и передадим ему шаблон для поиска
    QRegularExpression regExp(ui->lineEditSearchPattern->text());

    // Проверим на правильность шаблон и если в нём будет ошибка,
    // то выведем об этом сообщение на экран и завершим метод
    if (!regExp.isValid()) {
        QString errorString = regExp.errorString();
        ui->statusbar->showMessage(tr("Expression error: %1")
                                            .arg(errorString));

        return;
    }
    else
        ui->statusbar->clearMessage();

    // Для замены исходного текста в объекте plainTextEdit,
    // можно воспользоваться уже существующей функцией замены replace(),
    // которая является частью класса QString и уже поддерживает работу
    // с регулярными выражениями QRegularExpression.
    // Результат замены будет записан в переменную result
    QString result = ui->plainTextEdit->toPlainText().replace(regExp,
                                        ui->lineEditReplacePattern->text());

    // Теперь текст с новыми фрагментами можно поместить
    // в объект plainTextEdit, для этого можно воспользоваться
    // методом setPlainText()
//    ui->plainTextEdit->setPlainText(result);

    // Однако у метода setPlainText() есть недостаток.
    // Вместе со записью нового текста он сбрасывает
    // буфер отменить/повторить, а также формат текста.
    // Если есть необходимость в последующем отменить замену,
    // например через сочетание клавиш "Ctrl+Z",
    // то можно сделать замену через выделение всего текста
    ui->plainTextEdit->selectAll();
    // и вставку нового с подсветкой
    ui->plainTextEdit->insertPlainText(result);
    // Таким образом возможность отмены действия по замене сохранится
}
