#include "./lib/branqs.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

pthread_mutex_t writeOutputsBufferLock = PTHREAD_MUTEX_INITIALIZER;

#define BC8S_IEC_BASE_ADDRESS 600
unsigned char BC8S_outputBuffers[16] = {0};
unsigned char BC8S_enabled[16] = {0};

void sleep_ms(int ms) {
    usleep(ms * 1000); 
}

void *CANcommunicationThread(void *args)
{
    while(1) {
        //////////////////////////////////////////////////////////////
        // 16 Módulos BC8S - 8 saídas digitais por módulo
        //////////////////////////////////////////////////////////////
        for (int BC8S_address = 0; BC8S_address < 16; BC8S_address++) {
            unsigned char BC8SoutputEnabled;
            unsigned char outputStates;

            pthread_mutex_lock(&writeOutputsBufferLock);
                BC8SoutputEnabled = BC8S_enabled[BC8S_address];
                outputStates = BC8S_outputBuffers[BC8S_address];
            pthread_mutex_unlock(&writeOutputsBufferLock);
            
            if (BC8SoutputEnabled) {
                setDigitalOutput(BC8S_address, outputStates);
            }
        }
        sleep_ms(500);
    }
    pthread_exit(NULL);
}

void updateOutputCycle(int cycle) {
    pthread_mutex_lock(&writeOutputsBufferLock);
    for (int i = 0; i < 16; i++) {
        BC8S_enabled[i] = 1;  
        BC8S_outputBuffers[i] = (cycle % 2 == 0) ? 0b10101010 : 0b01010101;
    }
    pthread_mutex_unlock(&writeOutputsBufferLock);
}

int main()
{
    pthread_t CANthread;
    int ret = pthread_create(&CANthread, NULL, CANcommunicationThread, NULL);
    if(ret != 0) {
        fprintf(stderr, "Erro ao criar thread: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    printf("Branqs successfully initialized\n");

    int cycle = 0;
    while(1) {
        updateOutputCycle(cycle);
        cycle++;
        sleep_ms(3000); // Atualiza a cada 3 segundos
    }
    return 0;
}