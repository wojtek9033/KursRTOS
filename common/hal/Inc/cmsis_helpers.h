#define FILL_REG(REG, BITS, VAL) {				\
	REG &= ~BITS;								\
	REG |= ((VAL << BITS##_Pos) & BITS);		\
}												\

#define GPIO_MODER_AF 			2
#define GPIO_MODER_INPUT 		0
#define GPIO_MODER_OUTPUT 		1
#define GPIO_MODER_ANALOG		3

#define GPIO_PUPDR_NONE 0
#define GPIO_PUPDR_PUP 1

#define GPIO_OTYPER_PUSH_PULL 	0

#define SYSCFG_EXTI_PC 2 // means GPIO C
