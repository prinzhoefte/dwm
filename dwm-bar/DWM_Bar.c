/*

    Author: Justin Rauch

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
removeLast(char* str) {
    str[strlen(str)-1] = '\0';
}

void
getNetwork(char* network) {
	FILE *f = popen("nmcli | grep 'connected' | awk 'NR==1{print $4}'", "r");
    fgets(network, 100, f);
    removeLast(network);
    if(strcmp(network, "to") == 0)
        strcpy(network, "disconnected");
	pclose(f);
}

void
getCpu(char* cpu) {
    FILE *f = popen("top -bn1 | grep Cpu | awk 'NR==1{print $2}'", "r");
    fgets(cpu, 6, f);
    removeLast(cpu);
    pclose(f);
}

void
getMemory(char* memory) {
    FILE *f = popen("free -h | grep Mem | awk '{print $3}'", "r");
    fgets(memory, 6, f);
    removeLast(memory);
    pclose(f);
}

void
getTemp(char* temp) {
    FILE *f = popen("sensors -u coretemp-isa-0000 | grep temp1_input | awk '{print $2}'", "r");
    fgets(temp, 4, f);
    removeLast(temp);
    pclose(f);
}

void
getCharge(char* charge) {
    FILE *f = popen("cat /sys/class/power_supply/BAT0/capacity", "r");
    fgets(charge, 5, f);
    removeLast(charge);
    pclose(f);
}

void
getDate(char* date) {
    FILE *f = popen("date \"+%d-%m %T\"", "r");
    fgets(date, 15, f);
    pclose(f);
}

int
main() {
    char* output = malloc(sizeof(char)*136);
    char* cpu = malloc(sizeof(char)*6);
    char* memory = malloc(sizeof(char)*6);
    char* temp = malloc(sizeof(char)*4);
    char* charge = malloc(sizeof(char)*5);
    char* date = malloc(sizeof(char)*15);
    char* network = malloc(sizeof(char)*100);

    while(1) {
        getCpu(cpu);
        getMemory(memory);
        getTemp(temp);
        getCharge(charge);
        getDate(date);
        getNetwork(network);
        sprintf(output, 
            "%s '[ %s] [ %s%] [ %s] [ %sC] [ %s%] [ %s]'", 
            "xsetroot -name ", 
            network,
            cpu, 
            memory, 
            temp,
            charge,
            date
        );
        system(output);
        sleep(1);
    }
}
