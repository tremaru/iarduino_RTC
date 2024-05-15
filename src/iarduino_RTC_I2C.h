//  Библиотека выбора реализации шины I2C (аппаратная или программная).
//	Библиотека iarduino для работы с модулем должна заранее знать, какие подключены библиотеки в скетче *.ino (Wire.h и/или iarduino_I2C_Software.h).
//	Но Arduino IDE не даёт доступ к созданию глобальных идентификаторов.
//	Значит две библиотеки подключённые в скетч *.ino не смогут узнать о существовании друг друга. Так как нельзя подключать файлы одной библиотеки в другую, не зная о существовании этой библиотеки у пользователя.
//	Основная задача этого файла - обойти ограничения Arduino IDE и узнать, подключена ли библиотека iarduino_I2C_Software.h в скетче *.ino и поддерживается ли библиотека Wire.h.
//	О том как подключить данный файл к ВАШЕЙ библиотеке, рассказано ниже...
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данного кода, как целиком, так и его частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор кода: Панькин Павел
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru
//
//	----------------------------------------------------------------------------------------------	//
//	ПОДКЛЮЧЕНИЕ:																					//
//																									//
//	В файле *.h ВАШЕЙ библиотеки, в начале необходимо вставить следующий код:						//
/**																									//
	#include "Название_данного_файла.h"																//	Подключаем библиотеку выбора реализации шины I2C.
																									//
	#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega2560__) || defined(ESP8266) || defined(ESP32) || defined(ARDUINO_ARCH_RP2040) || defined(RENESAS_CORTEX_M4) // Если подключена библиотека Wire или платы её поддерживают...
		#include <Wire.h>																			//	Разрешаем использовать библиотеку Wire в данной библиотеке.
	#endif																							//
	#if defined( iarduino_I2C_Software_h )															//	Если библиотека iarduino_I2C_Software подключена в скетче...
		#include <iarduino_I2C_Software.h>															//	Разрешаем использовать библиотеку iarduino_I2C_Software в данной библиотеке.
	#endif																							//
**/																									//
//																									//
//	В файле *.h ВАШЕЙ библиотеки, в конструкторе основаного класса нужно вставить код:				//
/**																									//
	selI2C = new iarduino_I2C_Select;																//	Переопределяем указатель selI2C на объект производного класса iarduino_I2C_Select.
**/																									//
																									//
//	В файле *.h ВАШЕЙ библиотеки, в блоке private основного класса нужно объявить указатель selI2C:	//
/**																									//
	private:																						//
	iarduino_I2C_VirtualSelect* selI2C;																//	Объявляем указатель на объект полиморфного класса iarduino_I2C_VirtualSelect, но в конструкторе текущего класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C_Select.
**/																									//
																									//
//	В файле *.h	в любой функции необходимо обратиться к функции selI2C->begin( объект_шины );		//
/**																									//
	public:																							//
	#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__)								//	Если подключена библиотека Wire.h
		bool begin (TwoWire* i=&Wire ){ selI2C->begin(i); return _begin(); }						//	Определяем функцию инициализации модуля (Параметр: объект для работы с аппаратной шиной I2C).
	#endif																							//
	#if defined(iarduino_I2C_Software_h)															//	Если подключена библиотека iarduino_I2C_Software.h
		bool begin (SoftTwoWire* i   ){ selI2C->begin(i); return _begin(); }						//	Определяем функцию инициализации модуля (Параметр: объект для работы с программной шиной I2C).
	#endif																							//
**/																									//
																									//
//	----------------------------------------------------------------------------------------------	//
//	ДОСТУПНЫЕ ФУНКЦИИ:																				//
																									//
