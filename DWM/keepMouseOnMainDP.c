/*

    Author: Justin

*/

//Includes for C system calls
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//Include for the mouse position in X11
#include <X11/Xlib.h>

void
getMousePos(int* mousePosX, int* mousePosY)
{
    Display *display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);
    int x, y;
    unsigned int mask;
    XQueryPointer(display, root, &root, &root, &x, &y, &x, &y, &mask);
    XCloseDisplay(display);
    *mousePosX = x;
    *mousePosY = y;
}

void
getScreenCords(int* screenX_L, int* screenX_R, int* screenY_U, int* screenY_D, char* activeScreen)
{
    char xrandrCommand[100];
    char xrandrOutputString[100];
    char x[10];
    char y[10];
    char resX[10];
    char resY[10];
    int resXInt;
    int resYInt;
    int xInt;
    int yInt;
    sprintf(xrandrCommand, "xrandr | grep '%s' | cut -d ' ' -f 3", activeScreen);
    FILE* xrandrOutput = popen(xrandrCommand, "r");
    fgets(xrandrOutputString, 100, xrandrOutput);
    //For the primary window we have to use a diffrent command because xrandr changes the output slightly
    if(strcmp(xrandrOutputString, "primary") >= 0) {
        pclose(xrandrOutput);
        sprintf(xrandrCommand, "xrandr | grep '%s' | cut -d ' ' -f 4", activeScreen);
        FILE* xrandrOutput = popen(xrandrCommand, "r");
        fgets(xrandrOutputString, 100, xrandrOutput);
    }
    pclose(xrandrOutput);
    int size = strlen(xrandrOutputString);
    //get the x and y offsets
    for(int i = 0; i < size; i++) {
        if(xrandrOutputString[i] == '+') {
            for(int j = 0; j < size; j++) {
                x[j] = xrandrOutputString[j+i+1];
                if(xrandrOutputString[j+i+1] == '+') {
                    x[j] = '\0';
                    break;
                }
                for(int k = 0; k < size; k++) {
                    y[k] = xrandrOutputString[j+i+k+3];
                    if(xrandrOutputString[j+i+k+3] == ' ') {
                        y[k] = '\0';
                        break;
                    }
                }
            }
            break;
        }
    }
    //get screen resolution
    for(int i = 0; i < size; i++) {
        if(xrandrOutputString[i] == 'x') {
            for(int j = 0; j < size; j++) {
                resY[j] = xrandrOutputString[j+i+1];
                if(xrandrOutputString[j+i+1] == '+') {
                    resY[j] = '\n';
                    break;
                }
            }
            resX[i] = '\0';
            break;
        } else {
            resX[i] = xrandrOutputString[i];
        }
    }
    resXInt = atoi(resX);
    resYInt = atoi(resY);
    xInt = atoi(x);
    yInt = atoi(y);
    *screenX_L = xInt;
    *screenX_R = xInt + resXInt;
    *screenY_U = yInt;
    *screenY_D = yInt + resYInt;
}

void
checkUpdateMousePos(int* mousePosX, int* mousePosY, int* screenX_L, int* screenX_R, int* screenY_U, int* screenY_D, int offset)
{
    //Change the Position of the mouse to the right coordinates if necessary
    int ret = 0;
    if(*mousePosX >= *screenX_R - offset) {
        //Force the mouse to stay in the current screen
        *mousePosX = *screenX_R - offset;
        ret = 1;
    }
    if(*mousePosX <= *screenX_L + offset) {
        //Force the mouse to stay in the current screen
        *mousePosX = *screenX_L + offset;
        ret = 1;
    }
    if(*mousePosY >= *screenY_D - offset) {
        //Force the mouse to stay in the current screen
        *mousePosY = *screenY_D - offset;
        ret = 1;
    }
    if(*mousePosY <= *screenY_U + offset) {
        //Force the mouse to stay in the current screen
        *mousePosY = *screenY_U + offset;
        ret = 1;
    }
    if(ret) {
        Display *display = XOpenDisplay(NULL);
        Window root = DefaultRootWindow(display);
        XWarpPointer(display, None, root, 0, 0, 0, 0, *mousePosX, *mousePosY);
        XFlush(display);
        XCloseDisplay(display);
    }
}

void
main(int argc, char** argv)
{
    //Check if the user specified the active screen
    if(argc <= 2) {
        printf("Usage: ./keepMouseOnMainDP '[activeScreen]' '[offset]'\n");
        exit(1);
    }
    //Reserve memory for vars
    int offset;
    char* activeScreen = malloc(sizeof(char)*strlen(argv[1]));
    strcpy(activeScreen, argv[1]);
    offset = atoi(argv[2]);
    int* mousePosX = malloc(sizeof(int));
    int* mousePosY = malloc(sizeof(int));
    int* screenX_L = malloc(sizeof(int));
    int* screenX_R = malloc(sizeof(int));
    int* screenY_U = malloc(sizeof(int));
    int* screenY_D = malloc(sizeof(int));
    getScreenCords(screenX_L, screenX_R, screenY_U, screenY_D, activeScreen);
    while(1) {
        getMousePos(mousePosX, mousePosY);
        checkUpdateMousePos(mousePosX, mousePosY, screenX_L, screenX_R, screenY_U, screenY_D, offset);
    }
}