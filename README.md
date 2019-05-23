  

[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

  

# iarduino_Pressure_BMP [СКАЧАТЬ](https://github.com/tremaru/iarduino_Pressure_BMP/archive/master.zip)

Библиотека iarduino_Pressure_BMP позволяет считывать температуру окружающей среды и атмосферное давление с датчиков [BMP180](http://iarduino.ru/shop/Sensory-Datchiki/barometr-gy-68-datchik-atmosfernogo-davleniya-bmp180.html) и [BMP280](http://iarduino.ru/shop/Sensory-Datchiki/barometr-trema-modul.html), а так же рассчитывать высоту.

  

> Подробнее про установку библиотеки читайте в нашей [инструкции](https://wiki.iarduino.ru/page/Installing_libraries/).

  

Пример подключения к [Arduino](https://iarduino.ru/shop/boards/arduino-uno-r3.html)/[Piranha UNO](https://iarduino.ru/shop/boards/piranha-uno-r3.html) с помощью [Trema Shield](https://iarduino.ru/shop/Expansion-payments/trema-shield.html)

Подробнее о [подключении модуля](https://wiki.iarduino.ru/page/trema-modul-pressure-meter)

![enter image description here](https://iarduino.ru/img/upload/ff71929a63d941fd58dc5a60860d0671.png)

  

| Модель | Ссылка на магазин|

|--|--|

| BMP280 ![enter image description here](https://wiki.iarduino.ru/img/resources/840/840.svg) | https://iarduino.ru/shop/Sensory-Datchiki/barometr-trema-modul.html|

| BMP180 ![enter image description here](https://wiki.iarduino.ru/img/resources/840/840.svg) | https://iarduino.ru/shop/Sensory-Datchiki/barometr-gy-68-datchik-atmosfernogo-davleniya-bmp180.html |

  

## Описание библиотеки:

Данная библиотека может использовать как аппаратную, так и программную реализацию шины I2C.

О том как выбрать тип шины I2C рассказано в статье [Wiki - расширенные возможности библиотек iarduino для шины I2C](https://wiki.iarduino.ru/page/i2c_connection/).

  

**[ Подробное описание, подключение и примеры работы ](https://wiki.iarduino.ru/page/trema-modul-pressure-meter)**

  

## Назначение функций и переменных:

Подробное описание работы с библиотекой, находится в разделе [Wiki Четырёхразрядный индикатор](https://wiki.iarduino.ru/page/chetyrehrazryadnyy-indikator-trema-modul/  "Wiki Четырёхразрядный индикатор").

  

**Подключаем библиотеку.**

  

#include **<iarduino_Pressure_BMP.h>** // Подключаем библиотеку.

  

**Создаём объект (адрес по умолчанию 0x77).**

  

iarduino_Pressure_BMP **ОБЪЕКТ (** [ АДРЕС_I2C ] **);** // Создаём объект (адрес по умолчанию 0x77).

  

**Инициализация работы BMP датчика (с указанием его начальной высоты).**

  

Функция **begin(** [ ВЫСОТА ] **);** // Инициализация работы BMP датчика (с указанием его начальной высоты).

  

**Чтение показаний датчика (с выбором единицы измерения давления).**

  

Функция **read(** [ ЦИФРА ] **);** // Чтение показаний датчика (с выбором единицы измерения давления).

  

**Выбор точности измерений (подавление шума).**

  

Функция **measurement(** ЦИФРА **);** // Выбор точности измерений (подавление шума).

  

**Возвращает температуру окружающей среды в °С.**

  

Переменная **temperature** // Возвращает температуру окружающей среды в °С.

  

**Возвращает атмосферное давление в мм.рт.ст. или Па.**

  

Переменная **pressure** // Возвращает атмосферное давление в мм.рт.ст. или Па.

  

**Возвращает высоту относительно начальной в м.**

  

Переменная **altitude** // Возвращает высоту относительно начальной в м.

  

**Возвращает тип датчика: 180 или 280.**

  

Переменная **type** // Возвращает тип датчика: 180 или 280.

  

**Возвращает версию прошивки датчика.**

  

Переменная **version** // Возвращает версию прошивки датчика.

  
  
  
  
  
  
  
  
  
  

<!--stackedit_data:

eyJoaXN0b3J5IjpbLTEzNjk3NzY1MDldfQ==

-->
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTI1MDM2MDA5MSwtMTA3ODgyNDM3MCwxMT
YwNTU0NV19
-->