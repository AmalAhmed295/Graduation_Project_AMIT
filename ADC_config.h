#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


/*options
 * 1: DIVISION_BY_2
 * 2: DIVISION_BY_4
 * 3: DIVISION_BY_8
 * 4: DIVISION_BY_16
 * 5: DIVISION_BY_32
 * 6: DIVISION_BY_64
 * 7: DIVISION_BY_128
 * */

#define ADC_U8_PRESCALER              DIVISION_BY_128

#define ADC_U32_TIMEOUT                50000

/*options
 *   1: EIGHT_BIT
 *   2: TEN_BIT
 * */
#define ADC_U8_RESOLUTION             EIGHT_BIT
#endif