//	Теперь в ВАШЕЙ библиотеке доступны следующие функции данной библиотеки:							//
/**																									//
	void	begin			(ссылка на объект класса TwoWire или SoftTwoWire                    );	//	Инициализация работы по аппаратной или программной шине I2C.
	void	begin			(void                                                               );	//	Переинициализация ранее выбранной шине I2C.
	uint8_t	getPinSDA		(void                                                               );	//	Получение номера вывода SDA.
	uint8_t	getPinSCL		(void                                                               );	//	Получение номера вывода SCL.
	void	setWireTimeout	(void                                                               );	//	Изменение таймаута ожидания ведомого на значение по умолчанию.
	void	setWireTimeout	(uint32_t                                                           );	//	Изменение таймаута ожидания ведомого в мкс.
	void	setClock		(uint32_t                                                           );	//	Изменение скорости передачи данных в Гц.
	bool	checkAddress	(uint8_t адрес_модуля                                               );	//	Проверка наличия ведомого с указанным адресом.
	bool	readBytes		(uint8_t адрес_модуля, uint8_t регистр, uint8_t* массив, uint8_t sum);	//	Пакетное чтение нескольких байт данных из регистров модуля.
	bool	readBytes		(uint8_t адрес_модуля,                  uint8_t* массив, uint8_t sum);	//	Пакетное чтение нескольких байт данных из           модуля.
	uint8_t readByte		(uint8_t адрес_модуля, uint8_t регистр                              );	//	Чтение   одного байта           данных из регистра  модуля.
	bool	writeBytes		(uint8_t адрес_модуля, uint8_t регистр, uint8_t* массив, uint8_t sum);	//	Пакетная запись нескольких байт данных в  регистры  модуля.
	bool	writeBytes		(uint8_t адрес_модуля,                  uint8_t* массив, uint8_t sum);	//	Пакетная запись нескольких байт данных в            модуль.
	bool	writeByte		(uint8_t адрес_модуля, uint8_t регистр, uint8_t  байт               );	//	Запись   одного байта           данных в  регистр   модуля.
**/																									//
																									//
//	----------------------------------------------------------------------------------------------	//
//	ПРЕДУПРЕЖДЕНИЕ О УСТАРЕВШИХ БИБЛИОТЕКАХ:														//
																									//
	#if defined(iarduino_I2C_h)																		//	В ранних версиях реализации работы с шиной I2C создавался идентификатор iarduino_I2C_h.
		#error Ваши библиотеки iarduino для работы с шиной I2C устарели, пожалуйста обновите все используемые библиотеки iarduino.
	#endif																							//
	#if defined(pin_SW_SDA) || defined(pin_SW_SCL)													//	В ранних версиях реализации программной шины I2C нужно было указывать выводы pin_SW_SDA и pin_SW_SCL.
		#error Библиотеки iarduino работают с программной шиной I2C через библиотеку iarduino_I2C_Software. Смотрите: файл/примеры/iarduino_I2C...
	#endif																							//
	#if defined(iarduino_I2C_Select_Version) && iarduino_I2C_Select_Version<1						//	Если уже подключена библиотека выбора шины I2C с версией ниже 1, то информируем о необходимости обновить библиотеки.
		#error Ваши библиотеки iarduino для работы с шиной I2C устарели, пожалуйста обновите все используемые библиотеки iarduino.
	#endif																							//
																									//
//	----------------------------------------------------------------------------------------------	//
																									//
#ifndef iarduino_I2C_Select_h																		//
#define iarduino_I2C_Select_h																		//
																									//
#define iarduino_I2C_Select_Version 1																//	Версия данной библиотеки.
																									//
//	Если подключена или поддерживается библиотека Wire.h, то разрешаем её использовать:				//
	#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega2560__) || defined(ESP8266) || defined(ESP32) || defined(ARDUINO_ARCH_RP2040) || defined(RENESAS_CORTEX_M4) // Если подключена библиотека Wire.h или платы её поддерживают...
		#define I2C_HW_includes																		//	Идентификатор разрешения работы с библиотекой Wire.h
		#include <Wire.h>																			//	Разрешаем использовать библиотеку Wire.h в данной библиотеке.
	#endif																							//
																									//
