/*
 *	CrossInteger.h
 *	Fading class
 *
 *	@author		Nikolai Tikhonov aka Dragon_Knight <dubki4132@mail.ru>, https://vk.com/globalzone_edev
 *	@licenses	MIT https://opensource.org/licenses/MIT
 *	@repo		https://github.com/Dragon-Knight/CrossInteger
*/

#pragma once

template<typename T>
class CrossInteger
{
	public:
		using callback_t = void (*)(T value, bool complete);
		using conversion_t = T (*)(T min, T max, T from, T to, T current);
		
		CrossInteger()
		{
			return;
		};
		
		CrossInteger(callback_t callback, T val, T min, T max, T step, uint32_t interval) : _data{val, val, min, max, step, interval, 0, callback, nullptr}
		{
			return;
		};
		
		// Указать колбэк-функцию изменения значения.
		void SetCallback(callback_t callback)
		{
			_data.callback = callback;
			
			return;
		};
		
		// Указать колбэк-функцию пересчёта значения.
		void SetConversion(conversion_t conversion)
		{
			_data.conversion = conversion;
			
			return;
		};
		
		// Указать текущее значение.
		void SetVal(T val)
		{
			_data.val = val;
			_data.val_to = val;
			
			return;
		};
		
		// Указать минимальное значение.
		void SetMin(T min)
		{
			_data.min = min;
			
			return;
		};
		
		// Указать максимальное значение.
		void SetMax(T max)
		{
			_data.max = max;
			
			return;
		};
		
		// Указать шаг изменения значения.
		void SetStep(T step)
		{
			_data.step = step;
			
			return;
		};
		
		// Указать интервал изменения значения.
		void SetInterval(uint32_t interval)
		{
			_data.interval = interval;
			
			return;
		};
		
		// Мгновенно установить минимальное значение.
		void GoMin()
		{
			if(_data.val != _data.min)
			{
				_data.val = _data.min;
				_data.val_to = _data.val;
				_data.callback( _data.val, true );
			}
			
			return;
		};
		
		// Мгновенно установить максимальное значение.
		void GoMax()
		{
			if(_data.val != _data.max)
			{
				_data.val = _data.max;
				_data.val_to = _data.val;
				_data.callback( _data.val, true );
			}
			
			return;
		};
		
		// Мгновенно установить среднее значение.
		void GoCenter()
		{
			T new_val = (_data.min + _data.max) / 2;
			if(_data.val != new_val)
			{
				_data.val = new_val;
				_data.val_to = _data.val;
				_data.callback( _data.val, true );
			}
			
			return;
		};
		
		// Плавно установить указанное значение.
		void FadeTo(T val_to)
		{
			if(_data.min <= val_to && _data.max >= val_to)
			{
				_data.val_from = _data.val;
				_data.val_to = val_to;
			}
			
			return;
		};
		
		// Плавно установить минимальное значение.
		void FadeMin()
		{
			_data.val_from = _data.val;
			_data.val_to = _data.min;
			
			return;
		};
		
		// Плавно установить максимальное значение.
		void FadeMax()
		{
			_data.val_from = _data.val;
			_data.val_to = _data.max;
			
			return;
		};
		
		// Плавно установить среднее значение.
		void FadeCenter()
		{
			_data.val_from = _data.val;
			_data.val_to = (_data.min + _data.max) / 2;
			
			return;
		};
		
		// Получить текущее значение.
		T GetVal(/*bool forced = false*/)
		{
			return _data.val;
		};
		
		//
		void GetCallback()
		{
			_data.callback( _data.val, (_data.val == _data.val_to) );
		}
		
		// Обработка класса.
		void Processing(uint32_t currentTime = millis())
		{
			if( (_data.update + _data.interval) <= currentTime && _data.val != _data.val_to)
			{
				_data.val = (_data.conversion != nullptr) ? _data.conversion(_data.min, _data.max, _data.val_from, _data.val_to, _data.val) : _Move();
				_data.callback( _data.val, (_data.val == _data.val_to) );
				_data.update = currentTime;
			}
			
			return;
		};
	protected:
	private:
		// 'Двигает' число в нужную сторону но не даёт уйти за границу.
		T _Move()
		{
			T result;
			
			if( abs(_data.val - _data.val_to) / _data.step > 0 )
			{
				if(_data.val > _data.val_to){ result = _data.val - _data.step; }
				else{ result = _data.val + _data.step; }
			}
			else
			{
				result = _data.val_to;
			}
			
			return result;
		};
		
		struct data_t
		{
			T val;				// Текущее значение.
			T val_to;			// Значение, к которому стремится val.
			T val_from;			// Значение, от которого стремится val.
			T min;				// Минимальное значение val.
			T max;				// Максимальное значение val.
			T step;				// Размер шага.
			uint32_t interval;	// Интервал обновления, в мс.
			uint32_t update;	// Время последнего обновления.
			callback_t callback;		// Колбэк-функция изменения значения.
			conversion_t conversion;	// Колбэк-функция пересчёта значения.
		} _data;
};
