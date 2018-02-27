################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Botao.cpp \
../BotaoPrincipal.cpp \
../Celula.cpp \
../Jogo.cpp \
../Numero.cpp \
../Tabuleiro.cpp \
../main.cpp 

OBJS += \
./Botao.o \
./BotaoPrincipal.o \
./Celula.o \
./Jogo.o \
./Numero.o \
./Tabuleiro.o \
./main.o 

CPP_DEPS += \
./Botao.d \
./BotaoPrincipal.d \
./Celula.d \
./Jogo.d \
./Numero.d \
./Tabuleiro.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