//	Если подключена библиотека iarduino_I2C_Software.h, то разрешаем её использовать:				//
	#if defined( iarduino_I2C_Software_h )															//	Если библиотека iarduino_I2C_Software.h подключена в скетче...
		#define I2C_SW_includes																		//	Идентификатор разрешения работы с библиотекой iarduino_I2C_Software.h
		#include <iarduino_I2C_Software.h>															//	Разрешаем использовать библиотеку iarduino_I2C_Software.h в данной библиотеке.
	#endif																							//
																									//
class iarduino_I2C_VirtualSelect{																	//	Определяем полиморфный класс
	public:																							//
		virtual bool	readBytes		(uint8_t, uint8_t , uint8_t*, uint8_t);						//	Пакетное чтение нескольких байт данных из регистров модуля	(аргументы: адрес_модуля, адрес_первого_регистра, указатель_на_массив, количество_байт).
		virtual bool	readBytes		(uint8_t,           uint8_t*, uint8_t);						//	Пакетное чтение нескольких байт данных из           модуля	(аргументы: адрес_модуля,                         указатель_на_массив, количество_байт).
		virtual uint8_t readByte		(uint8_t, uint8_t                    );						//	Чтение   одного байта           данных из регистра  модуля	(аргументы: адрес_модуля, адрес_регистра                                              ).
		virtual bool	writeBytes		(uint8_t, uint8_t , uint8_t*, uint8_t);						//	Пакетная запись нескольких байт данных в  регистры  модуля	(аргументы: адрес_модуля, адрес_первого_регистра, указатель_на_массив, количество_байт).
		virtual bool	writeBytes		(uint8_t,           uint8_t*, uint8_t);						//	Пакетная запись нескольких байт данных в            модуль	(аргументы: адрес_модуля,                         указатель_на_массив, количество_байт).
		virtual bool	writeByte		(uint8_t, uint8_t , uint8_t          );						//	Запись   одного байта           данных в  регистр   модуля	(аргументы: адрес_модуля, адрес_регистра        , байт_для_записи                     ).
		virtual bool	checkAddress	(uint8_t                             );						//	Проверка наличия ведомого с указанным адресом				(аргумент : адрес_модуля).
		virtual void	setWireTimeout	(uint32_t                            );						//	Изменение таймаута ожидания ведомого						(аргумент : timeout_мкс). Если timeout=0 то таймаут отключён.
		virtual void	setWireTimeout	(void                                );						//	Изменение таймаута ожидания ведомого на значение по умолчанию.
		virtual uint8_t	getPinSDA		(void                                );						//	Получение номера вывода SDA.
		virtual uint8_t	getPinSCL		(void                                );						//	Получение номера вывода SCL.
		virtual void	begin			(void                                );						//	Переинициализация шины I2C.
		#if defined(I2C_HW_includes)																//
		virtual void	begin			(TwoWire*                            );						//	Инициализация работы по аппаратной шине I2C с указанием объекта класса TwoWire.
		#endif																						//
		#if defined(I2C_SW_includes)																//
		virtual void	begin			(SoftTwoWire*                        );						//	Инициализация работы по программной шине I2C с указанием объекта класса SoftTwoWire.
		#endif																						//
};																									//
																									//
