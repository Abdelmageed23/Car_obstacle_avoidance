#ifndef _SWICU_INTERFACE_H_
#define _SWICU_INTERFACE_H_

void SW_ICU_RISING(void);
void SW_ICU_FALLING(void);

void SW_ICU_init(void);

ERROR_STATUS_t SW_ICUCounts(uint32_t* u32_counts);


#endif
