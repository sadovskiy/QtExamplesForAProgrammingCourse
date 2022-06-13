# 12_01 Пример простой реализации технологии перетащить и отпустить (Drag and Drop) в Qt

Демонстрация работы приложения с GUI состоящего из двух объектов от класса `QTableWidget`, расположенных на форме `MainWindow`. В левой таблице `tableWidgetSource` есть данные для переноса в правую `tableWidgetDestination`.

В данном примере показано как можно организовать интерфейс пользователя с технологией «Перетащить и отпустить» (англ. Drag and Drop). Это простой пример, где всё необходимое для получения четвёрки реализуется через включение соответствующих свойств в редакторе форм.

В дизайнере надо добавить необходимый табличный виджет и в окне свойств объекта, унаследованных от класса `QAbstractItemView`, надо включить пункт `dragEnabled`. Затем в пункте `dragDropMode` выставить `DragDrop`.

Таким образом можно будет переносить ячейки внутри приложения и между такими же приложениями **Qt**. Переносить в другие программы, такие как блокнот, нельзя, так как ячейки имеют собственный бинарный формат, который не понимают другие программы.

Ещё несколько свойств, связанных с перетаскиванием.
- `showDropIndicator` – отвечает за отображения в самой таблице индикатора, появляющегося при перетаскивании ячейки, показывающего куда будет помещена ячейка если её в этом месте отпустить. Может выглядеть в таблице, или как прямоугольник, или как линия в нижней части ячейки. Если прямоугольник, то значит вставка будет в эту ячейку, а если линия, значит вставка будет как новая строка между существующими или в конец таблицы. Линия появляется если свойство `dragDropOverwriteMode` выключено.
- `dragDropOverwriteMode` – отвечает за то, как поступать с ячейками таблицы. Если свойство включено, то вставка ячеек между двух других будет затруднена, о если всё-таки удастся, то значение пойдёт в первый столбец низа таблицы. При вставке в ячейку старые данные будут стираться новыми. Если опция выключена, то данные будут вставляться между ячеек создавая
новую строку между существующими.

Для реализации различных режимов выделения ячеек, свойство `selectionMode` должно быть уставлено в режим `ExtendedSelection`. Для выделения группы ячеек надо зажимать клавишу **Shift** и выделять нужные ячейки левой клавишей указателя мышь. Это позволит делать одну непрерывную группу ячеек. Затем можно перетащить всё группу. Если зажать **Shift** и затем потащить одну ячейку, зажав при этом левую клавишу мыши, то данные из старого места будут удалены и вставлены в то место, где она будет отпущена, в рамках одной таблицы. Использование зажатой клавиши **Ctrl** даст возможность выделять мышью несколько отдельных ячеек. При этому будут создаваться отдельные массивы выделенных ячеек, даже если они рядом. Соответствующие методы (например `selectedRanges()`), ответственные за работу с выделенной областью, будут возвращать эти отдельные области размером в одну ячейку.