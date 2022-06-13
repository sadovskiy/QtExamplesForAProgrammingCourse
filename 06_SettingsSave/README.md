# 06 Пример сохранения и восстановления параметров интерфейса в Qt

Демонстрация работы приложения с GUI состоящего из объектов, расположенных на форме `MainWindow`:
- от класса `QCheckBox`

Для работы необходимо использовать объекты класса `QSettings`, которые задают возможность хранить параметры, в то время, когда приложение закрыто. Для этого в ОС Windows используется реестр, а в Linux/Mac скрытый файл в домашнем каталоге пользователя. В примере для сохранения параметров у объекта `settings` используется метод `setValue()`, а для восстановления метод `value()`. В обоих случаях надо придумать общий для параметра идентификатор, например **position** для хранения местоположения окна. Для удобства можно делить настройки на отдельный группы с помощью методов `beginGroup()` и `endGroup()`. В качестве примеров параметров для запоминания при закрытии приложения и восстановлении при запуске используются: местоположение, размер главного окна и отметка расположенного на нём объекта `checkBox`.
