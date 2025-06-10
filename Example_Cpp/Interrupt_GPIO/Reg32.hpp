/*
 * Reg32.hpp
 *
 *  Created on: Jun 6, 2025
 *      Author: aresi
 */

#ifndef REG32_HPP_
#define REG32_HPP_

#include <cstdint>

/*
 * template<std::uintptr_t address>: le decimos al compilador que vamos a
 * usar una dirección específica de un registro (como 0x40059000) para esta clase.
 * Sirve para generar clases únicas para cada dirección de registro que se defina.
 * */
template<std::uintptr_t ADDRESS>
/*
 * Clase Reg32 creada por métodos estáticos:
 * - No necesitan un objeto para usarse.
 * - No acceden a variables miembro, debido a que no hay objetos.
 * - Minimo uso de RAM.
 * - No hay variables que mantener en la clase.
 * - evitar errores al crear instancias innecesarias, porque los registros ya existen.
 * */
class Reg32 {
	public:

		static inline void write(uint32_t value)
		{
			*reg() = value;
		}

		static inline void setBits(uint8_t mask, uint8_t bit)
		{
			*reg() |= (mask << bit);
		}

		static inline void clearBits(uint32_t mask, uint8_t bit)
		{
			*reg() &= ~(mask << bit);
		}

		static inline uint32_t read()
		{
			return *reg();
		}

	private:
		static inline volatile uint32_t* reg()
		{
			return reinterpret_cast < volatile uint32_t * > (ADDRESS);
		}

	    /*
	     * Impedir instancias, indicando al compilador que nunca
	     * se podrán crear objetos de esta clase
	     * */
		Reg32() = delete;
	    ~Reg32() = delete;
	    Reg32(const Reg32&) = delete;
	    Reg32& operator=(const Reg32&) = delete;

};
#endif /* REG32_HPP_ */
