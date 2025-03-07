#include "branqs.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // para usleep

pthread_mutex_t writeOutputsBufferLock = PTHREAD_MUTEX_INITIALIZER;


#define BC8S_IEC_BASE_ADDRESS 600
unsigned char BC8S_outputBuffers[16];
unsigned char BC8S_enabled[16];

// Função auxiliar para dormir x milissegundos
void sleep_ms(int ms) {
    usleep(ms * 1000);
}

void setDigitalOutput(int moduleAddress, int value) {
    printf("setDigitalOutput: Módulo %d, valor %d\n", moduleAddress, value);
}

void *CANcommunicationThread(void *args)
{
    while(1) {

        //////////////////////////////////////////////////////////////
        // 16 Módulos BC8S - 8 saídas digitais por módulo
        //////////////////////////////////////////////////////////////
        int BC8S_address = 600;
        int BC8S_output = 0x00;

        for (BC8S_address=0;BC8S_address<16;BC8S_address++) {
            unsigned char BC8SoutputEnabled;
            unsigned char outputStates;

            pthread_mutex_lock(&writeOutputsBufferLock);
                BC8SoutputEnabled=BC8S_enabled[BC8S_address];
                outputStates=BC8S_outputBuffers[BC8S_address];
            pthread_mutex_unlock(&writeOutputsBufferLock);
            
            if (BC8SoutputEnabled) {
                    setDigitalOutput(BC8S_address,outputStates);
            }
        }

        sleep_ms(50);
    }

    pthread_exit(NULL);
}


int main()
{
    pthread_t CANthread;
    int ret = pthread_create(&CANthread, NULL, CANcommunicationThread, NULL);
    if (ret != 0) {
        fprintf(stderr, "Erro ao criar thread: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    //printf("Branqs successfully initialized\n");
    //log("Branqs successfully initialized\n");

    // Em aplicações reais pode ser interessante esperar a thread ou implementar sinal de término.
    // pthread_join(CANthread, NULL);
}