class iarduino_I2C_Select: public iarduino_I2C_VirtualSelect{										//
																									//
	public:																							//
																									//
	//	Функции инициализации работы с выбранной шиной I2C:											//
		#if defined(I2C_HW_includes)																//	Если подключена библиотека Wire...
			void begin(TwoWire* i    ){ objI2C=i; flgI2CType=1; (*(TwoWire*    )objI2C).begin(); }	//	Присваиваем указателю objI2C адрес из ссылки i указывающий на объект класса TwoWire.
		#endif																						//
		#if defined(I2C_SW_includes)																//	Если подключена библиотека iarduino_I2C_Software...
			void begin(SoftTwoWire* i){ objI2C=i; flgI2CType=2; (*(SoftTwoWire*)objI2C).begin(); }	//	Присваиваем указателю objI2C адрес из ссылки i указывающий на объект класса SoftTwoWire.
		#endif																						//
																									//
	//	Функция переинициации ранее выбранной шины I2C:												//
		void begin(void){																			//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ (*(TwoWire*    )objI2C).begin(); }								//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ (*(SoftTwoWire*)objI2C).begin(); }								//
			#endif																					//
		}																							//
																									//
	//	Функция получения номера вывода SDA:														//
		uint8_t getPinSDA(void){																	//
			int scl=0, sda=0;																		//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ sda=SDA; }														//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ (*(SoftTwoWire*)objI2C).getPins(&sda, &scl); }					//
			#endif																					//
			return (uint8_t)sda;																	//
		}																							//
																									//
	//	Функция получения номера вывода SCL:														//
		uint8_t getPinSCL(void){																	//
			int scl=0, sda=0;																		//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ scl=SCL; }														//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ (*(SoftTwoWire*)objI2C).getPins(&sda, &scl); }					//
			#endif																					//
			return (uint8_t)scl;																	//
		}																							//
																									//
	//	Изменение таймаута ожидания ведомого в мкс (для программной шины):							//
		void setWireTimeout(uint32_t timeout){	//	Если timeout=0 мкс, то таймаут отключён.		//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ (*(SoftTwoWire*)objI2C).setWireTimeout(timeout); }				//
			#endif																					//
		}																							//
	//	Изменение таймаута ожидания ведомого на значение по умолчанию:								//
		void setWireTimeout(void){																	//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ (*(SoftTwoWire*)objI2C).setWireTimeout(); }						//
			#endif																					//
		}																							//
																									//
	//	Функция пакетного чтения нескольких байт данных из регистров модуля:						//
		bool readBytes(uint8_t adr, uint8_t reg, uint8_t *data, uint8_t sum){						//	Определяем функцию пакетного чтения нескольких байт данных из регистров модуля	(аргументы: адрес_модуля, адрес_первого_регистра, указатель_на_массив, количество_байт)
			uint8_t i=0;																			//	Предустанавливаем переменную i в значение 0 - это ответ по умолчанию.
			beginTransmission(adr);																	//	Инициируем передачу данных по шине I2C к устройству с адресом adr и битом RW=0 => запись. При этом сама передача не начнётся.
			write(reg);																				//	Определяем значение первого байта (reg - адреса регистра) который будет отправлен после байта адреса. Функция write() поместит указанный байт в буфер для передачи.
			i = endTransmission(false); if(i){ return false; }										//	Выполняем инициированную ранее передачу данных (без установки состояния STOP). Функция endTransmission() возвращает: 0-передача успешна / 1 - переполнен буфер для передачи / 2 - получен NACK при передаче адреса / 3 - получен NACK при передаче данных / 4 - другая ошибка.
			if( !requestFrom( adr, sum )    ){ return false; }										//	Читаем (запрашиваем) sum байт данных от устройства с адресом adr и битом RW=1 => чтение. Функция requestFrom() возвращает количество реально принятых байтов. Так как предыдущая функция не установила состояние STOP, то состояние START данной функции будет расценено как RESTART.
			while( available() && i<sum     ){ data[i]=read(); i++; }								//	Читаем sum принятых байт из буфера для полученных данных в массив по указателю data.
			while( available()              ){         read();      }								//	Если в буфере для полученных данных есть еще принятые байты, то чистим буфер.
			return (bool)(i==sum);																	//	Возвращаем true если удалось прочитать sum байт.
		}																							//
																									//
	//	Функция пакетного чтения нескольких байт данных из модуля:									//
		bool readBytes(uint8_t adr, uint8_t *data, uint8_t sum){									//	Определяем функцию пакетного чтения нескольких байт данных из модуля	(аргументы: адрес_модуля, указатель_на_массив, количество_байт)
			uint8_t i=0;																			//	Предустанавливаем переменную i в значение 0 - это ответ по умолчанию.
			if( !requestFrom( adr, sum ) ){ return false; }											//	Читаем (запрашиваем) sum байт данных от устройства с адресом adr и битом RW=1 => чтение. Функция requestFrom() возвращает количество реально принятых байтов.
			while( available() && i<sum  ){ data[i]=read(); i++; }									//	Читаем sum принятых байт из буфера для полученных данных в массив по указателю data.
			while( available()           ){         read();      }									//	Если в буфере для полученных данных есть еще принятые байты, то чистим буфер.
			return (bool)(i==sum);																	//	Возвращаем true если удалось прочитать sum байт.
		}																							//
																									//
	//	Функция чтения одного байта данных из модуля:												//
		uint8_t readByte(uint8_t adr, uint8_t reg){uint8_t i=0; readBytes(adr,reg,&i,1); return i;}	//	Чтение одного байта данных из регистра модуля	(аргументы: адрес_модуля, адрес_регистра). Возвращает байт данных.
																									//
	//	Функция пакетной записи нескольких байт данных в регистр модуля:							//
		bool writeBytes(uint8_t adr, uint8_t reg, uint8_t *data, uint8_t sum){						//	Определяем функцию пакетной записи нескольких байт данных в регистры модуля	(аргументы: адрес_модуля, адрес_первого_регистра, указатель_на_массив, количество_байт)
			uint8_t i=0;																			//	Предустанавливаем переменную i в значение 0 - это результат записи
			beginTransmission(adr);																	//	Инициируем передачу данных по шине I2C к устройству с адресом adr и битом RW=0 => запись. При этом сама передача не начнётся.
			write(reg);																				//	Определяем значение первого байта (reg - адреса регистра) который будет отправлен после байта адреса. Функция write() поместит указанный байт в буфер для передачи.
			if( sum ){ write(data, sum); }															//	Определяем значения следующих байт (data - массив данных) которые будут отправлены после байта регистра. Функция write() поместит sum элементов массива data в буфер для передачи.
			i = endTransmission();																	//	Выполняем инициированную ранее передачу данных. Функция endTransmission() возвращает: 0-передача успешна / 1 - переполнен буфер для передачи / 2 - получен NACK при передаче адреса / 3 - получен NACK при передаче данных / 4 - другая ошибка / 5 - timeout. В качестве параметра функция endTransmission() может принимать флаг установки стсояния STOP - по умолчанию true.
			return (bool)(i==0);																	//	Возвращает true если функция endTransmission() вернула 0.
		}																							//
																									//
	//	Функция пакетной записи нескольких байт данных в модуль:									//
		bool writeBytes(uint8_t adr, uint8_t *data, uint8_t sum){									//	Определяем функцию пакетной записи нескольких байт данных в модуль	(аргументы: адрес_модуля, указатель_на_массив, количество_байт)
			uint8_t i=0;																			//	Предустанавливаем переменную i в значение 0 - это результат записи
			beginTransmission(adr);																	//	Инициируем передачу данных по шине I2C к устройству с адресом adr и битом RW=0 => запись. При этом сама передача не начнётся.
			if( sum ){ write(data, sum); }															//	Указываем массив данных который будет отправлен после байта адреса. Функция write() поместит sum элементов массива data в буфер для передачи.
			i = endTransmission();																	//	Выполняем инициированную ранее передачу данных. Функция endTransmission() возвращает: 0-передача успешна / 1 - переполнен буфер для передачи / 2 - получен NACK при передаче адреса / 3 - получен NACK при передаче данных / 4 - другая ошибка / 5 - timeout. В качестве параметра функция endTransmission() может принимать флаг установки стсояния STOP - по умолчанию true.
			return (bool)(i==0);																	//	Возвращает true если функция endTransmission() вернула 0.
		}																							//
																									//
	//	Функция записи одного байта данных в модуль:												//
		bool writeByte(uint8_t adr, uint8_t reg, uint8_t data){return writeBytes(adr,reg,&data,1);}	//	Запись одного байта данных в регистр модуля		(аргументы: адрес_модуля, адрес_регистра, байт_для_записи). Возвращает true при успешной записи.
																									//
	//	Функция проверки наличия ведомого по его адресу: 											//
		bool checkAddress(uint8_t adr){																//	Определяем функцию записи одного байта данных в регистр модуля					(аргументы: адрес_регистра, байт_данных)
			uint8_t i=0;																			//	Предустанавливаем переменную i в значение 0 - это результат проверки.
			beginTransmission(adr);																	//	Инициируем передачу данных по шине I2C к устройству с адресом adr и битом RW=0 => запись. При этом сама передача не начнётся.
			i = endTransmission();																	//	Выполняем инициированную ранее передачу данных. Функция endTransmission() возвращает: 0-передача успешна / 1 - переполнен буфер для передачи / 2 - получен NACK при передаче адреса / 3 - получен NACK при передаче данных / 4 - другая ошибка / 5 - timeout. В качестве параметра функция endTransmission() может принимать флаг установки стсояния STOP - по умолчанию true.
			return (bool)(i==0);																	//	Возвращает true если функция endTransmission() вернула 0.
		}																							//
																									//
	private:																						//
																									//
	//	Функция инициации передачи данных ведомому с указанным адресом:								//
		void beginTransmission(uint8_t adr){														//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ (*(TwoWire*    )objI2C).beginTransmission(adr); }				//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ (*(SoftTwoWire*)objI2C).beginTransmission(adr); }				//
			#endif																					//
		}																							//
																									//
	//	Функция помещения очередного байта в буфер для передачи ведомому:							//
		void write(uint8_t data){																	//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ (*(TwoWire*    )objI2C).write(data); }							//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ (*(SoftTwoWire*)objI2C).write(data); }							//
			#endif																					//
		}																							//
																									//
	//	Функция помещения массива байт в буфер для передачи ведомому:								//
		size_t write(const uint8_t* data, size_t sum){												//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ return (*(TwoWire*    )objI2C).write(data,sum); }				//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ return (*(SoftTwoWire*)objI2C).write(data,sum); }				//
			#endif																					//
		}																							//
																									//
	//	Функция выполнения инициированной ранее передачи данных из буфера ведомому:					//
		uint8_t endTransmission(bool sendStop=true){												//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ return (*(TwoWire*    )objI2C).endTransmission(sendStop); }		//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ return (*(SoftTwoWire*)objI2C).endTransmission(sendStop); }		//
			#endif																					//
		}																							//
																									//
	//	Функция выполнения чтения от ведомого указанного количества байт:							//
		size_t requestFrom(uint8_t adr, size_t sum){												//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ return (*(TwoWire*    )objI2C).requestFrom(adr,sum); }			//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ return (*(SoftTwoWire*)objI2C).requestFrom(adr,sum); }			//
			#endif																					//
		}																							//
																									//
	//	Функция возвращает количество байт оставшихся в буфере после чтения:						//
		int available(void){																		//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ return (*(TwoWire*    )objI2C).available(); }					//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ return (*(SoftTwoWire*)objI2C).available(); }					//
			#endif																					//
		}																							//
																									//
	//	Функция возвращает очередной байт из буфера прочитанных данных:								//
		int read(void){																				//
			#if defined(I2C_HW_includes)															//
				if(flgI2CType==1){ return (*(TwoWire*    )objI2C).read(); }							//
			#endif																					//
			#if defined(I2C_SW_includes)															//
				if(flgI2CType==2){ return (*(SoftTwoWire*)objI2C).read(); }							//
			#endif																					//
		}																							//
																									//
		void*	objI2C;																				//	Указатель на объект работы с шиной I2C (Wire, Wire1, ..., SoftwareWire).
		uint8_t	flgI2CType = 0;																		//	Флаг указывающий на тип соединения (0-нет, 1-TwoWire, 2-SoftTwoWire).
};																									//
																									//
#endif																								//
